#include "strace.h"

void	init_trace(t_trace *trace, int argc, char **argv, char **env)
{
	trace->name = NULL;
	trace->args = NULL;
	trace->env = NULL;
	trace->pid = 0;
	trace->ret = 0;
	trace->ready = 0;
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
