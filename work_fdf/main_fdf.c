/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:30:47 by schevall          #+#    #+#             */
/*   Updated: 2017/02/28 14:58:39 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_img_spec(t_par *p, int mode)
{
	if (mode == 1)
	{
		p->color = 0;
		p->z_pad = 0;
		p->coord_type = 1;
		p->color_img = 1;
		p->ratio_z = 1;
	}
	p->ratio_x = 20;
	p->ratio_y = 20;
	p->width = WIDTH;
	p->height = HEIGHT;
	p->max_xs = INT_MIN;
	p->max_ys = INT_MIN;
	p->min_xs = INT_MAX;
	p->min_ys = INT_MAX;
}

int		keys(int keycode, t_par *p)
{
	ft_printf("keycode = %d\n", keycode);
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	else if (keycode == 8)
		p->color++;
	else if (keycode == 11)
		p->coord_type++;
	else if (keycode == 9)
		p->color_img++;
	else if (keycode == 6)
		p->z_pad = -2;
	else if (keycode == 7)
		p->z_pad = 2;
	else if (keycode == 0 && p->ratio_z > -15)
		p->ratio_z -= 2;
	else if (keycode == 1 && p->ratio_z < 15)
		p->ratio_z += 2;
	if (keycode != 6 && keycode != 7)
		p->z_pad = 0;
	init_img_spec(p, 2);
	mlx_destroy_window(p->mlx, p->win);
	display_img(p, 2);
	return (0);
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
	init_img_spec(&par, 1);
	get_coord(&par);
	get_ratio(&par);
	get_new_coord(&par);
	par.mlx = mlx_init();
	display_img(&par, 1);
	return (0);
}
