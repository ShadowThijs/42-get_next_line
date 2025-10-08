/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:03:54 by tlogtenb          #+#    #+#             */
/*   Updated: 2025/10/08 19:41:00 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_newline(char **stash, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while (*stash && (*stash)[i])
	{
		if ((*stash)[i] == '\n' || (*stash)[i] == EOF)
		{
			*line = malloc(i + 2);
			ft_strlcpy(*line, *stash, i + 2);
			temp = ft_strdup(*stash + i + 1);
			free(*stash);
			*stash = malloc(ft_strlen(temp) + 1);
			*stash = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

int	read_line(int fd, size_t size, char **stash)
{
	int		char_read;
	char	*buf;
	char	*temp;

	buf = malloc(size + 1);
	if (buf == NULL)
		return (0);
	char_read = read(fd, buf, size);
	buf[char_read + 1] = '\0';
	temp = ft_strdup(*stash);
	free(*stash);
	*stash = malloc(size + ft_strlen(*stash) + 1);
	*stash = ft_strjoin(temp, buf);
	return (char_read);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			char_read;

	char_read = BUFFER_SIZE;
	while (char_read == BUFFER_SIZE)
	{
		if (check_newline(&stash, &line))
			return (line);
		char_read = read_line(fd, BUFFER_SIZE, &stash);
	}
	if (check_newline(&stash, &line))
		return (line);
	return (NULL);
}

/*
int	main(void)
{
	int	fd;

	fd = open("README.md", O_RDONLY);
	char *line = get_next_line(fd);
	printf("line 1: %s", line);
	char *line2 = get_next_line(fd);
	printf("line 2: %s", line2);
	char *line3 = get_next_line(fd);
	printf("line 3: %s", line3);
	char *line4 = get_next_line(fd);
	printf("line 4: %s", line4);
	close(fd);
	return (0);
}
*/
