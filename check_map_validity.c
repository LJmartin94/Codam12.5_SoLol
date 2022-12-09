/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_validity.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 19:56:31 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/09 13:22:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* This function checks all positions reachable from a given starting position.
It decrements an integer passed to it by pointer, to keep track fo how many
Collectables, Players and Exits it can reach. When flood_fill completes,
the integer represents how many things could not be reached. A space that has 
been checked will be filled with a '1' on the map, 
so that it is not checked again.
*/
void	flood_fill(char **map, int *to_reach, t_coords pos)
{
	if (map[pos.y][pos.x] == '1')
		return ;
	if (map[pos.y][pos.x] == 'E' || map[pos.y][pos.x] == 'C' \
		|| map[pos.y][pos.x] == 'P')
		(*to_reach)--;
	map[pos.y][pos.x] = '1';
	flood_fill(map, to_reach, (t_coords){pos.x + 1, pos.y});
	flood_fill(map, to_reach, (t_coords){pos.x - 1, pos.y});
	flood_fill(map, to_reach, (t_coords){pos.x, pos.y + 1});
	flood_fill(map, to_reach, (t_coords){pos.x, pos.y - 1});
}

/* This function makes a copy of the existing map, as it is 'destroyed' in 
the process of checking (i.e. filled with '1's).
FOR NORME REASONS, it is null terminated in a terrible way, 
though it could also have been not null-terminated at all.
It then calls flood_fill, a recursive function which checks all positions 
reachable from the player's starting position.
If not all the collectables, the player position and the exit are reachable,
it returns an error.
After the map_copy is used up, it is freed.
*/
void	check_solvable(t_data *d)
{
	char		**map_copy;
	int			i;
	t_coords	here;

	map_copy = (char **)ft_safe_malloc(d->map_len * sizeof(char *));
	i = 0;
	while (i < (d->map_width * d->map_len))
	{
		here = (t_coords){i % d->map_width, i / d->map_width};
		if (here.x == 0)
			map_copy[here.y] = (char *)ft_safe_malloc(d->map_width + 1);
		map_copy[here.y][here.x] = d->map[here.y][here.x];
		map_copy[here.y][here.x + 1] = '\0';
		i++;
	}
	i = 2 + d->num_collectables;
	flood_fill(map_copy, &i, d->player);
	if (i != 0)
		ft_print_error("Map is not solveable!\n");
	while (i < d->map_len)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

/* This function stores the position of the collectables, the player and the 
exit. 
It also checks whether there are no duplicate player or exit characters,
whether there are no invalid characters,
and whether there is at least one collectable, player and exit.
*/
void	check_map_chars(t_data *d)
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
	check_map_chars(d);
	check_solvable(d);
	return ;
}
