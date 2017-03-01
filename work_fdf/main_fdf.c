/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:30:47 by schevall          #+#    #+#             */
/*   Updated: 2017/03/01 15:18:13 by schevall         ###   ########.fr       */
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
	p->div_ratio_x = 1;
	p->div_ratio_y = 1;
}

void	get_ratio_for_big_map(t_par *p)
{
	ft_printf("init get_ratio_for_big_map\n");
	while (((p->max_xs - p->min_xs) / p->div_ratio_x) > WIDTH)
		p->div_ratio_x++;
	while (((p->max_ys - p->min_ys) / p->div_ratio_y) > HEIGHT)
		p->div_ratio_y++;
	ft_printf("div_ratio_x = %d, div_ratio_y = %d\n", p->div_ratio_x,
			p->div_ratio_y);
	p->ratio_x = 1;
	p->ratio_y = 1;
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
	t_par	p;

	if (ac != 2)
		fdf_error(1, NULL);
	if ((fd = open(av[1], O_RDONLY)) <= 0)
		fdf_error(3, av[1]);
	parsing(fd, &p);
	close(fd);
	init_img_spec(&p, 1);
	get_coord(&p);
	if (p.max_xs - p.min_xs > WIDTH || p.max_ys - p.min_ys > HEIGHT)
		get_ratio_for_big_map(&p);
	else
		get_ratio(&p);
	get_new_coord(&p);
	p.mlx = mlx_init();
	display_img(&p, 1);
	return (0);
}
