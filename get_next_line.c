/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:15:06 by jikarunw          #+#    #+#             */
/*   Updated: 2023/09/20 20:56:46 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_file_size(int fd, char *buffer, char *data_buffer)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		data_buffer[read_line] = '\0';
		if (!data_buffer)
			data_buffer = ft_strdup("");
		temp = data_buffer;
		data_buffer = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (data_buffer);
}

static char	*ft_extract_line(char *text)
{
	size_t	len;
	char	*line;

	len = 0;
	while (text[len] != '\n' && text[len] != '\0')
		len++;
	if (text[len] != '\0' || text[1] == '\0')
		return (NULL);
	line = ft_substr(text, len + 1, ft_strlen(text) - len);
	if (*line == '\0')
	{
		free(line);
		line = NULL;
	}
	text[len + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*data = NULL;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE +1));
	if (!buffer)
		return (NULL);
	data = ft_read_file_size(fd, buffer, data);
    line = ft_extract_line(data);
	return (line);
}
