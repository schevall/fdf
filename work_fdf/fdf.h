/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:29:16 by schevall          #+#    #+#             */
/*   Updated: 2017/02/20 17:52:40 by schevall         ###   ########.fr       */
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

# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define WIDTH 2500
# define HEIGHT 1300

typedef struct	s_coord
{
	int				x;
	int				y;
	int				z;
	int				X;
	int				Y;
	int				color;
	struct s_coord	*right;
	struct s_coord	*down;
}				t_coord;

typedef struct	s_par
{
	void			*mlx;
	void			*win;
	t_coord			*map;
	size_t			zoom;
	int				img_orix;
	int				img_oriy;
	int				max_x;
	int				max_y;
	int				img_w;
	int				img_h;
	int				offset_x;
	int				offset_y;
	void			*img;
	char			*mem;
	int				bpp;
	int				sline;
	int				endian;
}				t_par;

void	parsing(int fd, t_par *p);
void	init_display(t_par *p);
void	display_img(t_par *par);
void	init_fdf_params(void *mlx_p, void *win_p, t_par *params);
int		keys(int keycode, t_par *p);
void	fdf_error(int mode, char *error);

#endif
