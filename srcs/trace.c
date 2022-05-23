#include "strace.h"
#include "summary.h"

static int get_memory(t_trace *trace)
{
	int	ptrace_ret;

	if (trace->arch == 32)
	{
		ft_memset(&trace->regs32, 0, sizeof(trace->regs32));
		trace->iov.iov_len = sizeof(trace->regs32);
		trace->iov.iov_base = &(trace->regs32);
	}
	else
	{
		ft_memset(&trace->regs64, 0, sizeof(trace->regs64));
		trace->iov.iov_len = sizeof(trace->regs64);
		trace->iov.iov_base = &(trace->regs64);
	}
	ptrace_ret = ptrace(PTRACE_GETREGSET, trace->pid, NT_PRSTATUS, &(trace->iov));
	if (ptrace_ret == -1)
	{
		perror("getregset");
		return (1);
	}
	return (0);
}

static int	next_syscall(t_trace *trace, int action)
{
	int	ret = 0;
	int	stopped = 0;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, trace->pid, NULL, trace->delivery_sig);
		ret = wait_child(trace, action);
		if (trace->c && !action)
			update_summary_time(trace);
		if (ret)
			return (3);
		trace->delivery_sig = 0;
		ret = check_child_state(trace, action);
		if (trace->detach)
			detach_prog(trace);
		if (!ret)
			break;
		if (ret == 1)
			return (1);
		if (ret == 2)
			stopped = 1;
	}
	return (stopped ? 4 : 0);
}

int	tracing(t_trace *trace)
{
	int	ret;
	int	loop = 0;

	while (1)
	{
		if ((ret = next_syscall(trace, 1)) && ret != 4)
			break ;
		if (!trace->c && loop && ret != 4)
			display_ret_syscall(trace->sys.ret, (trace->arch == 64) ? trace->regs64.rax : (long unsigned int)trace->regs32.eax);
		get_memory(trace);
		trace->sys = get_syscall(trace);
		if (!trace->c)
			display_syscall(trace, 0);
		if ((ret = next_syscall(trace, 0)) && ret != 4)
		{
			update_summary_count(trace, 0);
			break;
		}
		get_memory(trace);
		if (!trace->c)
			display_syscall(trace, 1);
		update_summary_count(trace, (long)((trace->arch == 64) ? trace->regs64.rax : (long unsigned int)trace->regs32.eax));
		loop = 1;
	}
	if (trace->c)
		display_summary(trace);
	return (0);
}
