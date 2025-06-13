
#include "../../includes/utils.h"

void free_dptr(char **dptr)
{
    int i = 0;
    if (!dptr)
        return;
    while (dptr[i])
    {
        free(dptr[i]);
        i++;
    }
    free(dptr);
}

int	mlc_size(int j, char **mlc)
{
	while (mlc[j])
		j++;
	return (j);
}

static int	count_strings(char **arr)
{
	int i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

// Duplica um array de strings, tratando NULL e falha de malloc
char	**dptr_dup(char **arr)
{
	char	**copy;
	int		i;
	int		len;

	if (!arr)
		return (NULL);
	len = count_strings(arr);
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = strdup(arr[i]);
		if (!copy[i])
		{
			// Limpa tudo em caso de falha
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[len] = NULL;
	return (copy);
}
