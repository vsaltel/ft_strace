#include "strace.h"

int	tracing(t_trace *trace)
{
	signal(SIGINT, &catch_sigint);
	trace->ready = 1;
	while (1)
	{
		if (waitpid(trace->pid, &trace->ret, WUNTRACED) == -1)
		{
			ft_dprintf(2, "ft_strace: waitpid fail\n");
			return (3);
		}
		if (WIFEXITED(trace->ret) || WIFSIGNALED(trace->ret))
		{
			ft_printf("exiting\n");
			return (0);
		}
		/*
		else if (WIFSTOPPED(trace->ret))
			ft_printf("sig : %d\n", WSTOPSIG(trace->ret));
		*/

		ft_memset(&trace->regs, 0, sizeof(trace->regs));
		trace->iov.iov_len = sizeof(trace->regs);
		trace->iov.iov_base = &(trace->regs);
		if (ptrace(PTRACE_GETREGSET, trace->pid, NT_PRSTATUS, &(trace->iov)) == -1)
			perror("getregset");
		ft_printf("read %d eax : %d\n", trace->iov.iov_len, trace->regs.rax);
		ptrace(PTRACE_SYSCALL, trace->pid, NULL, NULL);
	}
	return (0);
}
