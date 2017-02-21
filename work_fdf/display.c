/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/21 18:12:51 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	color_tab(t_par *p)
{
	unsigned int color;
	int index;

	index = p->color % 4;
	if (index == 0)
		color = mlx_get_color_value(p->mlx, WHITE);
	if (index == 1)
		color = mlx_get_color_value(p->mlx, RED);
	if (index == 2)
		color = mlx_get_color_value(p->mlx, GREEN);
	if (index == 3)
		color = mlx_get_color_value(p->mlx, BLUE);
	return (color);
}

void	get_color_spec(t_coord *point)
{
	int z;

	z = -1 * point->z;
	if (z < 0)
		point->color = BLUE;
	else if (z == 0)
		point->color = GREEN;
	else if (z > 0)
		point->color = BROWN;

}

void	put_pixel(int X, int Y, int color, t_par *p)
{
	char *mem_tmp;

	
//	ft_printf("init init put_pixel, X = %d, Y = %d\n", X, Y);
	if ((X > 0 && X < (WIDTH / 8)) || (Y > 0 && Y < HEIGHT))
	{
		mem_tmp = p->mem + p->bpp/8 * X + p->sline * Y;
		if (p->color_variato)
			*(int*)mem_tmp = mlx_get_color_value(p->mlx, color);
		else
			*(int*)mem_tmp = color_tab(p);
	}
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

	int color;
	int color_gap;
	int	color_incr;

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
	color = ori->color;
	color_gap = ft_abs(ori->color - dest->color) / 256;
	if (Dx > Dy)
	{
		color_incr = color_gap / Dx / 256;
		while (i <= Dx)
		{
			put_pixel(x1, y1, color, par);
			color += color_incr;
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
		color_incr = color_gap / Dy / 256;
		while (i <= Dy)
		{
			put_pixel(x1, y1, color, par);
			color += color_incr;
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

//	ft_printf("init create_image\n");
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
//	ft_printf("end create_image\n");

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
			if (ft_abs(line->z) > 0)
				line->elevated = 1;
			if (line->elevated)
				line->z += p->z_pad;
			if (p->color_variato)
				get_color_spec(line);
			line->X = p->zoom * (2 * line->x - 2 * line->y + p->offset_x);
			line->Y = p->zoom * (line->z + line->x + line->y + p->offset_y);
			line = line->right;
		}
		tmp = tmp->down;
	}
//	ft_printf("end get_iso_coord\n");
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
