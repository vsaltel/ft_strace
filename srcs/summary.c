#include "strace.h"

t_sum	*search_sum(t_sum *deb, long long unsigned int code)
{
	while (deb)
	{
		if (deb->code == code)
			return (deb);
		deb = deb->next;
	}
	return (NULL);
}

t_sum	*new_sum(t_sum **deb, long long unsigned int code, char *name)
{
	t_sum	*new;

	if (!(new = malloc((sizeof(t_sum)))))
		return (NULL);
	new->code = code;
	new->name = ft_strdup(name);
	new->use_count = 0;
	new->err_count = 0;
	new->time_spend = 0.0;
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

void	update_summary_count(t_trace *trace, long reg)
{
	t_sum *sum;

	if (!(sum = search_sum(trace->summary, trace->sys.code64)))
		sum = new_sum(&trace->summary, trace->sys.code64, trace->sys.name);
	sum->use_count++;
	if (reg < 0)
		sum->err_count++;
}

void	update_summary_time(t_trace *trace)
{
	t_sum	*sum;
	float	tmp_aft, tmp_bef;

	if (!(sum = search_sum(trace->summary, trace->sys.code64)))
		sum = new_sum(&trace->summary, trace->sys.code64, trace->sys.name);
	tmp_bef = trace->bef.tv_sec + (trace->bef.tv_usec * 0.000001);
	tmp_aft = trace->aft.tv_sec + (trace->aft.tv_usec * 0.000001);
	sum->time_spend += tmp_aft - tmp_bef;
}

t_sum	*sort_summary_by_time(t_sum **sum)
{
	t_sum *curr;
	t_sum *tmp = NULL;
	t_sum *bef = NULL;

	if (!sum || !*sum)
		return (NULL);
	curr = *sum;
	while (curr && curr->next)
	{
		if (curr->time_spend < curr->next->time_spend)
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			tmp->next = curr;
			if (curr == *sum)
				*sum = tmp;
			else
				bef->next = tmp;
			bef = NULL;
			curr = *sum;
		}
		else
		{
			bef = curr;
			curr = curr->next;
		}
	}
	return (*sum);
}

void	display_summary(t_trace *trace)
{
	t_sum			*sum;
	unsigned int	use_max = 0;
	unsigned int	err_max = 0;
	float			time_max= 0.0;

	sort_summary_by_time(&trace->summary);
 	sum = trace->summary;
	while (sum)
	{
		time_max += sum->time_spend;
		sum = sum->next;
	}
	ft_printf("%6s %11s %11s %9s %9s %-16s\n", "% time", "seconds", "usecs/call", "calls", "errors", "syscall");
	ft_printf("%s\n", "------ ----------- ----------- --------- --------- ----------------");
	sum = trace->summary;
	while (sum)
	{
		use_max += sum->use_count;
		err_max += sum->err_count;
		ft_printf("%6.2f %11f %11d %9d %9.0d ",
				time_max ? (sum->time_spend * 100) / time_max : 0, sum->time_spend,
				sum->use_count ? ((int)(sum->time_spend * 1000000) / sum->use_count) : 0,
				sum->use_count, sum->err_count);
		if (!sum->name)
			ft_printf("syscall_%#llx\n", sum->code);
		else
			ft_printf("%-16s\n", sum->name);
		sum = sum->next;
	}
	ft_printf("%s\n", "------ ----------- ----------- --------- --------- ----------------");
	ft_printf("%6.2f %11f %11.0d %9d %9.0d %-16s\n", 100.00, time_max,
			use_max ? ((int)(time_max * 1000000) / use_max) : 0, use_max, err_max, "total");
}
