/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:30:47 by schevall          #+#    #+#             */
/*   Updated: 2017/02/23 19:38:20 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keys(int keycode, t_par *p)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	else if (keycode == 8)
		p->color++;
	else if (keycode == 6 && p->z_pad > 1)
		p->z_pad--;
	else if (keycode == 7 && p->z_pad < 10)
		p->z_pad++;
	else if (keycode == 11)
		p->coord_type++;
	else if (keycode == 9)
		p->color_img++;
	mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_image(p->mlx, p->img);
	display_img(p);
	return (0);
}

void	init_img_spec(t_par *p)
{
	p->ratio_x = 20;
	p->ratio_y = 20;
	p->width = WIDTH;
	p->height = HEIGHT;
	p->max_xs = 0;
	p->max_ys = 0;
	p->min_xs = INT_MAX;
	p->min_ys = INT_MAX;
	p->color = 0;
	p->z_pad = 3;
	p->coord_type = 1;
	p->color_img = 1;
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
	close(fd);
	init_img_spec(&par);
	get_coord(&par);
	get_offset_and_zoom(&par);
	display_img(&par);
	return (0);
}
