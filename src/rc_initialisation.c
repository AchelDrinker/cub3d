/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:10:31 by humartin          #+#    #+#             */
/*   Updated: 2022/12/22 09:08:40 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

void	ft_initialisation2(t_recup *recup)
{
	recup->s.zbuffer = (double *)malloc(sizeof(double) * recup->rx);
	if (!recup->s.zbuffer)
		exit(0);
	recup->data.forward = 0;
	recup->data.back = 0;
	recup->data.left = 0;
	recup->data.right = 0;
	recup->data.rotate_right = 0;
	recup->data.rotate_left = 0;
	recup->ray.posx = (double)recup->dx + 0.5;
	recup->ray.posy = (double)recup->dy + 0.5;
	recup->ray.dirx = 0;
	recup->ray.diry = 0;
	recup->ray.planx = 0;
	recup->ray.plany = 0;
	ft_init_dir(recup);
}

void	ft_initialisation3(t_recup *recup)
{
	recup->ray.hit = 0;
	recup->ray.perpwalldist = 0;
	recup->ray.camerax = 2 * recup->ray.x / (double)recup->rx - 1;
	recup->ray.raydirx = recup->ray.dirx + recup->ray.planx * \
						recup->ray.camerax;
	recup->ray.raydiry = recup->ray.diry + recup->ray.plany * \
						recup->ray.camerax;
	recup->ray.mapx = (int)recup->ray.posx;
	recup->ray.mapy = (int)recup->ray.posy;
	recup->ray.movespeed = 0.1;
	recup->ray.rotspeed = 0.033 * 1.8;
	ft_init_more3(recup);
}

void	ft_init_texture(t_recup *recup)
{
	if (recup->ray.side == 0 && recup->ray.raydirx < 0)
		recup->t.texdir = 0;
	if (recup->ray.side == 0 && recup->ray.raydirx >= 0)
		recup->t.texdir = 1;
	if (recup->ray.side == 1 && recup->ray.raydiry < 0)
		recup->t.texdir = 2;
	if (recup->ray.side == 1 && recup->ray.raydiry >= 0)
		recup->t.texdir = 3;
	if (recup->ray.side == 0)
		recup->t.wallx = recup->ray.posy + recup->ray.perpwalldist \
						* recup->ray.raydiry;
	else
		recup->t.wallx = recup->ray.posx + recup->ray.perpwalldist \
						* recup->ray.raydirx;
	recup->t.wallx -= floor((recup->t.wallx));
}

void	ft_init_sprite(t_recup *recup)
{
	int	i;
	int	j;

	i = -1;
	recup->s.nbspr = 0;
	ft_verify_errors(recup);
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
		{
			if (recup->map[i][j] == '2')
				recup->s.nbspr += 1;
		}
	}
	recup->sxy = (t_sprxy *)malloc(sizeof(t_sprxy) * recup->s.nbspr);
	check_error(recup);
	ft_init_sprite2(recup, 0, 0, 0);
	ft_mlx(recup);
}

void	ft_init_sprite2(t_recup *recup, int i, int j, int v)
{
	i = i - 1;
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
		{
			if (recup->map[i][j] == '2')
			{
				recup->sxy[v].x = (double)i + 0.5;
				recup->sxy[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}
