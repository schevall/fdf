/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:10:24 by schevall          #+#    #+#             */
/*   Updated: 2017/02/24 18:53:59 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	color_tab(t_par *p)
{
	int				index;

	index = p->color % 5;
	if (index == 0)
		return (mlx_get_color_value(p->mlx, WHITE));
	else if (index == 1)
		return (mlx_get_color_value(p->mlx, RED));
	else if (index == 2)
		return (mlx_get_color_value(p->mlx, GREEN));
	else if (index == 3)
		return (mlx_get_color_value(p->mlx, BLUE));
	else
		return (mlx_get_color_value(p->mlx, BLACK));
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

unsigned int	color_with_z(t_coord *ori, t_coord *dest, t_par *p)
{
	if (ori->z == 0 && dest->z == 0)
		return (mlx_get_color_value(p->mlx, GREEN));
	else if (ori->z < 0 || dest->z < 0)
		return (mlx_get_color_value(p->mlx, BLUE));
	else if ((ori->z > 0 && ori->z < 6) || (dest->z > 0 && dest->z < 6))
		return (mlx_get_color_value(p->mlx, BROWN));
	else
		return (mlx_get_color_value(p->mlx, WHITE));
}
