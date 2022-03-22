#include "strace.h"

static int	if_stopped(t_trace *trace, int action)
{
	int	sig;
	siginfo_t siginfo;

	sig = WSTOPSIG(trace->ret);
	ft_bzero(&siginfo, sizeof(siginfo));
	if (ptrace(PTRACE_GETSIGINFO, trace->pid, NULL, &siginfo) != -1 &&
		!(siginfo.si_signo == SIGTRAP && siginfo.si_code != 0))
	{
		if (!trace->c && action)
			ft_printf(") = ?\n");
		if (!trace->c && siginfo.si_pid != -1)
			ft_printf("--- %d {si_signo=%d, si_code=%d, si_pid=%d, si_uid=%d} ---\n", sig, siginfo.si_signo, siginfo.si_code, siginfo.si_pid, siginfo.si_uid);
		else if (!trace->c)
			ft_printf("--- %d {si_signo=%d, si_code=%d, si_addr=%#llx} ---\n", sig, siginfo.si_signo, siginfo.si_code, siginfo.si_addr);
		trace->delivery_sig = sig;
		return (2);
	}
	return (0);
}

int	check_child_state(t_trace *trace, int action)
{
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
	else if (WIFSTOPPED(trace->ret) && if_stopped(trace, action))
		return (2);
	else if (WIFSIGNALED(trace->ret))
	{
		if (!trace->c)
		{
			ft_printf("+++ killed by %d", WTERMSIG(trace->ret));
			if (WCOREDUMP(trace->ret))
				ft_printf(" (core dumped)");
			ft_printf(" +++\n");
		}
		return (1);
	}
	return (0);
}

int	wait_child(t_trace *trace, int action)
{
	int	ret = 0;
	struct rusage usage;

	ft_bzero(&usage, sizeof(usage));
	if (sigprocmask(SIG_SETMASK, &trace->old, NULL))
		perror("sigprocmask SETMASK");
	ret = wait4(trace->pid, &trace->ret, WUNTRACED, &usage);
	if (sigprocmask(SIG_BLOCK, &trace->new, NULL))
		perror("sigprocmask BLOCK");
	if (ret == -1)
	{
		ft_dprintf(2, "ft_strace: waitpid fail\n");
		return (3);
	}
	if (action)
	{
		ft_bzero(&trace->bef, sizeof(trace->bef));
		ft_bzero(&trace->aft, sizeof(trace->aft));
		trace->bef = usage.ru_stime;
	}
	if (!action)
		trace->aft = usage.ru_stime;
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
	if (trace.c)
		display_summary(&trace);
	free_trace(&trace);
	exit(130);
}
