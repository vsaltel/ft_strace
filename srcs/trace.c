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
	ptrace(PTRACE_SYSCALL, trace->pid, NULL, NULL);
	if (waitpid(trace->pid, &trace->ret, WUNTRACED) == -1)
	{
		ft_dprintf(2, "ft_strace: waitpid fail\n");
		return (3);
	}
	if (WIFEXITED(trace->ret) || WIFSIGNALED(trace->ret))
	{
		if (!action && !ft_strcmp(trace->sys.name, "exit_group"))
			ft_printf(") = ?\n");
		ft_printf("+++ exited +++\n");
		return (1);
	}
	/*
	else if (WIFSTOPPED(trace->ret))
		ft_printf("sig : %d\n", WSTOPSIG(trace->ret));
	*/
	return (0);
}

int	tracing(t_trace *trace)
{
	int	ret;

	ptrace(PTRACE_SEIZE, trace->pid, NULL, NULL);
	ptrace(PTRACE_INTERRUPT, trace->pid, NULL, NULL);
	get_stack_file(trace);
	if (waitpid(trace->pid, &trace->ret, WUNTRACED) == -1)
	{
		ft_dprintf(2, "ft_strace: waitpid fail\n");
		return (3);
	}
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
