#include "strace.h"

t_trace		trace;

int	main(int argc, char **argv, char **env)
{
	int		ret;

	if (argc < 2)
	{
		ft_dprintf(2, "ft_strace: must have PROG [ARGS]\n");
		return (0);
	}
	init_trace(&trace, argc, argv, env);
	if (!get_path(&trace))
		return (1);
	ret = launch_prog(&trace);
	free_trace(&trace);
	return (ret);
}
