/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:29:16 by schevall          #+#    #+#             */
/*   Updated: 2017/02/15 17:54:09 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define PRG_NAME "Fdf"

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define WIDTH 2000
# define HEIGHT 1200
# define DEPTH 3
# define CTE 0.75;


typedef struct	s_coord
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_coord	*right;
	struct s_coord	*down;
}				t_coord;

typedef struct	s_par
{
	void			*mlx_p;
	void			*win_p;
	void			*img_p;
	char			*mem;
	int				bpp;
	int				sizeline;
	int				endian;
}				t_par;

t_coord	*parsing(int fd);
void	display(t_coord *map);
void	init_fdf_params(void *mlx_p, void *win_p, t_par *params);
int		my_keys(int keycode, void *params);
void	fdf_error(int mode, char *error);

#endif
