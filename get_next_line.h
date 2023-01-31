/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:00:57 by chris             #+#    #+#             */
/*   Updated: 2023/01/30 11:57:10 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char 	*get_next_line(int fd);
char	*ft_strdup(const char *s, char end);
char	*ft_strjoin(char *s1, char *s2, int start_s2);
int		ft_strlen(const char *s, char end);
void	cpy_until_end(const char *src, char *dest, int *i, char end);
#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif