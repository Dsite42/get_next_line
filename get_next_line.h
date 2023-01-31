/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodecke <cgodecke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:00:57 by chris             #+#    #+#             */
/*   Updated: 2023/01/31 17:51:50 by cgodecke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char 	*get_next_line(int fd);
char	*ft_strdup(const char *s, char end);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *s, char end);
void	cpy_len(const char *src, char *dest, int len);
int	line_counter(const char *str);
char	*reduce_tmp(char *str, int start);
int read_new_line(char **tmp, int fd);
int	fill_buffer(char **buf, int fd);




#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif