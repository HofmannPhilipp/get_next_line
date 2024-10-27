/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:00:44 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/27 17:59:43 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	char buf[BUFFER_SIZE + 1];
	static char *rest_buf = NULL;
	ssize_t bytes_read;
	char	*str;
	char	*remaining;
	
	if (rest_buf)
	{
		str = search_for_new_line(rest_buf);
		if (str)
		{	
			remaining = ft_strdup(rest_buf + ft_strlen(str));
			free(rest_buf);
			rest_buf = remaining;
			return (str);
		}
	}
	else 
		rest_buf = ft_strdup("");


	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		remaining = ft_strjoin(rest_buf, buf);
		free(rest_buf);
		rest_buf = remaining;
		
		str = search_for_new_line(rest_buf);
		if (str)
		{	
			remaining = ft_strdup(rest_buf + ft_strlen(str));
			free(rest_buf);
			rest_buf = remaining;
			return (str);
		}

		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(rest_buf);
		rest_buf = NULL;
		return (NULL);
	}

	if (rest_buf && *rest_buf != '\0')
	{
		str = ft_strdup(rest_buf);
		free(rest_buf);
		rest_buf = NULL;
		return (str);
	}

	free(rest_buf);
	rest_buf = NULL;
	return (NULL);
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

 