#include "strace.h"

int	launch_prog(t_trace *trace)
{
	int	ret = 0;

	trace->pid = fork();
	ptrace(PTRACE_SEIZE, trace->pid, NULL, NULL);
	ptrace(PTRACE_INTERRUPT, trace->pid, NULL, NULL);
	if (trace->pid == -1)
	{
		ft_dprintf(2, "ft_strace: fork fail\n");
		ret = 1;
	}
	else if (trace->pid > 0) //parent
		ret = tracing(trace);
	else //son
	{
		if (execve(trace->name, trace->args, trace->env) == -1)
		{
			ft_dprintf(2, "ft_strace: Can't execute\n", trace->name);
			ret = 2;
		}
	}
	return (ret);
}
