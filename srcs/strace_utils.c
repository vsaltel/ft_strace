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

t_syscall get_syscall(t_trace *trace)
{
	int			i = -1;
	t_syscall	sys;

	while (g_syscall[++i].name)
	{
		if (trace->regs.orig_rax == (long long unsigned int)g_syscall[i].code || !g_syscall[i].name)
		{
			sys = g_syscall[i];
			break;
		}
	}
	return (sys);
}
