/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:08 by chris             #+#    #+#             */
/*   Updated: 2023/02/01 14:43:21 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*get_new_line_from_tmp(char **tmp)
{
	char	*new_line;

	//if (line_counter(*tmp) == 0)
	//	return (*tmp);
	new_line = ft_strdup(*tmp, '\n');
	*tmp = reduce_tmp(*tmp, ft_strlen(*tmp, '\n') + 0);
	return (new_line);
}

int	fill_buffer(char **buf, int fd)
{
	int		is_eof;

	*buf = (char *) malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (*buf == NULL)
		return (0);
	is_eof = read(fd, *buf, BUFFER_SIZE);
	if (is_eof < 0 || is_eof == 0)
	{
		free(*buf);
		return (is_eof);
	}
	(*buf)[is_eof] = '\0';
	return (is_eof);
}

char	*get_last_line(char **tmp, char **new_line)
{
	*new_line = ft_strjoin(NULL, *tmp);
	*tmp = NULL;
	if (**new_line == '\0')
	{
		free(*new_line);
		return (NULL);
	}
	return (*new_line);
}

char	*get_next_line(int fd)
{
	static char	*tmp = NULL;
	char		*new_line;
	int			is_eof;

	new_line = NULL;
	if (line_counter(tmp) != 0)
		new_line = get_new_line_from_tmp(&tmp);
	//else
	//{
	//	new_line = tmp;
	//	tmp = NULL;
	//}
	else
	{
		is_eof = read_new_line(&tmp, fd);
		if (is_eof == -1)
		{
			return (NULL);
		}
	}
	if (new_line == NULL && ((is_eof == 0 && ft_strlen(tmp, '\0') != 0) || is_eof != 0))
	{
		new_line = get_new_line_from_tmp(&tmp);
		//if (is_eof == 0 && line_counter(tmp) == 0)
		//	tmp = NULL;
	}
	//printf("tmp:%s", tmp);
	return (new_line);
}

/*
int	main(void)
{
	//printf("%i", BUFFER_SIZE);

	int fd;
	int readd;
	char *next_line;
	int	cnt_line = 0;
	int loop = 6;

	//fd = 100;
	//printf("get_next_line:%s\n", get_next_line(fd));

	fd = open("./file.txt", O_RDONLY);
	//readd = read(fd, next_line, 10);
	//printf("fd:%i", readd);
	//fd = open("file.txt", O_RDONLY);
	
	
	//while (cnt_line != loop)
	//{
	//next_line = get_next_line(fd);
	////if (next_line != NULL)
	//	printf("get_next_line:%s\n", next_line);
	////if (next_line != NULL)
	//	cnt_line++;
	//}
	next_line = get_next_line(fd);
	printf("get_next_line:%s\n", next_line);
	printf("nstrcmp:%i\n", strcmp(next_line, "\n"));
	//free(next_line);

	next_line = get_next_line(fd);
	printf("get_next_line:%s\n", next_line);
	printf("nstrcmp:%i\n", next_line == NULL);
	//printf("get_next_line:%s\n", get_next_line(fd));
	//printf("fd:%d\n", fd);

	//	close(fd);
	//fd = open("/Users/cgodecke/francinette/tests/get_next_line/fsoares/multiple_nl.txt", O_RDONLY);

	//printf("get_next_line:%s\n", get_next_line(fd));
			//printf("fd:%d\n", fd);

	printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));
	close(fd);
	//printf("%i bytes were read.\n", sz);
	//printf("Content:%c\n", buf[3]);


}
*/