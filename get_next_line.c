/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:00:44 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/28 16:46:30 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	char		buffer[BUFFER_SIZE + 1];
	static char	*rest_buffer = NULL;
	ssize_t		bytes_read;

	char		*found_nl_str;
	char		*remaining;
	char		*joined_buffer;

	if (rest_buffer == NULL)
	{
		rest_buffer = ft_strdup("");
		if (!rest_buffer)
			return (NULL);
	}
	found_nl_str = search_for_new_line(rest_buffer);
	if (found_nl_str == NULL)
	{
		free(rest_buffer);
		return (NULL);
	}
	if (*found_nl_str != '\0')
	{
		remaining = ft_strdup(rest_buffer + ft_strlen(found_nl_str));
		free(rest_buffer);
		rest_buffer = remaining;
		return (found_nl_str);
	}

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[BUFFER_SIZE] = '\0';

		found_nl_str = search_for_new_line(buffer);
		if (found_nl_str == NULL)
		{
			free(rest_buffer);
			rest_buffer = NULL;
			return (NULL);
		}
		if (*found_nl_str != '\0')
		{
			joined_buffer = ft_strjoin(rest_buffer, found_nl_str);
			free(rest_buffer);
			rest_buffer = ft_strdup(buffer + ft_strlen(found_nl_str));
			return (joined_buffer);
		}
		if (*found_nl_str == '\0')
		{
			joined_buffer = ft_strjoin(rest_buffer,buffer);
			free (rest_buffer);
			rest_buffer = joined_buffer;
		}
	}
}


// char	*get_next_line(int fd)
// {
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	char buf[BUFFER_SIZE + 1];
// 	static char *rest_buf = NULL;
// 	ssize_t bytes_read;
// 	char	*str;
// 	char	*remaining;
	
// 	if (!rest_buf)
// 	{
// 		rest_buf = ft_strdup("");
// 		if (!rest_buf)
// 			return (NULL);
// 	str = search_for_new_line(rest_buf);
// 	if (!str)
// 	{
// 		free(rest_buf);
// 		rest_buf = NULL;
// 		return (NULL);
// 	}
// 	if (*str != '\0')
// 	{
// 		remaining = ft_strdup(rest_buf + ft_strlen(str));
// 		free(rest_buf);
// 		if (!remaining)
// 		{
// 			rest_buf = NULL;
// 			return (NULL);
// 		}
// 		rest_buf = remaining;
// 		return (str);
// 	}
// 	}
// 	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
// 	{
// 		buf[bytes_read] = '\0';
// 		remaining = ft_strjoin(rest_buf, buf);
// 		free(rest_buf);
// 		if (!remaining)
// 		{
// 			rest_buf = NULL;
// 			return (NULL);
// 		}
// 		rest_buf = remaining;
// 		str = search_for_new_line(rest_buf);
// 		if (!str)
// 		{
// 			free(rest_buf);
// 			rest_buf = NULL;
// 			return (NULL);
// 		}
// 		if (*str != '\0')
// 		{
// 			remaining = ft_strdup(rest_buf + ft_strlen(str));
// 			free(rest_buf);
// 			if (!remaining)
// 			{
// 				rest_buf = NULL;
// 				return (NULL);
// 			}
// 			rest_buf = remaining;
// 			return (str);
// 		}
// 	}
// 	if (bytes_read == -1 || (!str && (!rest_buf || *rest_buf == '\0')))
// 	{
// 		free(rest_buf);
// 		rest_buf = NULL;
// 		return (NULL);
// 	}
// 	free(rest_buf);
// 	rest_buf = NULL;
// 	return (NULL);
// }
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

 