/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:00:44 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/30 11:06:19 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_buf(int error_flag, char **buf)
{
	if (error_flag == 1)
	{
		free(*buf);
		*buf = NULL;
	}
}
char	*search_for_new_line(char *buf)
{
	char	*str;
	int		i;

	i = 0;
	if(!buf)
		return(NULL);
	while (buf[i] != '\0' && buf[i] != '\n')
		i ++;
	if (buf[i] == '\n')
	{
		str = (char *)malloc(sizeof(char) * (i + 2));
		if (!str)
		{
			return (NULL);
		}
		ft_strlcpy(str, buf, i + 2);
		return (str);
	}
	return (NULL);
}
char *process_remaining_buffer(char *rest_buf, char *str)
{
	char *remaining = ft_strdup(rest_buf + ft_strlen(str));
	free(rest_buf);
	return remaining;
}
// char *read_and_process(int fd, char *rest_buf, int *error_flag)
// {
// 	char buf[BUFFER_SIZE + 1];
// 	ssize_t bytes_read;
// 	char *remaining;
// 	char *str;

// 	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0) {
// 		buf[bytes_read] = '\0';
// 		remaining = ft_strjoin(rest_buf, buf);
// 		if (!remaining)
// 			return (free_buf(1, &rest_buf), NULL);
// 		free(rest_buf);
// 		rest_buf = remaining;
// 		str = search_for_new_line(rest_buf);
// 		if (str) {
// 			remaining = process_remaining_buffer(rest_buf, str);
// 		if (!remaining)
// 			return (free_buf(1, &rest_buf), NULL);
// 		rest_buf = remaining;
// 		return (str);
// 		}
// 	}
// 	return (NULL);
// }

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	char buf[BUFFER_SIZE + 1];
	static char *rest_buf = NULL;
	ssize_t bytes_read;
	char	*str;
	char	*remaining;
	
	if (!rest_buf)
	{
		rest_buf = ft_strdup("");
		if (!rest_buf)
			return (NULL);
	}
	str = search_for_new_line(rest_buf);
	if (str)
	{
		rest_buf = process_remaining_buffer(rest_buf, str);
		return (str);
	}
	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		remaining = ft_strjoin(rest_buf, buf);
		if (!remaining)
			return (free_buf(1, &rest_buf), NULL);
		free(rest_buf);
		rest_buf = remaining;
		str = search_for_new_line(rest_buf);
		if (str)
		{
			rest_buf = process_remaining_buffer(rest_buf, str);
			return (str);
		}
	}
	if (rest_buf && *rest_buf != '\0' && bytes_read != -1)
	{
		str = ft_strdup(rest_buf);
		free_buf(1, &rest_buf);
		return (str);
	}
	return (free_buf(1, &rest_buf), NULL);
}
// #include <stdio.h>

// int main(void)
// {	
// 	int fd;

// 	char buf[BUFFER_SIZE + 1];
// 	fd = open("test.txt",O_RDONLY);
// 	printf("%zd\n",read(99,buf,BUFFER_SIZE));
// 	char *res = get_next_line(fd);
// 	// char *res2 = get_next_line(fd); 
// 	// char *res3 = get_next_line(fd); 
// 	// char *res4 = get_next_line(fd); 
// 	printf("%s",res);
// 	// printf("%s",res2);
// 	// printf("%s",res3);
// 	// printf("%s",res4);
// }

 