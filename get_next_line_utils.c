/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:03 by chris             #+#    #+#             */
/*   Updated: 2023/01/21 21:33:24 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s, char end)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*(s + i) != end && *(s + i) != '\0')
	{
		i++;
	}
	if (end == '\n' && *(s + i) == '\0')
	{
		return (0);
	}
	if (end == '\n' && *(s + i) == '\n' && i == 0)
	{
		return (-1);
	}
	return (i);
}

void	cpy_until_end(const char *src, char *dest, int *i, char end)
{
	while (src[*i] != end)
	{
		dest[*i] = src[*i];
		*i = *i + 1;
	}
}

char	*ft_strdup(const char *s, char end)
{
	char	*dup;
	char	*dup_start;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)s, end);
	if (len == -1)
		len = 1;
	else if (end == '\n')
		len++;
	dup = malloc((len * sizeof(char)) + 1);
	if (dup == NULL)
		return (NULL);
	dup_start = dup;
	cpy_until_end(s, dup, &i, end);
	if (s[i] == '\n')
	{
		dup[i] = '\n';
		i++;
	}
	dup[i] = '\0';
	return (dup_start);
}

char	*ft_strjoin(char *s1, char *s2, int start_s2)
{
	char	*joined;
	int		i;
	int		j;

	joined = (char *) malloc((ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1)
			* sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		cpy_until_end(s1, joined, &i, '\0');
	j = start_s2;
	while (s2[j] != '\0')
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	if (s1 != NULL)
		free(s1);
	free(s2);
	return (joined);
}
