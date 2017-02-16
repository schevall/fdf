/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/16 17:12:13 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		draw_point(t_coord *l, t_par *p)
{
	unsigned int color;
	char *mem_tmp;
	int X;
	int Y;

	mem_tmp = p->mem;
	color = mlx_get_color_value(p->mlx_p, WHITE);
	ft_printf("l.x = %d, l.y = %d\n", l->x, l->y);
	X = ISO1 * l->x - ISO2 * l->y;
	Y = l->z + (ISO1 / 2) * l->x + (ISO2 / 2) * l->y;
//	X = l->x - l->y;
//	Y = l->z + l->x + l->y;
	ft_printf("X = %d, Y = %d\n", X, Y);
	if (X > WIDTH || Y > HEIGHT || X < 0 || Y < 0)
		return (0);
	p->mem += p->bpp * X + p->sline * Y;
	*p->mem = color;
	p->mem = mem_tmp;
	return (1);
}

int		draw_segment(t_coord *line, t_coord *dest)
{
	if (!line || !dest)
		return (0);
	
	return (1);
}

void	create_image(t_coord *map, t_par *p)
{
	t_coord *line;

	p->mem = mlx_get_data_addr(p->img_p, &(p->bpp), &(p->sline), &(p->endian));
	while (map)
	{
		line = map;
		while (line)
		{
			draw_point(line, p);
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
		create_image(map, &params);
		mlx_put_image_to_window(params.mlx_p, params.win_p, params.img_p, 0, 0);
		mlx_key_hook(params.win_p, my_keys, &params);
		mlx_loop(params.mlx_p);
	}
}
