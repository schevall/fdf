/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/20 17:52:36 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(int X, int Y, t_par *p)
{
	char *mem_tmp;

//	ft_printf("init init put_pixel, X = %d, Y = %d\n", X, Y);
	mem_tmp = p->mem + p->bpp/8 * X + p->sline * Y;
	*(int*)mem_tmp = mlx_get_color_value(p->mlx, WHITE);
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
	ori->X > dest->X ? x_incr = -1 : 1;
	ori->Y > dest->Y ? y_incr = -1 : 1;
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			put_pixel(x1, y1, par);
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
			put_pixel(x1, y1, par);
			i++;
			y1 += y_incr;
			ey -= dx;
			if (ey < 0)
			{
				x1 += x_incr;
				ey += dy;
			}
		}
	}
	return (1);
}

void	create_image(t_par *p)
{
	t_coord *tmp;
	t_coord *line;

	p->mem = mlx_get_data_addr(p->img, &(p->bpp), &(p->sline), &(p->endian));
	tmp = p->map;
	while (tmp)
	{
		line = tmp;
		while (line)
		{
			draw_segment(line, line->right, p);
			draw_segment(line, line->down, p);
			line = line->right;
		}
		tmp = tmp->down;
	}

}

void	get_iso_coord(t_coord *map, t_par *p)
{
	t_coord *tmp;
	t_coord *line;

	tmp = map;
//	ft_printf("init iso coord, map x = %d, y = %d, X = %d, Y = %d\n", map->x, map->y, map->X, map->Y);
	while (tmp)
	{
		line = tmp;
		while (line)
		{
			line->X = p->zoom * (2 * line->x - 2 * line->y + p->offset_x);
			line->Y = p->zoom * (line->z + line->x + line->y + p->offset_y);
			line = line->right;
		}
		tmp = tmp->down;
	}
}

void	display_img(t_par *p)
{
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	get_iso_coord(p->map, p);
	create_image(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, p->img_orix, p->img_oriy);
	mlx_key_hook(p->win, &keys, p);
	mlx_loop(p->mlx);
}

void	init_display(t_par *p)
{
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, PRG_NAME);
	display_img(p);
}
