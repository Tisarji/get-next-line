/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:15:04 by jikarunw          #+#    #+#             */
/*   Updated: 2023/09/22 02:13:11 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(&str[s1_len], s2, s1_len + s2_len + 1);
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;

	i = 0;
	src_length = 0;
	while (src[src_length])
		src_length++;
	if (size <= 0)
		return (src_length);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_length);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char) str[i] == (unsigned char)c)
			return ((char *) &str[i]);
		i++;
	}
	if (c == '\0')
		return ((char *) &str[i]);
	return ((void *) 0);
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	len;
	char	*dup;

	i = 0;
	len = 0;
	if (!src)
		return (NULL);
	while (src[len])
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		++i;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	substr_length;
	size_t	s_length;
	char	*substr;

	if (!s)
		return (NULL);
	s_length = 0;
	while (s[s_length])
		s_length++;
	substr_length = s_length - start;
	if (s_length > start)
	{
		if (substr_length > len)
			substr = (char *) malloc(sizeof(char) * (len + 1));
		else
			substr = (char *) malloc(sizeof(char) * (substr_length + 1));
		if (!substr)
			return (NULL);
		ft_strlcpy(substr, &s[start], len + 1);
	}
	else
		substr = ft_strdup("");
	return (substr);
}
