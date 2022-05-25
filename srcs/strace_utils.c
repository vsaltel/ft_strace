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

int		get_architecture(t_trace *trace)
{
	int fd;
	int	ret = 0;
	int	nb;
	Elf32_Ehdr	hdr;

	if ((fd = open(trace->name, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "ft_strace: %s is not readable\n", trace->name);
		return (-1);
	}
	if ((nb = read(fd, &hdr, sizeof(hdr))) != -1)
	{
		if ((size_t)nb < sizeof(Elf32_Ehdr) || ft_memcmp(&hdr, "\x7f\x45\x4C\x46", 4))
		{
			ft_dprintf(2, "ft_strace: %s is not a ELF file\n", trace->name);
			ret = -3;
		}
		else if (hdr.e_ident[EI_CLASS] == ELFCLASS32)
			trace->arch = 32;
		else if (hdr.e_ident[EI_CLASS] == ELFCLASS64)
			trace->arch = 64;
		else
		{
			ft_dprintf(2, "ft_strace: %s Architecture is not handle\n", trace->name);
			ret = -4;
		}
	}
	else
		ret = -2;
	close(fd);
	return (ret);
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
