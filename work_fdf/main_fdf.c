/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:30:47 by schevall          #+#    #+#             */
/*   Updated: 2017/02/20 17:52:32 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keys(int keycode, t_par *p)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	/**
	 * 124 = droite
	 * 123 = gauche 
	 * 125 = bas
	 * 126 = haut
	 **/
	else if (keycode == 123)
		p->img_orix -= 10;
	else if (keycode == 124)
		p->img_orix += 10;
	else if (keycode == 125)
		p->img_oriy += 10;
	else if (keycode == 126)
		p->img_oriy -= 10;
	else if (keycode == 78)
	{
		p->img_orix += 10;
		p->img_oriy += 10;
		p->zoom--;
	}
	else if (keycode == 69)
	{
		p->img_orix -= 10;
		p->img_oriy -= 10;
		p->zoom++;
	}
	mlx_clear_window(p->mlx, p->win);
	mlx_destroy_image(p->mlx, p->img);
	display_img(p);
	return (0);
}

void	get_spec(t_par *p)
{
	t_coord *map;

	map = p->map;
	while (map->down)
		map = map->down;
	while (map->right)
		map = map->right;
	p->max_x = map->x + 1;
	p->max_y = map->y + 1;
	p->zoom = 10;
	p->offset_x = p->max_x;
	p->offset_y = p->max_y;
	p->img_orix = 1;
	p->img_oriy = 1;
}

int		main(int ac, char **av)
{
	int		fd;
	t_par	par;

	if (ac != 2)
		fdf_error(1, NULL);
	if (!(fd = open(av[1], O_RDONLY)))
		fdf_error(3, av[1]);

	parsing(fd, &par);
	get_spec(&par);
	init_display(&par);
	return (0);
}
