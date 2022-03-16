#include "strace.h"

char	*get_path(t_trace *trace)
{
	char	*ret = NULL;
	char	**split_path;
	int		i = -1;

	if (trace->name[0] == '/' || trace->name[0] == '.')
		return (trace->name);
	if ((split_path = ft_strsplit(getenv("PATH"), ':')))
	{
		while (split_path[++i])
		{
			ret = ft_strjoint(split_path[i], "/", trace->name);
			if (!access(ret, F_OK) && !access(ret, R_OK) && !access(ret, X_OK))
				break;
			else
				ft_strdel(&ret);
		}
	}
	ft_tabfree(split_path);
	if (!ret)
		ft_dprintf(2, "ft_strace: Can't stat '%s': No such file or directory\n", trace->name);
	free(trace->name);
	trace->name = ret;
	return (ret);
}
