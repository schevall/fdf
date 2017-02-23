/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:10:24 by schevall          #+#    #+#             */
/*   Updated: 2017/02/23 19:31:52 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	color_tab(t_par *p)
{
	unsigned int	color;
	int				index;

	index = p->color % 5;
	if (index == 0)
		color = mlx_get_color_value(p->mlx, WHITE);
	if (index == 1)
		color = mlx_get_color_value(p->mlx, RED);
	if (index == 2)
		color = mlx_get_color_value(p->mlx, GREEN);
	if (index == 3)
		color = mlx_get_color_value(p->mlx, BLUE);
	if (index == 4)
		color = mlx_get_color_value(p->mlx, BLACK);
	return (color);
}

void			change_contrast(t_par *p)
{
	char		*tmp;
	int			max;
	int			i;

	i = 0;
	max = p->width * p->height;
	tmp = p->mem;
	while (i < max)
	{
		*(int*)tmp = mlx_get_color_value(p->mlx, WHITE);
		i++;
		tmp += 4;
	}
}
