/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:14:29 by schevall          #+#    #+#             */
/*   Updated: 2017/02/23 19:37:01 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_min_max(int x, int y, t_par *p)
{
	if (x < p->min_xs)
		p->min_xs = x;
	else if (x > p->max_xs)
		p->max_xs = x;
	if (y < p->min_ys)
		p->min_ys = y;
	else if (y > p->max_ys)
		p->max_ys = y;
}

void	get_coord(t_par *p)
{
	t_coord *tmp;
	t_coord *l;

	tmp = p->map;
	while (tmp)
	{
		l = tmp;
		while (l)
		{
			if (p->coord_type % 2)
			{
				l->xs = l->x - l->y;
				l->ys = l->x + l->y - (l->z / p->z_pad);
			}
			else
			{
				l->xs = l->x + (l->z / p->z_pad) * 2;
				l->ys = l->y + l->z / p->z_pad;
			}
			get_min_max(l->xs, l->ys, p);
			l = l->right;
		}
		tmp = tmp->down;
	}
}

void	get_offset_and_zoom(t_par *p)
{
	t_coord *tmp;
	t_coord *point;

	while (((p->max_xs - p->min_xs) * p->ratio_x) > p->width)
		p->ratio_x--;
	p->width = (p->max_xs - p->min_xs + 1) * p->ratio_x;
	while (((p->max_ys - p->min_ys) * p->ratio_y) > p->height)
		p->ratio_y--;
	p->height = (p->max_ys - p->min_ys + 1) * p->ratio_y;
	tmp = p->map;
	while (tmp)
	{
		point = tmp;
		while (point)
		{
			point->xs = (point->xs - p->min_xs) * p->ratio_x;
			point->ys = (point->ys - p->min_ys) * p->ratio_y;
			point = point->right;
		}
		tmp = tmp->down;
	}
}
