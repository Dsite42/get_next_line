/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:01:08 by chris             #+#    #+#             */
/*   Updated: 2023/01/18 18:13:33 by cgodecke         ###   ########.fr       */
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

	//printf("le%lin%cf:%s\n", i,*(s + i), s);
	return (i);
}


char	*ft_strdup(const char *s, char end)
{
	char	*dup;
	char	*dup_start;
	int		len;

	len = ft_strlen((char *)s, end);
	if (end == '\n')
		len++;
	dup = malloc((len * sizeof(char)) + 1);
	if (dup == NULL)
		return (NULL);
	dup_start = dup;
	while (*s != end)
	{
		*dup = *s;
		s++;
		dup++;
	}
	if (*s == '\n')
	{
		*(dup) = '\n';
		dup++;
	}
	*(dup) = '\0';
	return (dup_start);
}

/*
int len_line(char *tmp)
{
	static int	cnt = 0;
	int	i;

	i = 0;
	while (tmp[i] != '\n' && tmp[i] != '\0')
	{
		//printf("NU?:%c\n",tmp[i]);
		i++;
	}
	if (tmp[i] == '\n')
	{
		cnt = i++;
		return (i++);
	}
	if (tmp[i] == '\0' && cnt == 0)
		return (-1);
	if (tmp[i] == '\0' && cnt != 0)
		return (-i);
}
*/

char	*ft_strjoin(char *s1, char *s2, int start_s2)
{
	char	*joined;
	size_t	i;
	size_t	j;
	
	joined = (char *) malloc((ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1)
			* sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;

	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	j = start_s2;
	while (s2[j] != '\0')
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	if (*s1 != '\0')
	{
		//printf("fuck:%c\n", *s1);
		free(s1);
	}
	free(s2);
	return (joined);
}

char *get_next_line(int fd)
{
	char		*buf;
	static char	*tmp = "\0";
	static int			isEOF = 0;
	static char		*new_line = NULL;
	char		str_end;

	if (fd < 0 || fd == 1000)
	{
		return (NULL);
	}
	str_end = '\0';
	if (tmp == NULL)
	{
		//printf("hier?");
		return (NULL);
	}
	/*
	if (new_line != NULL)
	{
		printf("mist\n");
		free(new_line);
	}
		printf("free%s\n", new_line);
	*/
	new_line = NULL;
	//printf("PPPPPPPPPPPPPPPP:%c", *tmp);
	while (ft_strlen(tmp, '\n') == 0 && (isEOF == BUFFER_SIZE || *tmp == '\0'))
	{
	if (ft_strlen(tmp, '\n') == 0)
	{
		buf = (char *) malloc(BUFFER_SIZE * sizeof(char) +1);
		if (buf == NULL)
			return (0);
		isEOF = read(fd, buf, BUFFER_SIZE - 0);
		buf[isEOF] = '\0';
		if ((isEOF == 0 && *tmp == '\0') || isEOF == -1)
		{
				if (isEOF != -1 && tmp != NULL)
				{
					//printf("hier2?%s\n", tmp);
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
		tmp = ft_strjoin(tmp, buf, 0);
	}
	if (ft_strlen(tmp, '\n') != 0)
	{
		new_line = ft_strdup(tmp, '\n');
		if (ft_strlen(tmp, '\n') == -1)
			tmp = ft_strjoin(&str_end, tmp, ft_strlen(tmp, '\n') + 2);
		else
			tmp = ft_strjoin(&str_end, tmp, ft_strlen(tmp, '\n') + 1);
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
		new_line = ft_strjoin(&str_end, tmp, 0);
		tmp = NULL;
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

	fd = open("file.txt", O_RDONLY);
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


	printf("get_next_line:%s\n", get_next_line(fd));
	printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));
	//printf("get_next_line:%s\n", get_next_line(fd));

	close(fd);
	//printf("%i bytes were read.\n", sz);
	//printf("Content:%c\n", buf[3]);


}
*/