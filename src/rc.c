/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humartin <humartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:10:46 by humartin          #+#    #+#             */
/*   Updated: 2022/12/22 11:15:35 by humartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <mlx.h>

void	ft_get_texture_adress(t_recup *recup)
{
	recup->texture[0].addr = (int *)mlx_get_data_addr(recup->texture[0].img,
			&recup->texture[0].bits_per_pixel,
			&recup->texture[0].line_length, &recup->texture[0].endian);
	recup->texture[1].addr = (int *)mlx_get_data_addr(recup->texture[1].img,
			&recup->texture[1].bits_per_pixel,
			&recup->texture[1].line_length, &recup->texture[1].endian);
	recup->texture[2].addr = (int *)mlx_get_data_addr(recup->texture[2].img,
			&recup->texture[2].bits_per_pixel,
			&recup->texture[2].line_length, &recup->texture[2].endian);
	recup->texture[3].addr = (int *)mlx_get_data_addr(recup->texture[3].img,
			&recup->texture[3].bits_per_pixel,
			&recup->texture[3].line_length, &recup->texture[3].endian);
	recup->texture[4].addr = (int *)mlx_get_data_addr(recup->texture[4].img,
			&recup->texture[4].bits_per_pixel,
			&recup->texture[4].line_length, &recup->texture[4].endian);
}

void	ft_get_texture(t_recup *recup)
{
	recup->texture[0].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->no, &(recup->texture[0].width), &(recup->texture[0].height));
	if (!recup->texture[0].img)
		ft_error(recup, "Error : Texture SO\n");
	recup->texture[1].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->so, &(recup->texture[1].width), &(recup->texture[1].height));
	if (!recup->texture[1].img)
		ft_error(recup, "Error : Texture NO\n");
	recup->texture[2].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->we, &(recup->texture[2].width), &(recup->texture[2].height));
	if (!recup->texture[2].img)
		ft_error(recup, "Error : Texture EA\n");
	recup->texture[3].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->ea, &(recup->texture[3].width), &(recup->texture[3].height));
	if (!recup->texture[3].img)
		ft_error(recup, "Error : Texture WE\n");
	recup->texture[4].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->sp, &(recup->texture[4].width), &(recup->texture[4].height));
	if (!recup->texture[4].img)
		ft_error(recup, "Error : Texture S\n");
	ft_get_texture_adress(recup);
}

int	ft_raycasting(t_recup *recup)
{
	recup->ray.x = 0;
	while (recup->ray.x < recup->rx)
	{
		ft_initialisation3(recup);
		ft_stepsidedist(recup);
		ft_color_column(recup);
		recup->s.zbuffer[recup->ray.x] = recup->ray.perpwalldist;
		recup->ray.x++;
	}
	ft_sprite(recup);
	mlx_put_image_to_window(recup->data.mlx_ptr, recup->data.mlx_win,
		recup->data.img, 0, 0);
	ft_forward_back(recup);
	ft_left_right(recup);
	ft_rotate_right_left(recup);
	ft_swap(recup);
	return (0);
}

int	ft_mlx(t_recup *recup)
{
	ft_initialisation2(recup);
	recup->data.mlx_ptr = mlx_init();
	if (!recup->data.mlx_ptr)
		ft_error(recup, "Mlx init impossible\n");
	recup->rx = 1080;
	recup->ry = 720;
	ft_get_texture(recup);
	recup->data.img = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr = (int *)mlx_get_data_addr(recup->data.img,
			&recup->data.bits_per_pixel, &recup->data.line_length,
			&recup->data.endian);
	recup->data.mlx_win = mlx_new_window(recup->data.mlx_ptr, recup->rx,
			recup->ry, "FLEXGANG");
	recup->data.img2 = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr2 = (int *)mlx_get_data_addr(recup->data.img2, &recup-> \
			data.bits_per_pixel, &recup->data.line_length, &recup->data.endian);
	mlx_hook(recup->data.mlx_win, 17, 0, ft_exit, recup);
	mlx_hook(recup->data.mlx_win, 2, 1L << 0, ft_key_press, recup);
	mlx_loop_hook(recup->data.mlx_ptr, ft_raycasting, recup);
	mlx_hook(recup->data.mlx_win, 3, 1L << 1, ft_key_release, recup);
	mlx_loop(recup->data.mlx_ptr);
	return (0);
}
