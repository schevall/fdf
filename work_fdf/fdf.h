/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:29:16 by schevall          #+#    #+#             */
/*   Updated: 2017/02/28 16:34:12 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>

# define PRG_NAME "Fdf"

# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLACK 0x000000
# define BLUE 0x000000FF

# define WIDTH 2500
# define HEIGHT 1300

typedef struct	s_coord
{
	int				x;
	int				y;
	int				z;
	int				xs;
	int				ys;
	int				elev;
	struct s_coord	*right;
	struct s_coord	*down;
}				t_coord;

typedef struct	s_segment
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		x_incr;
	int		y_incr;
	int		e1;
	int		e2;
}				t_segment;

typedef struct	s_par
{
	void			*mlx;
	void			*win;
	t_coord			*map;
	void			*img;
	char			*mem;
	int				bpp;
	int				sline;
	int				endian;
	int				color;
	int				color_img;
	int				max_xs;
	int				max_ys;
	int				min_xs;
	int				min_ys;
	int				ratio_x;
	int				ratio_y;
	int				width;
	int				height;
	int				z_pad;
	int				ratio_z;
	int				coord_type;
}				t_par;

void			parsing(int fd, t_par *p);
void			init_display(t_par *p);
void			display_img(t_par *par, int mode);
int				keys(int keycode, t_par *p);
void			fdf_error(int mode, char *error);
void			get_coord(t_par *p);
void			get_ratio(t_par *p);
void			get_new_coord(t_par *p);
unsigned int	color_tab(t_par *p);
void			change_contrast(t_par *p);

#endif
