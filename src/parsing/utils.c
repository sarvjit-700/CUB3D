/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:19:01 by ssukhija          #+#    #+#             */
/*   Updated: 2026/02/24 13:19:01 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (ft_strchr("01NSWE ", c))
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	check_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (!len || len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1, s2);
	free(s1);
	return (new_str);
}