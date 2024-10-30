/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:00:44 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/30 16:27:11 by phhofman         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		read_buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = search_for_new_line(buffer);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (!line && bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, read_buffer);
		if (!buffer)
			return (NULL);
		line = search_for_new_line(buffer);
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	if (line)
		return (buffer = process_remaining_buffer(buffer, line), line);
	if (bytes_read != -1 && buffer && buffer[0] != '\0')
		return (line = ft_strdup(buffer), free_buf(&buffer), line);
	return (free_buf(&buffer), NULL);
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
