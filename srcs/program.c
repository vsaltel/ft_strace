#include "strace.h"

static int	init_tracing(t_trace *trace)
{
	signal(SIGINT, &catch_sigint);
	ptrace(PTRACE_SEIZE, trace->pid, NULL, NULL);
	ptrace(PTRACE_INTERRUPT, trace->pid, NULL, NULL);
	init_block_sig(trace);
	if (waitpid(trace->pid, &trace->ret, WUNTRACED) == -1)
	{
		ft_dprintf(2, "ft_strace: waitpid fail\n");
		return (3);
	}
	if (check_child_state(trace, 1) == 1)
		return (1);
	return (0);
}

int	launch_prog(t_trace *trace)
{
	int	ret = 0, fd = -1;

	trace->ppid = getpid();
	trace->pid = fork();
	if (trace->pid == -1)
	{
		ft_dprintf(2, "ft_strace: fork fail\n");
		ret = 1;
	}
	else if (trace->pid > 0)
	{
		if ((ret = init_tracing(trace)))
			return (ret);
		ret = tracing(trace);
	}
	else //son
	{
		if (execve(trace->name, trace->args, trace->env) == -1)
		{
			ft_dprintf(2, "ft_strace: Can't execute\n", trace->name);
			ret = 2;
		}
		close(fd);
	}
	return (ret);
}
