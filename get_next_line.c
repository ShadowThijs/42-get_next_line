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
#include <stdlib.h>
#include <unistd.h>

static char	*extract_line(char **stash)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	newline_pos = ft_strchr(*stash, '\n');
	if (!newline_pos)
		return (NULL);
	line = ft_substr(*stash, 0, newline_pos - *stash + 1);
	temp = ft_strdup(newline_pos + 1);
	free(*stash);
	*stash = temp;
	return (line);
}

static char	*cleanup(char **stash, char *buf, int buf_bool, int stash_bool)
{
	if (buf_bool == 1)
	{
		free(buf);
	}
	if (stash_bool == 1)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

static char	*read_and_stash(int fd, char **stash)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read < 0)
		return (cleanup(stash, buf, 1, 1));
	if (bytes_read == 0)
		return (cleanup(stash, buf, 1, 0));
	buf[bytes_read] = '\0';
	temp = ft_strjoin(*stash, buf);
	free(buf);
	free(*stash);
	*stash = temp;
	return (*stash);
}

static char	*get_remainder(char **stash)
{
	char	*line;

	if (!*stash || !**stash)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	line = ft_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		line = extract_line(&stash);
		if (line)
			return (line);
		if (!read_and_stash(fd, &stash))
			break ;
	}
	return (get_remainder(&stash));
}

/*
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("line 1: %s\n", line);
	char *line2 = get_next_line(fd);
	printf("line 2: %s\n", line2);
	char *line3 = get_next_line(fd);
	printf("line 3: %s\n", line3);
	char *line4 = get_next_line(fd);
	printf("line 4: %s\n", line4);
  char *line5 = get_next_line(fd);
	printf("line 5: %s\n", line5);
  char *line6 = get_next_line(fd);
	printf("line 6: %s\n", line6);
  char *line7 = get_next_line(fd);
	printf("line 7: %s\n", line7);
	char *line8 = get_next_line(fd);
	printf("line 8: %s\n", line8);
  close(fd);
	return (0);
}
*/
