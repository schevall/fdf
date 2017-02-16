/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:30:47 by schevall          #+#    #+#             */
/*   Updated: 2017/02/16 17:12:11 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		my_keys(int keycode, void *params)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	params++;
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;
	t_coord *map;

	if (ac != 2)
		fdf_error(1, NULL);
	if (!(fd = open(av[1], O_RDONLY)))
		fdf_error(3, av[1]);

	map = parsing(fd);
	display(map);
	return (0);
}
