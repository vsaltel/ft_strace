#include "strace.h"

t_sum	*search_sum(t_sum *deb, char *str)
{
	while (deb)
	{
		if (!ft_strcmp(deb->name, str))
			return (deb);
		deb = deb->next;
	}
	return (NULL);
}

t_sum	*new_sum(t_sum **deb, int code, char *name)
{
	t_sum	*new;

	if (!(new = malloc((sizeof(t_sum)))))
		return (NULL);
	new->code = code;
	new->name = ft_strdup(name);
	new->use_count = 0;
	new->err_count = 0;
	new->time_spend.tv_sec = 0;
	new->time_spend.tv_usec = 0;
	new->next = NULL;
	if (!*deb)
		*deb = new;
	else
	{
		new->next = *deb;
		*deb = new;
	}
	return (new);
}

void	free_sum(t_sum **sum)
{
	t_sum *curr = *sum;
	t_sum *tmp;

	while (curr)
	{
		tmp = curr->next;
		free(curr->name);
		free(curr);
		curr = tmp;
	}
	sum = NULL;
}

void	update_summary(t_trace *trace)
{
	t_sum *sum;

	if (!(sum = search_sum(trace->summary, trace->sys.name)))
		sum = new_sum(&trace->summary, trace->sys.code, trace->sys.name);
	sum->use_count++;
	if ((long)trace->regs.rax < 0)
		sum->err_count++;
	sum->time_spend.tv_sec += trace->aft.tv_sec - trace->bef.tv_sec;
	sum->time_spend.tv_usec += trace->aft.tv_usec - trace->bef.tv_usec;
}

void	display_summary(t_trace *trace)
{
	t_sum			*sum = trace->summary;
	unsigned int	use_max = 0;
	unsigned int	err_max = 0;
	float			time_tmp;

	ft_printf("%6s %11s %11s %9s %9s %-16s\n", "% time", "seconds", "usecs/call", "calls", "errors", "syscall");
	ft_printf("%s\n", "------ ----------- ----------- --------- --------- ----------------");
	while (sum)
	{
		use_max += sum->use_count;
		err_max += sum->err_count;
		ft_printf("%d %d\n", sum->time_spend.tv_usec, sum->time_spend.tv_sec);
		time_tmp = 0;
		time_tmp += (sum->time_spend.tv_usec * 0.000001);
		//time_tmp += sum->time_spend.tv_sec;
		ft_printf("%6.2f %11f %11d %9d %9.0d %-16s\n", time_tmp, time_tmp, 0, sum->use_count, sum->err_count, sum->name);
		sum = sum->next;
	}
	ft_printf("%s\n", "------ ----------- ----------- --------- --------- ----------------");
	ft_printf("%6.2f %11f %11.0d %9d %9.0d %-16s\n", 100.00, 0.0, 0, use_max, err_max, "total");
}
