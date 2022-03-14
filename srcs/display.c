#include "strace.h"

int		display_args(enum e_type type, uint64_t reg, int space)
{
	//int		fd;
	//long	tmp;
	if (type == TNONE)
		return (1);
	if (space)
		write(1, ", ", 2);
	if (type == TINT)
		ft_printf("%ld", reg);
	else if (type == TUINT)
		ft_printf("%lu", reg);
	else if (type == TPTR)
	{
		if (!reg)
			ft_printf("NULL");
		else
			ft_printf("%#lp", reg);
	}
	else if (type == TSTR)
		ft_printf("%#lp", reg);
	return (0);
	/*
	if ((fd = open(trace->stack_file, O_RDONLY)) > 0)
	{
		lseek(fd, trace->regs.rsp - (sizeof(tmp) * 3), SEEK_SET);
		read(fd, &tmp, sizeof(tmp));
		ft_printf(" 0x%lx", tmp);
		read(fd, &tmp, sizeof(tmp));
		ft_printf(" 0x%lx", tmp);
		read(fd, &tmp, sizeof(tmp));
		ft_printf(" 0x%lx", tmp);
		close(fd);
	}
	*/
}

void	display_syscall(t_trace *trace)
{
	//rdi, rsi, rdx, r10, r8, r9
	
	ft_printf("%s(", trace->sys.name);
	if (!display_args(trace->sys.arg1, trace->regs.rdi, 0))
		if (!display_args(trace->sys.arg2, trace->regs.rsi, 1))
			if (!display_args(trace->sys.arg3, trace->regs.rdx, 1))
				if (!display_args(trace->sys.arg4, trace->regs.r10, 1))
					if (!display_args(trace->sys.arg5, trace->regs.r8, 1))
						display_args(trace->sys.arg6, trace->regs.r9, 1);
}

void	display_ret_syscall(enum e_type type, uint64_t reg)
{
	if (type == TNONE)
		return ;
	if (type == TINT)
		ft_printf(") = %ld\n", reg);
	else if (type == TPTR)
		ft_printf(") = %#lp\n", reg);
}
