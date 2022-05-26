#include "strace.h"

void	init_trace(t_trace *trace, int argc, char **argv, char **env)
{
	trace->name = NULL;
	trace->args = NULL;
	trace->env = NULL;
	trace->summary = NULL;
	trace->pid = 0;
	trace->ret = 0;
	trace->c = 0;
	trace->detach = 0;
	trace->ch_arch = 0;
	trace->arch = 64;
	trace->delivery_sig = 0;
	if (argc > 1)
	{
		if (!ft_strcmp(argv[1], "-c"))
		{
			trace->c = 1;
			argv++;
		}
		trace->name = ft_strdup(argv[1]);
		trace->args = &argv[1];
	}
	if (env)
		trace->env = env;
}

void	free_trace(t_trace *trace)
{
	if (trace->summary)
		free_sum(&trace->summary);
	if (trace->name)
		free(trace->name);
}

t_syscall get_syscall(t_trace *trace)
{
	int			i = -1;
	t_syscall	sys;
	int			cmp;

	if (trace->arch == 64)
		cmp = trace->regs64.orig_rax;
	else
		cmp = trace->regs32.orig_eax;
	sys.name = NULL;
	while (g_syscall[++i].name)
	{
		if ((trace->arch == 32 && cmp == g_syscall[i].code32) ||
			(trace->arch == 64 && cmp == g_syscall[i].code64))
		{
			sys = g_syscall[i];
			break;
		}
	}
	if (!sys.name)
	{
		if (trace->arch == 32)
			sys.code32 = cmp;
		else
			sys.code64 = cmp;
	}
	return (sys);
}
