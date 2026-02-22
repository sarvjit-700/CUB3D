/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 22:00:34 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/22 22:00:34 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *new_str;
    size_t  len1;
    size_t  len2;
    size_t  i;
    size_t  j;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i] != '\0')
    {
        new_str[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
    free(s1);
	return (new_str);
}

int     check_empty_lines(char *raw_map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (raw_map[i] == '\n')
        i++;
    while (raw_map[i])
    {
        if (raw_map[i] == '\n')
        {
            j = i + 1;
            while (raw_map[j] == 32 || raw_map[j] == '\t' || raw_map[j] == '\r')
                j++;
            if (raw_map[j] == '\n' || raw_map[j] == '\0')
                return (1);
        }
        i++;
    }
    return (0);
}