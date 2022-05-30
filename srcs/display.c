#include "strace.h"

static void add_hex_char(char *str, int *i, char c)
{
	char	*tmp;
	int		len;

	if (c == 0)
	{
		tmp = ft_strdup("\\0");
		len = 2;
	}
	else
	{
		tmp = ft_sprintf("\\%o", (int)c);
		len = ft_strlen(tmp);
	}
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

	if (trace.arch == 32)
	{
		if (trace.sys.code32 == 1 && trace.regs32.edx < (unsigned int)len
			&& (int)trace.regs32.edx >= 0)
			len = (int)trace.regs32.edx;
		else if ((trace.sys.code32 == 3 || trace.sys.code32 == 180) &&
			trace.regs32.eax < (unsigned int)len && (int)trace.regs32.eax >= 0)
			len = (int)trace.regs32.eax;
	}
	else
	{
		if (trace.sys.code64 == 1 && trace.regs64.rdx < (unsigned long)len
			&& (long)trace.regs64.rdx >= 0)
			len = (long)trace.regs64.rdx;
		else if ((trace.sys.code64 == 0 || trace.sys.code64 == 17) &&
			trace.regs64.rax < (unsigned long)len && (long)trace.regs64.rax >= 0)
			len = (long)trace.regs64.rax;
	}
	while (++i < len)
	{
		if (!str[i] && (trace.sys.code64 != 0 && trace.sys.code64 != 17))
			break;
		if (str[i] >= 0x07 && str[i] <= 0x0d)
			add_spec_char(buf, &y, str[i]);
		else if (!ft_isprint(str[i]) && str[i] >= 0)
			add_hex_char(buf, &y, str[i]);
		else if (str[i] >= 0)
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
		write(1, ", ...", 5);
	if (i)
		write(1, "]", 1);
}

int		display_args_64(enum e_type type, uint64_t reg, int space)
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

int		display_args_32(enum e_type type, uint32_t reg, int space)
{
	if (type == TNONE)
		return (1);
	if (space)
		write(1, ", ", 2);
	if (type == TINT)
		ft_printf("%d", reg);
	else if (type == TUINT)
		ft_printf("%u", reg);
	else if (type == TPTR)
	{
		if (!reg)
			ft_printf("NULL");
		else
			ft_printf("%#p", reg);
	}
	else if (type == TSTR)
		display_str_reg(&trace, reg);
	else if (type == TLSTR)
		display_lstr_reg(&trace, reg);
	return (0);
	
}

static void	display_syscall_64(t_trace *trace, int cont)
{
	if ((trace->sys.code64 != 0 && trace->sys.code64 != 17) && cont)
		return ;
	if (!trace->sys.name)
		ft_printf("syscall_%#llx(?)\n", trace->regs64.orig_rax);
	else if (cont)
	{
		if (!display_args_64(trace->sys.arg2, trace->regs64.rsi, 1))
			if (!display_args_64(trace->sys.arg3, trace->regs64.rdx, 1))
				if (!display_args_64(trace->sys.arg4, trace->regs64.r10, 1))
					if (!display_args_64(trace->sys.arg5, trace->regs64.r8, 1))
						display_args_64(trace->sys.arg6, trace->regs64.r9, 1);
	}
	else
	{
		ft_printf("%s(", trace->sys.name);
		if (!display_args_64(trace->sys.arg1, trace->regs64.rdi, 0))
			if ((trace->sys.code64 != 0 && trace->sys.code64 != 17) && !display_args_64(trace->sys.arg2, trace->regs64.rsi, 1))
				if (!display_args_64(trace->sys.arg3, trace->regs64.rdx, 1))
					if (!display_args_64(trace->sys.arg4, trace->regs64.r10, 1))
						if (!display_args_64(trace->sys.arg5, trace->regs64.r8, 1))
							display_args_64(trace->sys.arg6, trace->regs64.r9, 1);
	}
}

static void	display_syscall_32(t_trace *trace, int cont)
{
	if ((trace->sys.code32 != 3 && trace->sys.code32 != 180) && cont)
		return ;
	if (!trace->sys.name)
		ft_printf("syscall_%#x(?)\n", trace->regs32.orig_eax);
	else if (cont)
	{
		if (!display_args_32(trace->sys.arg2, trace->regs32.ecx, 1))
			if (!display_args_32(trace->sys.arg3, trace->regs32.edx, 1))
				if (!display_args_32(trace->sys.arg4, trace->regs32.esi, 1))
					if (!display_args_32(trace->sys.arg5, trace->regs32.edi, 1))
						display_args_32(trace->sys.arg6, trace->regs32.ebp, 1);
	}
	else
	{
		ft_printf("%s(", trace->sys.name);
		if (!display_args_32(trace->sys.arg1, trace->regs32.ebx, 0))
			if ((trace->sys.code32 != 3 && trace->sys.code32 != 180) && !display_args_32(trace->sys.arg2, trace->regs32.ecx, 1))
				if (!display_args_32(trace->sys.arg3, trace->regs32.edx, 1))
					if (!display_args_32(trace->sys.arg4, trace->regs32.esi, 1))
						if (!display_args_32(trace->sys.arg5, trace->regs32.edi, 1))
							display_args_32(trace->sys.arg6, trace->regs32.ebp, 1);
	}
}

void	display_syscall(t_trace *trace, int cont)
{
	if (trace->arch == 64)
		display_syscall_64(trace, cont);
	else if (trace->arch == 32)
		display_syscall_32(trace, cont);
}

void	display_ret_syscall_32(enum e_type type, uint32_t reg)
{
	if (type == TNONE)
		return ;
	if (type == TINT)
		ft_printf(") \t= %d\n", reg);
	else if (type == TPTR)
		ft_printf(") \t= %#p\n", reg);
}

void	display_ret_syscall_64(enum e_type type, uint64_t reg)
{
	if (type == TNONE)
		return ;
	if (type == TINT)
		ft_printf(") \t= %ld\n", reg);
	else if (type == TPTR)
		ft_printf(") \t= %#lp\n", reg);
}
