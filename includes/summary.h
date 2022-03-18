#ifndef SUMMARY_H
# define SUMMARY_H

# include "sys/time.h"

typedef struct			s_sum
{
	int				code;
	char			*name;
	unsigned int	use_count;
	unsigned int	err_count;
	struct timeval	time_spend;
	struct s_sum	*next;
}						t_sum;

#endif
