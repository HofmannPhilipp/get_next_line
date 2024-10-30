/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:10:50 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/30 10:51:57 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 1024
# endif
char	*get_next_line(int fd);
char	*search_for_new_line(char *buf);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlen(char *str);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char*s1, char *s2);
char	*ft_strdup(char *s1);
void	free_buf(int error_flag, char **buf);

#endif