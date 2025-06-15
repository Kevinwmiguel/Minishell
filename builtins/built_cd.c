#include "builtin.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	built_cd(char **args)
{
	char	*path;

	// If no argument, go to HOME
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else if (args[1][0] == '-' && args[1][1] == '\0') // cd -
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", path); // Print OLDPWD path like Bash does
	}
	else
		path = args[1]; // cd path

	if (chdir(path) != 0)
	{
		perror("cd"); // Print error if directory doesn't exist
		return (1);
	}

	// Optional: update PWD and OLDPWD in your shell environment
	return (0);
}
