#include "strace.h"
#include "syscall_name.h"

static char	*get_syscall_name(int code)
{
	int	i;

	i = -1;
	while (g_syscall[++i].name)
	{
		if (code == g_syscall[i].code)
			return (g_syscall[i].name);
	}
	return (NULL);
}

static void check_memory(t_trace *trace, int loop)
{
	//rdi, rsi, rdx, r10, r8, and r9
	char	*syscall_name;
	int		fd;
	//long	tmp;

	ft_memset(&trace->regs, 0, sizeof(trace->regs));
	trace->iov.iov_len = sizeof(trace->regs);
	trace->iov.iov_base = &(trace->regs);
	if (ptrace(PTRACE_GETREGSET, trace->pid, NT_PRSTATUS, &(trace->iov)) == -1)
		perror("getregset");
	syscall_name = get_syscall_name(trace->regs.orig_rax);
	if (syscall_name && loop > 2)
	{
		ft_printf("%s(", syscall_name);
		ft_printf("0x%lx,", trace->regs.rdi);
		ft_printf(" 0x%lx,", trace->regs.rsi);
		ft_printf(" 0x%lx)", trace->regs.rdx);
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
	write(1, "\n", 1);
}

int	tracing(t_trace *trace)
{
	int		loop = 0;

	ptrace(PTRACE_SEIZE, trace->pid, NULL, NULL);
	ptrace(PTRACE_INTERRUPT, trace->pid, NULL, NULL);
	get_stack_file(trace);
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
		check_memory(trace, loop);
		ptrace(PTRACE_SYSCALL, trace->pid, NULL, NULL);
		if (waitpid(trace->pid, &trace->ret, WUNTRACED) == -1)
		{
			ft_dprintf(2, "ft_strace: waitpid fail\n");
			return (3);
		}
		ptrace(PTRACE_SYSCALL, trace->pid, NULL, NULL);
		loop++;
	}
	return (0);
}
