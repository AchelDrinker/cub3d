/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:09:17 by humartin          #+#    #+#             */
/*   Updated: 2022/12/22 10:53:35 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

void	check_error(t_recup *recup)
{
	if (!recup->sxy)
		ft_error(recup, "Malloc sxy*");
	recup->s.order = (int *)malloc(sizeof(int) * recup->s.nbspr);
	if (!recup->s.order)
		ft_error(recup, "Malloc s.order*");
	recup->s.dist = (double *)malloc(sizeof(double) * recup->s.nbspr);
	if (!recup->s.dist)
		ft_error(recup, "Malloc s.dist*");
}

void	whilej(t_recup *recup, int i, int j)
{
	while (j <= (recup->sizeline - 1))
	{
		recup->map[i][j] = '1';
		j++;
	}
}

void	recup_texture(char **texture, t_recup *recup, char *str, int j)
{
	*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)));
	if (!*texture)
		recup->erreur = 2;
	while (str[j] != '\0')
	{
		(*texture)[recup->count2] = str[j];
		recup->count2++;
		j++;
	}
	(*texture)[recup->count2] = '\0';
}

void	fd_reader(int ret, int fd, t_recup *recup, char *str)
{
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, recup, 1);
		if (recup->insidemap == 1 && ft_lignevide(str) == 0 && \
				recup->count < recup->nblines)
			recup->lignevide = 1;
		recup->insidemap = ft_is_map(str, recup);
		if (recup->insidemap == 1)
		{
			recup->count++;
			ft_copy_map(str, recup);
		}
		free(str);
	}
}

void	fd_reader2(int ret, int fd, t_recup *recup, char *str)
{
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, recup, 1);
		if (recup->erreur == 2)
			ft_error(recup, "La partie parsing detecte une erreur\n");
		ft_color_resolution(&str, recup);
		ft_texture(str, recup);
		ft_map(str, recup);
		free(str);
	}
}
