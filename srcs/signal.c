#include "strace.h"

int	check_child_state(t_trace *trace, int action)
{
	int	sig;
	siginfo_t siginfo;

	if (WIFEXITED(trace->ret))
	{
		if (!trace->c)
		{
			if (!action)
				ft_printf(") = ?\n");
			ft_printf("+++ exited with %d +++\n", WEXITSTATUS(trace->ret));
		}
		return (1);
	}
	else if (WIFSTOPPED(trace->ret))
	{
		sig = WSTOPSIG(trace->ret);
		ft_bzero(&siginfo, sizeof(siginfo));
		if (ptrace(PTRACE_GETSIGINFO, trace->pid, NULL, &siginfo) != -1 &&
			!(siginfo.si_signo == SIGTRAP && siginfo.si_code != 0))
		{
			if (!trace->c)
				ft_printf("--- %d {si_signo=%d, si_code=%d, si_pid=%d, si_uid=%d} ---\n", sig, siginfo.si_signo, siginfo.si_code, siginfo.si_pid, siginfo.si_uid);
			trace->delivery_sig = sig;
			return (2);
		}
	}
	else if (WIFSIGNALED(trace->ret))
	{
		if (!trace->c)
		{
			ft_printf("+++ exited by %d", WTERMSIG(trace->ret));
			if (WCOREDUMP(trace->ret))
				ft_printf(" (core dumped)");
			ft_printf(" +++\n");
		}
		return (1);
	}
	return (0);
}

int	wait_child(t_trace *trace)
{
	if (sigprocmask(SIG_SETMASK, &trace->old, NULL))
		perror("sigprocmask SETMASK");
	if (waitpid(trace->pid, &trace->ret, WUNTRACED) == -1)
	{
		ft_dprintf(2, "ft_strace: waitpid fail\n");
		return (3);
	}
	if (sigprocmask(SIG_BLOCK, &trace->new, NULL))
		perror("sigprocmask BLOCK");
	return (0);
}

void	init_block_sig(t_trace *trace)
{
	sigemptyset(&trace->new);
	sigaddset(&trace->new, SIGHUP);
	sigaddset(&trace->new, SIGINT);
	sigaddset(&trace->new, SIGQUIT);
	sigaddset(&trace->new, SIGPIPE);
	sigaddset(&trace->new, SIGTERM);
	if (sigprocmask(SIG_BLOCK, &trace->new, &trace->old))
		perror("sigprocmask BLOCK");
}

void	catch_sigint(int signal)
{
	(void)signal;
	ptrace(PTRACE_DETACH, trace.pid, NULL, NULL);
	ft_dprintf(2, "ft_strace: Process %d detached\n", trace.pid);
	free_trace(&trace);
	exit(130);
}
