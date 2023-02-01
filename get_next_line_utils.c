/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:03 by chris             #+#    #+#             */
/*   Updated: 2023/02/01 15:01:32 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	if (end == '\n' && *(s + i) == '\n')
	{
		return (i + 1);
	}
	return (i);
}


int	line_counter(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (*str == '\n')
			i++;
		str++;
	}
	return (i);
}

void	cpy_len(const char *src, char *dest, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		*dest = *src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
}

char	*ft_strdup(const char *s, char end)
{
	char	*dup;
	char	*dup_start;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)s, end);
	dup = malloc((len * sizeof(char)) + 1);
	if (dup == NULL)
		return (NULL);
	dup_start = dup;
	cpy_len(s, dup, len);
	return (dup_start);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;

	joined = (char *) malloc((ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1)
			* sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		cpy_len(s1, joined, ft_strlen(s1, '\0'));
	cpy_len(s2, joined + ft_strlen(s1, '\0'), ft_strlen(s2, '\0'));
	if (s1 != NULL)
		free(s1);
	free(s2);
	return (joined);
}

char	*reduce_tmp(char *str, int start)
{
	char	*new_tmp;
	int		i;
	//printf("reduce_tmp:%i", start);
	if (ft_strlen(&str[start], '\0') == 0)
	{
		free(str);
		return (NULL);
	}
	//printf("tmp2:%s", &str[start]);
	new_tmp = (char *) malloc((ft_strlen(&str[start], '\0') + 1)
			* sizeof(char));
	if (new_tmp == NULL)
		return (NULL);
	i = 0;
	while (str[start] != '\0')
	{
		new_tmp[i] = str[start];
		start++;
		i++;
	}
	new_tmp[i] = '\0';
	free(str);
	return (new_tmp);
}


int read_new_line(char **tmp, int fd)
{
	char 	*buf;
	int		is_eof;

is_eof=-100;
	while (line_counter(*tmp) == 0 && is_eof != 0)
	{
		if (is_eof < BUFFER_SIZE && is_eof != -100)
			break;
		is_eof = fill_buffer(&buf, fd);
		if (is_eof == -1)
		{
			free (*tmp);
			*tmp = NULL;
			return (-1);
		}
		if (is_eof != 0)
			*tmp = ft_strjoin(*tmp, buf);
//		if (is_eof < BUFFER_SIZE)
//fill_buffer(&buf, fd);
	}
	return (is_eof);
}