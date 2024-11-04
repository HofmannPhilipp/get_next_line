/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:26:02 by phhofman          #+#    #+#             */
/*   Updated: 2024/11/04 10:44:02 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*rest_buffer[OPEN_MAX + 1];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 )
		return (NULL);
	if (!rest_buffer[fd])
		rest_buffer[fd] = ft_strdup("");
	if (!rest_buffer[fd])
		return (NULL);
	line = ft_extract_line(rest_buffer[fd]);
	while (!line && read_buffer(fd, buffer, &bytes_read) > 0)
	{
		rest_buffer[fd] = ft_strjoin_free(rest_buffer[fd], buffer);
		if (!rest_buffer[fd])
			return (NULL);
		line = ft_extract_line(rest_buffer[fd]);
	}
	if (line)
		return (rest_buffer[fd] = ft_update_buffer(rest_buffer[fd], line), line);
	if (bytes_read != -1 && rest_buffer[fd][0] != '\0')
		return (line = ft_strdup(rest_buffer[fd]), free_buf(&rest_buffer[fd]), line);
	return (free_buf(&rest_buffer[fd]), NULL);
}
