/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/15 17:54:03 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_coord *line)
{
	
}

void	draw_segment(t_coord *line, t_coord *dest)
{

}

void	create_image(t_coord *map, t_par params)
{
	t_coord *line;

	params.mem = mlx_get_data_addr(params.img_p, &(params.bpp),
			&(params.sizeline), &(params.endian));
	while (map)
	{
		line = map;
		while (line)
		{
			draw_point(line);
			draw_segment(line, line->right);
			draw_segment(line, line->down);
			line = line->right;
		}
		map = map->down;
	}
}

void	display(t_coord *map)
{
	t_par	params;

	params.mlx_p = mlx_init();
	params.win_p = mlx_new_window(params.mlx_p, WIDTH, HEIGHT, PRG_NAME);
	while (42)
	{
		params.img_p = mlx_new_image(params.mlx_p, WIDTH, HEIGHT);
		create_image(map, params);
		mlx_put_image_to_window(params.mlx_p, params.win_p, params.img_p, 0, 0);
		mlx_key_hook(params.win_p, my_keys, &params);
		mlx_loop(params.mlx_p);
	}
}
