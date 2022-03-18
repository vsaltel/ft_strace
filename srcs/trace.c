#include "strace.h"

static int get_memory(t_trace *trace)
{
	int	ptrace_ret;

	ft_memset(&trace->regs, 0, sizeof(trace->regs));
	trace->iov.iov_len = sizeof(trace->regs);
	trace->iov.iov_base = &(trace->regs);
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

	while (1)
	{
		ptrace(PTRACE_SYSCALL, trace->pid, NULL, trace->delivery_sig);
		trace->delivery_sig = 0;
		if (wait_child(trace))
			return (3);
		if (!(ret = check_child_state(trace, action)))
			break;
		if (ret == 1)
			return (1);
	}
	return (0);
}

int	tracing(t_trace *trace)
{
	int	ret;

	while (1)
	{
		ret = next_syscall(trace, 1);
		if (ret > 0)
			return (ret == 1 ? 0 : ret);
		get_memory(trace);
		trace->sys = get_syscall(trace);
		display_syscall(trace);
		ret = next_syscall(trace, 0);
		if (ret > 0)
			return (ret == 1 ? 0 : ret);
		if (!get_memory(trace))
			display_ret_syscall(trace->sys.ret, trace->regs.rax);
	}
	return (0);
}
