/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/17 17:48:16 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(int X, int Y, t_par *par, int mode)
{
	char *mem_tmp;

	mem_tmp = par->mem + ((par->bpp/8) * X + par->sline * Y);
	if (mode == 1)
		*(int*)mem_tmp = mlx_get_color_value(par->mlx_p, WHITE);
	else
		*(int*)mem_tmp = mlx_get_color_value(par->mlx_p, RED);
}

int		draw_segment(t_coord *ori, t_coord *dest, t_par *par)
{
	int x1;
	int y1;
	int dx;
	int dy;
	int Dx;
	int Dy;
	int ex;
	int ey;
	int x_incr;
	int y_incr;
	int i;

	if (!dest)
		return (0);
	x_incr = 1;
	y_incr = 1;
	x1 = ori->X;
	y1 = ori->Y;
	ex = ft_abs(dest->X - ori->X);
	ey = ft_abs(dest->Y - ori->Y);
	dx = 2 * ex;
	dy = 2 * ey;
	Dx = ex;
	Dy = ey;
	i = 0;
	if (ori->X > dest->X)
		x_incr = -1;
	if (ori->Y > dest->Y)
		y_incr = -1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			put_pixel(x1, y1, par, 2);
			i++;
			x1 += x_incr;
			ex -= dy;
			if (ex < 0)
			{
				y1 += y_incr;
				ex += dx;
			}
		}
	}
	else
	{
		while (i <= Dy)
		{
			put_pixel(x1, y1, par, 2);
			i++;
			y1 += y_incr;
			ey -= dx;
			if (ex < 0)
			{
				x1 += x_incr;
				ey += dy;
			}
		}
	}
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
			draw_segment(line, line->right, p);
			draw_segment(line, line->down, p);
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
		mlx_put_image_to_window(params.mlx_p, params.win_p, params.img_p, 300, 300);
		mlx_key_hook(params.win_p, my_keys, &params);
		mlx_loop(params.mlx_p);
	}
}
