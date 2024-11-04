/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:26:52 by phhofman          #+#    #+#             */
/*   Updated: 2024/11/04 10:39:21 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*ft_update_buffer(char *buffer, char *line);
char	*ft_extract_line(char *buf);
ssize_t	read_buffer(int fd, char *buffer, ssize_t *bytes_read);
void	free_buf(char **buf);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlen(char *str);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_free(char*s1, char *s2);
char	*ft_strdup(char *s1);

#endif