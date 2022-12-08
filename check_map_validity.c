/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_validity.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 19:56:31 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/08 22:11:50 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* This function stores the position of the collectables, the player and the 
exit. It also checks whether there are no duplicate player or exit characters,
whether there are no invalid characters,
and whether there is at least one collectable, player and exit.
*/
void	check_required_chars(t_data *d)
{
	int			i;
	t_coords	here;

	i = 0;
	d->player.y = -1;
	d->exit.y = -1;
	d->collectables = \
	(t_coords *)ft_safe_malloc(d->num_collectables * sizeof(t_coords));
	d->num_collectables = 0;
	while (i < (d->map_width * d->map_len))
	{
		here = (t_coords){i % d->map_width, i / d->map_width};
		if (d->map[here.y][here.x] == 'C')
			d->collectables[d->num_collectables++] = here;
		else if (d->map[here.y][here.x] == 'P' && d->player.y == -1)
			d->player = here;
		else if (d->map[here.y][here.x] == 'E' && d->exit.y == -1)
			d->exit = here;
		else if (d->map[here.y][here.x] != '1' && d->map[here.y][here.x] != '0')
			ft_print_error("Map contains invalid charachters.\n");
		i++;
	}
	if (d->num_collectables == 0 || d->player.y == -1 || d->exit.y == -1)
		ft_print_error("Map is missing required characters.\n");
}

/* Checks whether the top & bottom - as well as the left & right -
map edges are entirely '1's, i.e. walled off.
It errors and exits if not. */
void	check_walls(t_data *d)
{
	int	i;

	i = 0;
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
	check_required_chars(d);
	return ;
}
