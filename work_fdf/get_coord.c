/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:14:29 by schevall          #+#    #+#             */
/*   Updated: 2017/02/24 18:37:54 by schevall         ###   ########.fr       */
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

void	get_elevation(t_coord *l, t_par *p)
{
	if (l->z != 0)
		l->elev = 1;
	if (l->elev && (l->z < 50 || p->z_pad == -2) &&
			(l->z > -50 || p->z_pad == 2))
		l->z += p->z_pad;
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
			get_elevation(l, p);
			if (p->coord_type % 2)
			{
				l->xs = 2 * l->x - 2 * l->y;
				l->ys = l->x + l->y - (l->z * p->ratio_z);
			}
			else
			{
				l->xs = l->x + l->z / p->ratio_z;
				l->ys = l->y + l->z;
			}
			get_min_max(l->xs, l->ys, p);
			l = l->right;
		}
		tmp = tmp->down;
	}
}

void	get_ratio(t_par *p)
{
	while (((p->max_xs - p->min_xs) * p->ratio_x) > p->width)
		p->ratio_x--;
	p->width = (p->max_xs - p->min_xs + 1) * p->ratio_x;
	while (((p->max_ys - p->min_ys) * p->ratio_y) > p->height)
		p->ratio_y--;
	p->height = (p->max_ys - p->min_ys + 1) * p->ratio_y;
	if (p->height <= 0 || p->width <= 0)
		fdf_error(4, "Something gone weird with this map");
}

void	get_new_coord(t_par *p)
{
	t_coord *tmp;
	t_coord *point;

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
