/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 09:43:21 by humartin          #+#    #+#             */
/*   Updated: 2022/12/22 11:15:35 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

void	do_temp(char **buff, int start, char *line_temp, char **line)
{
	char	*temp;

	temp = ft_substr(*buff, 0, start);
	line_temp = *line;
	*line = ft_strjoin(*line, temp);
	free(temp);
	free(line_temp);
	*buff = ft_subbuff(*buff, start + 1, (ft_strlen(*buff) - start));
}

char	*buff_this(char *buff)
{
	if (!buff)
		buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	return (buff);
}

int	ft_nb_virgule(const char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
	}
	return (j);
}
