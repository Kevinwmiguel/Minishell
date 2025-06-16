#include "builtin.h"

int	built_cd(char **args)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
