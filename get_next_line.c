/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:15:06 by jikarunw          #+#    #+#             */
/*   Updated: 2023/10/10 15:08:17 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *ft_next_buffer(char **temp)
{
	char *line;
	char *ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		++ptr;
	ptr += (*ptr == '\n');
	line = ft_substr(*temp, 0, (size_t)(ptr - *temp));
	if (!line)
	{
		free(*temp);
		return (NULL);
	}
	ptr = ft_substr(ptr, 0, ft_strlen(ptr));
	free(*temp);
	*temp = ptr;
	return (line);
}

static char *ft_read_buffer(char *temp, int fd, char *buf)
{
	ssize_t r;

	r = 1;
	while (r && !ft_strchr(temp, '\n'))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		buf[r] = 0;
		temp = ft_strjoin(temp, buf);
		if (!temp)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (temp);
}

char *get_next_line(int fd)
{
	static char *temp[FD_MAX];
	char *buffer;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup("");
	if (!temp[fd])
		return (NULL);
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(temp[fd]);
		return (NULL);
	}
	temp[fd] = ft_read_buffer(temp[fd], fd, buffer);
	if (!temp[fd])
		return (NULL);
	if (!*temp[fd])
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (ft_next_buffer(&temp[fd]));
}
