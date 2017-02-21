/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:30:47 by schevall          #+#    #+#             */
/*   Updated: 2017/02/21 18:12:55 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keys(int keycode, t_par *p)
{
	ft_printf("keycode = %d\n", keycode);
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	/**
	 * 124 = droite
	 * 123 = gauche 
	 * 125 = bas
	 * 126 = haut
	 **/
	else if (keycode == 123)
		p->offset_x -= 10;
	else if (keycode == 124)
		p->offset_x += 10;
	else if (keycode == 125)
		p->offset_y += 10;
	else if (keycode == 126)
		p->offset_y -= 10;
	else if (keycode == 78)
		p->zoom--;
	else if (keycode == 69)
		p->zoom++;
	else if (keycode == 8)
		p->color++;
	else if (keycode == 9)
	{
		if (p->color_variato)
			p->color_variato = 0;
		else
			p->color_variato = 1;
	}
	else if (keycode == 6)
		p->z_pad = -1;
	else if (keycode == 7)
		p->z_pad = 1;
	ft_printf("variato = %d\n", p->color_variato);
	mlx_clear_window(p->mlx, p->win);
	mlx_destroy_image(p->mlx, p->img);
	display_img(p);
	return (0);
}

void	get_spec(t_par *p)
{
	t_coord *map;
	t_coord *line;

	ft_printf("init get_spec\n");
	p->max_x = 0;
	p->max_y = 0;
	p->max_z = 0;
	p->color = 0;
	p->color_variato = 0;
	p->z_pad = 0;
	map = p->map;
	while (map->down)
	{
		line = map;
		while (line->right)
		{
			if (p->max_z < ft_abs(line->z))
				p->max_z = ft_abs(line->z);
			line = line->right;
		}
		if (p->max_x < line->x + 1)
			p->max_x = line->x + 1;
		map = map->down;
	}
	p->max_y = map->y + 1;
	ft_printf("max y = %d, max x = %d, max z = %d\n", p->max_y, p->max_x, p->max_z);

	if (p->max_x * p->max_y > WIDTH)
	{
		p->zoom = p->max_x * p->max_y / (WIDTH * 3);
		p->offset_x = 14 * p->max_x / 10;
		p->offset_y = 4 * p->max_y / 10;
	}
	else
	{
		p->zoom = 2 + WIDTH / (p->max_x * p->max_y);
		p->offset_x = 42 * p->max_x / 10;
		p->offset_y = 28 * p->max_y / 10;
	}
	ft_printf("zoom = %d\n", p->zoom);
	ft_printf("offset_x = %d, offset_y = %d\n", p->offset_x, p->offset_y);
	p->img_size = 4 * p->zoom * (int)(hypot(p->max_x, p->max_y) + 0.5);
	ft_printf("map height = %d\n", p->img_size);
	ft_printf("GREEN = %d, BROnW = %d, BLUE = %d\n", GREEN, BROWN, BLUE);
	ft_printf("xGREEN = %x, xBROnW = %x, xBLUE = %x\n", GREEN, BROWN, BLUE);
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
