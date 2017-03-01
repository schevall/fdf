/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 12:34:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/01 15:11:55 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_coord	*add_point(int x, int y, char *line, int *i)
{
	t_coord *point;
	int		n;

	n = 0;
	if (!(point = (t_coord*)ft_memalloc(sizeof(t_coord))))
		fdf_error(4, "Malloc error");
	point->x = x;
	point->y = y;
	line += *i;
	point->z = ft_atoi(line);
	if (line[n] == '+' || line[n] == '-')
		n++;
	while (ft_isdigit(line[n]))
		n++;
	if (line[n] == ',')
		n += 9;
	if (line[n] != ' ' && line[n] != '\0')
		fdf_error(4, "Map error");
	*i += n;
	return (point);
}

static int		parse_line(char *line, t_coord **map, int y)
{
	int		x;
	int		i;

	x = 0;
	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else
		{
			*map = add_point(x, y, line, &i);
			map = &((*map)->right);
			x++;
		}
	}
	if (x == 0)
		fdf_error(4, "Map error, one line has no coord");
	return (1);
}

static void		make_map(int fd, t_coord **map)
{
	char	*line;
	int		y;

	y = 0;
	ft_printf("fd = %d\n", fd);
	while (get_next_line(fd, &line) == 1)
	{
		parse_line(line, map, y);
		map = &((*map)->down);
		y++;
		ft_strdel(&line);
	}
	if (y == 0)
		fdf_error(4, "Map error, y = 0");
}

static void		link_point(t_coord *map)
{
	t_coord	*current;
	t_coord *below;

	while (map)
	{
		current = map;
		below = map->down;
		while (current && below)
		{
			current->down = below;
			current = current->right;
			below = below->right;
		}
		map = map->down;
	}
}

void			parsing(int fd, t_par *p)
{
	t_coord		*map;

	ft_printf("Init parsing\n");
	make_map(fd, &map);
	link_point(map);
	p->map = map;
	ft_printf("Parsing is finished\n");
}
