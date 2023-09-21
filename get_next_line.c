/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:15:06 by jikarunw          #+#    #+#             */
/*   Updated: 2023/09/22 02:14:35 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*ft_get_line(char **current_buffer, char **line)
{
	char	*next_buffer;
	int		i;

	i = 0;
	next_buffer = NULL;
	while (*(*current_buffer + i) != '\n' && *(*current_buffer + i) != '\0')
		i++;
	if (*(*current_buffer + i) == '\n')
	{
		i++;
		*line = ft_substr(*current_buffer, 0, i);
		next_buffer = ft_strdup(*current_buffer + i);
	}
	else
		*line = ft_strdup(*current_buffer);
	ft_free(current_buffer);
	return (next_buffer);
}

static int	ft_read_line(int fd, char **r_buffer, char **bk_buffer, char **line)
{
	char	*temp_buffer;
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(*bk_buffer, '\n') && bytes_read)
	{
		bytes_read = read(fd, *r_buffer, BUFFER_SIZE);
		(*r_buffer)[bytes_read] = '\0';
		temp_buffer = *bk_buffer;
		*bk_buffer = ft_strjoin(temp_buffer, *r_buffer);
		free(temp_buffer);
	}
	ft_free(line);
	*bk_buffer = ft_get_line(bk_buffer, line);
	if (!(**line))
		ft_free(line);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buffer_backup = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!buffer_backup)
		buffer_backup = ft_strdup("");
	if (!ft_read_line(fd, &buffer, &buffer_backup, &line) && !line)
		return (NULL);
	return (line);
}
