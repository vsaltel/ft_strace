#include "strace.h"
#include "syscall_name.h"

static int	display_args(enum e_type type, uint64_t reg, int space)
{
	if (type == TNONE)
		return (1);
	if (space)
		write(1, ", ", 2);
	if (type == TINT)
		ft_printf("%ld", reg);
	else if (type == TUINT)
		ft_printf("%lu", reg);
	else if (type == TPTR)
		ft_printf("%#lp", reg);
	else if (type == TSTR)
		ft_printf("%#lp", reg);
	return (0);
}

void	display_syscall(t_trace *trace)
{
	//rdi, rsi, rdx, r10, r8, r9
	t_syscall	sys;
	int			i = -1;

	while (g_syscall[++i].name)
	{
		if (trace->regs.orig_rax == (long long unsigned int)g_syscall[i].code)
		{
			sys = g_syscall[i];
			break;
		}
	}
	if (i > NB_SYSCALL)
		return ;
	ft_printf("%s(", sys.name);
	if (!display_args(sys.arg1, trace->regs.rdi, 0))
		if (!display_args(sys.arg2, trace->regs.rsi, 1))
			if (!display_args(sys.arg3, trace->regs.rdx, 1))
				if (!display_args(sys.arg4, trace->regs.r10, 1))
					if (!display_args(sys.arg5, trace->regs.r8, 1))
						display_args(sys.arg6, trace->regs.r9, 1);
}
