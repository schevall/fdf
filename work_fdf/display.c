/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:14:28 by schevall          #+#    #+#             */
/*   Updated: 2017/02/23 19:38:16 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(int x, int y, t_par *p)
{
	char		*mem_tmp;

	if ((x > 0 && x <= p->width) || (y > 0 && y <= p->height))
	{
		mem_tmp = p->mem + p->bpp / 8 * x + p->sline * y;
		*(int*)mem_tmp = color_tab(p);
	}
}

void	init_segment(t_segment *seg, t_coord *ori, t_coord *dest)
{
	seg->x = ori->xs;
	seg->y = ori->ys;
	seg->dx = ft_abs(dest->xs - ori->xs);
	seg->dy = ft_abs(dest->ys - ori->ys);
	seg->x_incr = ori->xs < dest->xs ? 1 : -1;
	seg->y_incr = ori->ys < dest->ys ? 1 : -1;
	seg->e1 = (seg->dx > seg->dy ? seg->dx : -(seg->dy)) / 2;
}

int		draw_segment(t_coord *ori, t_coord *dest, t_par *p)
{
	int			i;
	t_segment	s;

	i = 0;
	if (!dest || !ori)
		return (0);
	init_segment(&s, ori, dest);
	while (s.x != dest->xs || s.y != dest->ys)
	{
		put_pixel(s.x, s.y, p);
		s.e2 = s.e1;
		if (s.e2 > -s.dx)
		{
			s.e1 -= s.dy;
			s.x += s.x_incr;
		}
		if (s.e2 < s.dy)
		{
			s.e1 += s.dx;
			s.y += s.y_incr;
		}
	}
	return (1);
}

void	create_image(t_par *p)
{
	t_coord		*tmp;
	t_coord		*point;

	p->mem = mlx_get_data_addr(p->img, &(p->bpp), &(p->sline), &(p->endian));
	if (p->color_img % 2 != 1)
		change_contrast(p);
	tmp = p->map;
	while (tmp)
	{
		point = tmp;
		while (point)
		{
			put_pixel(point->xs, point->ys, p);
			draw_segment(point, point->right, p);
			draw_segment(point, point->down, p);
			point = point->right;
		}
		tmp = tmp->down;
	}
}

void	display_img(t_par *p)
{
	p->mlx = mlx_init();
	get_coord(p);
	get_offset_and_zoom(p);
	p->win = mlx_new_window(p->mlx, p->width + 20, p->height + 20, PRG_NAME);
	p->img = mlx_new_image(p->mlx, p->width, p->height);
	create_image(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 5, 5);
	mlx_key_hook(p->win, &keys, p);
	mlx_loop(p->mlx);
}
