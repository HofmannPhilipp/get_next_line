/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:26:04 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/27 14:42:06 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize -1)
		{
			dst[i] = src[i];
			i ++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i ++;
	return (i);
}
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	dst_len = 0;
	src_len = ft_strlen(src);
	while (dst[dst_len] && dst_len < dstsize)
		dst_len ++;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && dst_len + i < dstsize - 1)
	{
		dst[dst_len + i] = src[i];
		i ++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	joinlen;
	char	*join;

	joinlen = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (joinlen + 1));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, joinlen + 1);
	ft_strlcat(join, s2, joinlen + 1);
	return (join);
}

char	*search_for_new_line(char *buf)
{
	char	*str;
	int		j;

	j = 0;
	if(!buf)
		return(NULL);
	while (buf[j] != '\0' && buf[j] != '\n')
	{
		j ++;
	}
	if (buf[j] == '\n')
	{
		str = (char *)malloc(sizeof(char) * (j + 2)); // +2 because of the \n and \0
		if (!str)
			return (NULL);
		ft_strlcpy(str, buf, j + 2);
		return (str);
	}
	return (NULL);
}