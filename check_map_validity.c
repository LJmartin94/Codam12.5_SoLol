/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_validity.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 19:56:31 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/08 20:07:34 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check if there is a requered amount of valid characters 
//(1 exit, at least 1 collectable, 1 player)


/* Checks whether the top & bottom - as well as the left & right -
map edges are entirely '1's, i.e. walled off.
It errors and exits if not. */
void	check_walls(t_data *d)
{
	int i = 0;
	while (i < d->map_width)
	{
		if (d->map[0][i] != '1' || d->map[d->map_len - 1][i] != '1')
			ft_print_error("Map is not properly walled off.\n");
		i++;
	}
	i = 0;
	while (i < d->map_len)
	{
		if (d->map[i][0] != '1' || d->map[i][d->map_width - 1] != '1')
			ft_print_error("Map is not properly walled off.\n");
		i++;
	}
	return ;
}

// exit and all of the collectables are reachable

void	check_map_validity(t_data *d)
{
	check_walls(d);
	return ;
}
