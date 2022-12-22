/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:09:43 by humartin          #+#    #+#             */
/*   Updated: 2022/12/22 10:53:33 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

int	ft_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_copy(char **line, char **buff)
{
	int		start;
	char	*temp;
	char	*line_temp;

	line_temp = NULL;
	*line = NULL;
	start = ft_check(*buff);
	if (start >= 0)
	{
		do_temp(buff, start, line_temp, line);
		return (0);
	}
	else
	{
		temp = NULL;
		if (*line)
			temp = *line;
		*line = ft_strjoin(*line, *buff);
		if (temp)
			free(temp);
		return (1);
	}
	return (-1);
}

int	ft_eof(int ret, char **buff, char **line)
{
	*line = NULL;
	if (ret == -1)
		return (-1);
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

int	ft_free_buff(char **buff, t_recup *recup)
{
	if (recup->erreur == 2 && *buff)
	{
		free(*buff);
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line, t_recup *recup, int ret)
{
	static char	*buff = NULL;

	if (ft_free_buff(&buff, recup) == 1)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (buff)
		ret = ft_copy(line, &buff);
	if (ret == 0)
		return (1);
	buff = buff_this(buff);
	if (!buff)
		return (-1);
	while (1)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buff[ret] = '\0';
		if (!ft_copy(line, &buff))
			return (1);
	}
	if (ret <= 0)
		return (ft_eof(ret, &buff, line));
	return (1);
}
