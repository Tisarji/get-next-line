/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikarunw <jikarunw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:15:06 by jikarunw          #+#    #+#             */
/*   Updated: 2023/10/10 23:58:43 by jikarunw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * The function `ft_next_buffer` extracts the next line from a given buffer and returns it, while
 * updating the buffer to exclude the extracted line.
 * 
 * @param temp A pointer to a pointer to a character (char **). It is used to store the address of a
 * string.
 * 
 * @return a pointer to a dynamically allocated character array (string) called "line".
 */

static char	*ft_next_buffer(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		++ptr;
	ptr += (*ptr == '\n');
	line = ft_substr(*temp, 0, (size_t)(ptr - *temp));
	if (!line)
	{
		free (*temp);
		return (NULL);
	}
	ptr = ft_substr(ptr, 0, ft_strlen(ptr));
	free(*temp);
	*temp = ptr;
	return (line);
}

/**
 * The function `ft_read_buffer` reads data from a file descriptor and appends it to a temporary buffer
 * until a newline character is encountered or the end of the file is reached.
 * 
 * @param temp The "temp" parameter is a string that stores the content read from the file so far. It
 * is initially empty and gets appended with the content read from the file in each iteration of the
 * while loop until a newline character is encountered or the end of file is reached.
 * @param fd The parameter "fd" represents the file descriptor of the file that is being read from.
 * @param buf The parameter `buf` is a character array used as a temporary buffer to read data from a
 * file descriptor (`fd`). It is used to store the data read from the file in chunks of size
 * `BUFFER_SIZE`.
 * 
 * @return a pointer to a character, which is the updated value of the "temp" variable.
 */

static char	*ft_read_buffer(char *temp, int fd, char *buf)
{
	ssize_t	r;

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

/**
 * The function "get_next_line" reads a line from a file descriptor and returns it as a string.
 * 
 * @param fd The parameter "fd" represents the file descriptor of the file that we want to read from.
 * It is an integer value that uniquely identifies an open file in the operating system.
 * 
 * @return a pointer to a character, which represents the next line read from the file descriptor
 * specified by `fd`.
 */

char	*get_next_line(int fd)
{
	static char	*temp[FD_MAX];
	char		*buffer;

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
