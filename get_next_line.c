/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:08 by chris             #+#    #+#             */
/*   Updated: 2023/01/31 11:03:37 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*get_new_line_from_buffer(char **tmp)
{
	char	*new_line;

	new_line = ft_strdup(*tmp, '\n');
	if (ft_strlen(*tmp, '\n') == -1)
		*tmp = ft_strjoin(NULL, *tmp, 1);
	else
		*tmp = ft_strjoin(NULL, *tmp, ft_strlen(*tmp, '\n') + 1);
	return (new_line);
}

void	*fill_buffer(char **buf, int *is_eof, int *cnt_read, int fd)
{
	*buf = (char *) malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (*buf == NULL)
		return (NULL);
	*is_eof = read(fd, *buf, BUFFER_SIZE - 0);
	*cnt_read = *cnt_read + 1;
	if (*is_eof != -1)
		(*buf)[*is_eof] = '\0';
	return ((void *) 1);
}

void	*read_new_line(char **tmp, int *is_eof, int *cnt_read, int fd)
{
	char	*buf;

	while ((ft_strlen(*tmp, '\n') == 0
			&& (*is_eof == BUFFER_SIZE || *tmp == NULL)))
	{
		buf = NULL;
		if (fill_buffer(&buf, is_eof, cnt_read, fd) == NULL)
			return (NULL);
		if (((*is_eof == 0 && *tmp == NULL) || *is_eof == -1))
		{
			if (*is_eof != -1 && *tmp != NULL )
			{
				if (*cnt_read > 1)
					free(*tmp);
				*tmp = NULL;
			}
			if (*is_eof == -1)
			{
				printf("XXXXXXXXXX");
				bzero(buf, BUFFER_SIZE+1);
				*cnt_read = 0;
				if (*tmp != NULL)
					free (*tmp);
				*tmp = NULL;
			}
			free(buf);
			
			return (NULL);
		}
		*tmp = ft_strjoin(*tmp, buf, 0);
	}
	return ((void *)1);
}

char	*get_last_line(char **tmp, char **new_line)
{
	*new_line = ft_strjoin(NULL, *tmp, 0);
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
	static int	is_eof = 0;
	static char	*new_line = NULL;
	static int	cnt_read = 0;

	if (tmp == NULL && cnt_read > 1)
		return (NULL);
	new_line = NULL;
	if (read_new_line(&tmp, &is_eof, &cnt_read, fd) == NULL)
		return (NULL);
	if (ft_strlen(tmp, '\n') != 0)
		new_line = get_new_line_from_buffer(&tmp);
	if ((is_eof == 0 || is_eof < BUFFER_SIZE)
		&& ft_strlen(tmp, '\n') == 0 && new_line == NULL)
		return (get_last_line(&tmp, &new_line));
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


	//printf("get_next_line:%s\n", get_next_line(fd));
	printf("get_next_line:%s\n", get_next_line(fd));
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