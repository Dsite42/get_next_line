/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:08 by chris             #+#    #+#             */
/*   Updated: 2023/01/20 18:57:41 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <string.h>

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

char *get_next_line(int fd)
{
	char		*buf;
	static char	*tmp = NULL;
	static int	isEOF = 0;
	static char	*new_line = NULL;
	static int	cnt_read = 0;

	if (tmp == NULL && cnt_read > 1)
	{
		return (NULL);
	}

	new_line = NULL;
	//printf("PPPPPPPPPPPPPPPP:%c", *tmp);
	while ((ft_strlen(tmp, '\n') == 0 && (isEOF == BUFFER_SIZE || tmp == NULL)))
	{
		if (ft_strlen(tmp, '\n') == 0)
		{
			buf = (char *) malloc(BUFFER_SIZE * sizeof(char) +1);
			if (buf == NULL)
				return (0);
			isEOF = read(fd, buf, BUFFER_SIZE - 0);
			cnt_read++;
			//printf("EOF:%i\n",isEOF);
			if (isEOF != -1)
				buf[isEOF] = '\0';
			if (((isEOF == 0 && tmp == NULL) || isEOF == -1))
			{
					if (isEOF != -1 && tmp != NULL )
					{
						//printf("hier2?%s\n", tmp);
						if (cnt_read > 1)
							free(tmp);
						tmp = NULL;
					}
					//printf("free(buf)\n");
				free(buf);
				return (NULL);
			}
		}
		//printf("test:%c\n", *tmp);
		if (ft_strlen(tmp, '\n') == 0)
		{
			//printf("slashN");
			tmp = ft_strjoin(tmp, buf, 0);
		}
	}
	if (ft_strlen(tmp, '\n') != 0)
	{
		new_line = ft_strdup(tmp, '\n');
		if (ft_strlen(tmp, '\n') == -1)
		{
			//printf("MinusEins");
			tmp = ft_strjoin(NULL, tmp, 1);
		}
		else
			tmp = ft_strjoin(NULL, tmp, ft_strlen(tmp, '\n') + 1);
		//printf("reduced:%s\n", tmp);
	}
	//printf("new_line:%s\n", new_line);
	//printf("tmp:%s\n", tmp);
	
	//write(1, tmp, len_line(tmp));
	//printf("len_line:%i\n", len_line(tmp));
	

	//printf("%pEOF:%s\n", buf, buf);
	//printf("EOF:%i\n",isEOF);
	//st_test[0] = 'P';
		//printf("isEOF:%i\n", isEOF);

	//if (new_line == NULL && isEOF < BUFFER_SIZE - 1 && ft_strlen(tmp, '\n') == 0)
	
	if ((isEOF == 0 || isEOF < BUFFER_SIZE) && ft_strlen(tmp, '\n') == 0 && new_line == NULL)
	{
		//printf("fuckfu:%i\n", ft_strlen(tmp, '\n'));
		new_line = ft_strjoin(NULL, tmp, 0);
		tmp = NULL;
		if (*new_line == '\0')
		{
			free(new_line);
			return (NULL);
		}
		return (new_line);
	}
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

	fd = open("/Users/cgodecke/francinette/tests/get_next_line/fsoares/only_nl.txt", O_RDONLY);
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