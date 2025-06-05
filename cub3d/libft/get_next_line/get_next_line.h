/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:05:26 by bde-luce          #+#    #+#             */
/*   Updated: 2024/09/13 18:18:58 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char		*get_next_line(int fd);
int			check_nl(char *buf);
size_t		str_len(char *str);
char		*join_buf(char *s1, char *s2);
void		copy_line(char *str_copy, char *str);
void		copy_rest(char *str_copy, char *str, int j);

#endif