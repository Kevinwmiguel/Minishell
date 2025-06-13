/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 01:48:21 by kwillian          #+#    #+#             */
/*   Updated: 2025/06/13 03:12:59 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char **build_export(char **env)
{
    int i, j;
    char **formatted;
    char *equal, *name, *value;
    char *tmp1, *tmp2;
    int size;

    if (!env)
        return NULL;

    size = mlc_size(0, env);
    formatted = ft_calloc(size + 1, sizeof(char *));
    if (!formatted)
        return NULL;

    i = 0;
    j = 0;
    while (env[i])
    {
        equal = ft_strchr(env[i], '=');
        if (equal)
        {
            name = ft_substr(env[i], 0, equal - env[i] + 1);
            if (!name)
                break;

            tmp1 = ft_strjoin("\"", equal + 1);
            if (!tmp1)
            {
                free(name);
                break;
            }
            value = ft_strjoin(tmp1, "\"");
            free(tmp1);
            if (!value)
            {
                free(name);
                break;
            }

            tmp1 = ft_strjoin("declare -x ", name);
            free(name);
            if (!tmp1)
            {
                free(value);
                break;
            }

            tmp2 = ft_strjoin(tmp1, value);
            free(tmp1);
            free(value);
            if (!tmp2)
                break;

            formatted[j++] = tmp2;
        }
        else
        {
            formatted[j++] = ft_strjoin("declare -x ", env[i]);
            if (!formatted[j - 1])
                break;
        }
        i++;
    }
    formatted[j] = NULL;

    if (env[i]) // erro na alocação
    {
        while (j-- > 0)
            free(formatted[j]);
        free(formatted);
        return NULL;
    }
    return formatted;
}


