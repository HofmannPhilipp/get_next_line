/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:00:44 by phhofman          #+#    #+#             */
/*   Updated: 2024/11/04 10:19:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_buf( char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}

char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i ++;
	if (buffer[i] == '\n')
	{
		line = (char *)malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		ft_strlcpy(line, buffer, i + 2);
		return (line);
	}
	return (NULL);
}

char	*ft_update_buffer(char *buffer, char *line)
{
	char	*remaining;

	remaining = ft_strdup(buffer + ft_strlen(line));
	free_buf(&buffer);
	if (!remaining)
		return (NULL);
	return (remaining);
}

ssize_t	read_buffer(int fd, char *buffer, ssize_t *bytes_read)
{
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read == -1)
		return (-1);
	buffer[*bytes_read] = '\0';
	return (*bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*rest_buffer;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (!rest_buffer)
		rest_buffer = ft_strdup("");
	if (!rest_buffer || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_extract_line(rest_buffer);
	while (!line && read_buffer(fd, buffer, &bytes_read) > 0)
	{
		rest_buffer = ft_strjoin_free(rest_buffer, buffer);
		if (!rest_buffer)
			return (NULL);
		line = ft_extract_line(rest_buffer);
	}
	if (line)
		return (rest_buffer = ft_update_buffer(rest_buffer, line), line);
	if (bytes_read != -1 && rest_buffer[0] != '\0')
		return (line = ft_strdup(rest_buffer), free_buf(&rest_buffer), line);
	return (free_buf(&rest_buffer), NULL);
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
