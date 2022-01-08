/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:50:08 by jpfuhl            #+#    #+#             */
/*   Updated: 2021/09/30 20:02:37 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_check_remainder(char **remainder, char **line);
static void	ft_modify_remainder(char *nl, char **remainder);
static char	*ft_read_text(int fd, char *line, char *nl, char **remainder);
static char	*ft_exit_function(char **line, char **buf);

char	*get_next_line(int fd)
{
	static char	*remainder[10240];
	char		*line;
	char		*nl;

	if (fd < 0 || 10240 < fd || BUFFER_SIZE <= 0)
		return (NULL);
	nl = ft_check_remainder(&remainder[fd], &line);
	line = ft_read_text(fd, line, nl, &remainder[fd]);
	return (line);
}

static char	*ft_check_remainder(char **remainder, char **line)
{
	char	*nl;

	nl = NULL;
	if (*remainder == NULL)
	{
		*line = malloc(1 * sizeof(char));
		if (*line == NULL)
			return (NULL);
		*line[0] = '\0';
	}
	else if (*remainder)
	{
		*line = ft_strdup(*remainder);
		nl = ft_strchr(*line, '\n');
		free(*remainder);
		ft_modify_remainder(nl, remainder);
	}
	return (nl);
}

static void	ft_modify_remainder(char *nl, char **remainder)
{
	if (nl)
	{
		if (*(nl + 1) != '\0')
			*remainder = ft_strdup(nl + 1);
		else
			*remainder = NULL;
		*nl = '\0';
	}
	else
		*remainder = NULL;
}

static char	*ft_read_text(int fd, char *line, char *nl, char **remainder)
{
	char	*buf;
	int		bytes_read;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (!nl && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read == 0 && line[0] == '\0'))
			return (ft_exit_function(&line, &buf));
		buf[bytes_read] = '\0';
		line = ft_strjoin(line, buf);
		nl = ft_strchr(line, '\n');
		ft_modify_remainder(nl, remainder);
	}
	ft_free_memory(&buf);
	if (nl)
		line = ft_strjoin(line, "\n");
	return (line);
}

static char	*ft_exit_function(char **line, char **buf)
{
	ft_free_memory(line);
	ft_free_memory(buf);
	return (NULL);
}
