#include "strace.h"

int	launch_prog(t_trace *trace)
{
	int	ret = 0, fd = -1;

	trace->ppid = getpid();
	trace->pid = fork();
	if (trace->pid == -1)
	{
		ft_dprintf(2, "ft_strace: fork fail\n");
		ret = 1;
	}
	else if (trace->pid > 0) //parent
	{
		signal(SIGINT, &catch_sigint);
		ret = tracing(trace);
	}
	else //son
	{
		fd = open("/dev/null", O_WRONLY | O_CREAT, 0666);
		if (fd > 0)
			dup2(fd, 1);
		if (execve(trace->name, trace->args, trace->env) == -1)
		{
			ft_dprintf(2, "ft_strace: Can't execute\n", trace->name);
			ret = 2;
		}
		close(fd);
	}
	return (ret);
}
