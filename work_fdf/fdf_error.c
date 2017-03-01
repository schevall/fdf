/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 12:21:15 by schevall          #+#    #+#             */
/*   Updated: 2017/03/01 15:11:20 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_error(int mode, char *error)
{
	if (mode == 1)
		ft_putendl_fd("Usage : ./fdf <filename>", 2);
	else if (mode == 2)
	{
		ft_putstr_fd("Error in file the line [", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd("] is irregular", 2);
	}
	else if (mode == 3)
	{
		ft_putstr_fd(error, 2);
		ft_putendl_fd(" : Open error", 2);
	}
	else if (mode == 4)
		ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}
