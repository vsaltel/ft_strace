#include "strace.h"

static void check_memory(t_trace *trace, int action)
{
	int	ptrace_ret;
	//int		fd;
	//long	tmp;

	ft_memset(&trace->regs, 0, sizeof(trace->regs));
	trace->iov.iov_len = sizeof(trace->regs);
	trace->iov.iov_base = &(trace->regs);
	ptrace_ret = ptrace(PTRACE_GETREGSET, trace->pid, NT_PRSTATUS, &(trace->iov));
	if (ptrace_ret == -1)
		perror("getregset");
	if (action)
		display_syscall(trace);
	else if (!ptrace_ret)
		ft_printf(") = %ld\n", trace->regs.rax);
	else
		ft_printf(") = ?\n");
	/*
	if ((fd = open(trace->stack_file, O_RDONLY)) > 0)
	{
		lseek(fd, trace->regs.rsp - (sizeof(tmp) * 3), SEEK_SET);
		read(fd, &tmp, sizeof(tmp));
		ft_printf(" 0x%lx", tmp);
		read(fd, &tmp, sizeof(tmp));
		ft_printf(" 0x%lx", tmp);
		read(fd, &tmp, sizeof(tmp));
		ft_printf(" 0x%lx", tmp);
		close(fd);
	}
	*/
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
		if (!action)
		ft_printf("exiting\n");
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
		check_memory(trace, 1);
		ret = next_syscall(trace, 0);
		if (ret > 0)
			return (ret == 1 ? 0 : ret);
		check_memory(trace, 0);
	}
	return (0);
}
