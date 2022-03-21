#ifndef SUMMARY_H
# define SUMMARY_H

# include "sys/time.h"

typedef struct			s_sum
{
	long long unsigned int	code;
	char					*name;
	unsigned int			use_count;
	unsigned int			err_count;
	float					time_spend;
	struct s_sum			*next;
}						t_sum;

#endif
