#include "strace.h"

void	init_trace(t_trace *trace, int argc, char **argv, char **env)
{
	trace->name = NULL;
	trace->args = NULL;
	trace->env = NULL;
	trace->pid = 0;
	trace->ret = 0;
	if (argc > 1)
	{
		trace->name = argv[1];
		trace->args = &argv[1];
	}
	if (env)
		trace->env = env;
}

void	catch_sigint(int signal)
{
	kill(trace.pid, signal);
}

char	*get_stack_file(t_trace *trace)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("/proc/");
	tmp = ft_itoa(trace->pid);
	str = ft_strfjoin(str, tmp, str);
	free(tmp);
	str = ft_strfjoin(str, "/stack", str);
	trace->stack_file = str;
	return (str);
}
