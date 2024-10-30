/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:26:04 by phhofman          #+#    #+#             */
/*   Updated: 2024/10/30 16:13:50 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*dup;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s1, len + 1);
	return (dup);
}
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
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
size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
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
char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	joinlen;
	char	*join;
	
	if(!s1 || !s2)
		return (NULL);
	joinlen = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (joinlen + 1));
	if (!join)
	{
		free_buf(&s1);
		return (NULL);
	}
	ft_strlcpy(join, s1, joinlen + 1);
	ft_strlcat(join, s2, joinlen + 1);
	free_buf(&s1);
	return (join);
}




