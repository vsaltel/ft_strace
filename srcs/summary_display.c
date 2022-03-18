#include "strace.h"

void	update_summary(t_trace *trace)
{
	trace->sys.use_count++;
	if ((long)trace->regs.rax < 0)
		trace->sys.err_count++;
}

void	display_summary(t_trace *trace)
{
	(void)trace;
	ft_printf("%6s %11s %11s %9s %9s %-16s\n", "% time", "seconds", "usecs/call", "calls", "errors", "syscall");
	ft_printf("%6c %11c %11c %9c %9c %16c\n", '-', '-', '-', '-', '-', '-');
}
