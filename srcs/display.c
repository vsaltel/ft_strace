#include "strace.h"

static void add_hex_char(char *str, int *i, char c)
{
	char	*tmp;
	int		len;

	tmp = ft_sprintf("\\0%o", (int)c);
	len = ft_strlen(tmp);
	ft_memcpy(str + *i, tmp, len);
	*i += len;
	free(tmp);
}

static void add_spec_char(char *str, int *i, char c)
{
	str[*i] = '\\';
	(*i)++;
	if (c == 0x07)
		str[*i] = 'a';
	else if (c == 0x08)
		str[*i] = 'b';
	else if (c == 0x09)
		str[*i] = 't';
	else if (c == 0x0a)
		str[*i] = 'n';
	else if (c == 0x0b)
		str[*i] = 'v';
	else if (c == 0x0c)
		str[*i] = 'f';
	else if (c == 0x0d)
		str[*i] = 'r';
	(*i)++;
}

static void	print_escaped_str(char *str)
{
	char	buf[BUFF_SIZE];
	int		i = -1;
	int		y = 0;
	int		len = 32;

	if (trace.sys.code == 1 &&
		trace.regs.rdx < (unsigned int)len && (int)trace.regs.rdx > 0)
		len = (int)trace.regs.rdx;
	while (str[++i] && i < len)
	{
		if (str[i] >= 0x07 && str[i] <= 0x0d)
			add_spec_char(buf, &y, str[i]);
		else if (!ft_isprint(str[i]) && str[i] > 0)
			add_hex_char(buf, &y, str[i]);
		else if (str[i] > 0)
			buf[y++] = str[i];
	}
	buf[y] = '\0';
	if (i >= 32)
		ft_printf("\"%s\"...", buf);
	else
		ft_printf("\"%s\"", buf);
}

void	display_str_reg(t_trace *trace, uint64_t reg)
{
	char			buf[BUFF_SIZE];
	unsigned long	ret;
	unsigned long	*tmp;
	unsigned int	i = 0;

	ft_bzero(buf, BUFF_SIZE);
	tmp = (unsigned long *)buf;
	while (i < 5)
	{
		ret = ptrace(PTRACE_PEEKDATA, trace->pid, reg + (i * 8), NULL);
		*tmp = ret;
		i++;
		tmp = (unsigned long *)(buf + (i * 8));
	}
	print_escaped_str(buf);
}

void	display_lstr_reg(t_trace *trace, uint64_t reg)
{
	unsigned int	i = 0;
	unsigned int	count = 0;
	unsigned long	ret = 1;

	while (ret && count < 10)
	{
		ret = ptrace(PTRACE_PEEKDATA, trace->pid, reg + (i * 8), NULL);
		if (++count == 10)
			break;
		if (ret)
		{
			if (!i)
				write(1, "[", 1);
			else
				write(1, ", ", 2);
			display_str_reg(trace, ret);
			i++;
		}
	}
	if (count == 10)
		write(1, "...", 3);
	if (i)
		write(1, "]", 1);
}

int		display_args(enum e_type type, uint64_t reg, int space)
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
	{
		if (!reg)
			ft_printf("NULL");
		else
			ft_printf("%#lp", reg);
	}
	else if (type == TSTR)
		display_str_reg(&trace, reg);
	else if (type == TLSTR)
		display_lstr_reg(&trace, reg);
	return (0);
	
}

void	display_syscall(t_trace *trace)
{
	if (!trace->sys.name)
		ft_printf("syscall_%#llx(?)\n", trace->regs.orig_rax);
	else
	{
		ft_printf("%s(", trace->sys.name);
		if (!display_args(trace->sys.arg1, trace->regs.rdi, 0))
			if (!display_args(trace->sys.arg2, trace->regs.rsi, 1))
				if (!display_args(trace->sys.arg3, trace->regs.rdx, 1))
					if (!display_args(trace->sys.arg4, trace->regs.r10, 1))
						if (!display_args(trace->sys.arg5, trace->regs.r8, 1))
							display_args(trace->sys.arg6, trace->regs.r9, 1);
	}
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
