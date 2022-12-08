/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 17:16:10 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/08 21:32:26 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_error(const char *msg)
{
	ft_print_msg(msg);
	exit(0);
}

/* This function saves a map as a char** array. 
It also checks whether the map is rectangular. 
*/
void	save_map(t_data *d, int fd)
{
	int	y;
	int	x;
	int	read_ret;

	d->map = (char **)ft_safe_malloc(sizeof(char *) * d->map_len);
	y = 0;
	read_ret = 0;
	while (y < d->map_len)
	{
		x = 0;
		d->map[y] = (char *)ft_safe_malloc(sizeof(char) * (d->map_width + 1));
		while (x < d->map_width)
		{
			read_ret += read(fd, &(d->map[y][x]), 1);
			x++;
		}
		read_ret += read(fd, &(d->map[y][x]), 1);
		if (d->map[y][x] != '\n' && y != d->map_len - 1)
			ft_print_error("Map is not rectangular.\n");
		d->map[y][x] = '\0';
		y++;
	}
	if (read_ret != ((d->map_width + 1) * d->map_len) - 1)
		ft_print_error("Last line of map is faulty. Trailing newlines?\n");
	return ;
}

/* This function stores the length and width of our map in our datastruct.
It also stores the total number of collectables it encounters.
It re-opens the map. */
void	get_map_dimensions(t_data *d, int *fd)
{
	int		read_ret;
	char	buf;

	d->map_width = 0;
	d->map_len = 0;
	d->num_collectables = 0;
	read_ret = 1;
	while (read_ret == 1)
	{
		read_ret = read(*fd, &buf, 1);
		if (read_ret < 0)
			ft_print_error("Error whilst reading from file.\n");
		if (buf == 'C')
			d->num_collectables++;
		if (read_ret == 0 || buf == '\n')
			d->map_len++;
		if (d->map_len == 0)
			d->map_width++;
	}
	close(*fd);
	*fd = open(d->map_file, O_RDONLY);
	if (fd < 0)
		ft_print_error("Could not open map file.\n");
}
// if (buf != '\n' && buf != '1' && buf != '0' && buf != 'C' && buf != 'P' \
// 	&& buf != 'E')
// 	ft_print_error("Map contains illegal characters.\n");

/* This function will exit() if an error is encountered, 
or init our data struct with the relevant information if not.
It checks the correct number of args are passed.
It opens the map.
It checks the map is '.ber' type.
It calls get_map_dimensions.
It calls save_map.
It calls check_map_validity.
*/
void	parsing(t_data *d, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		ft_print_error("Please provide exactly one argument.\n");
	d->map_file = argv[1];
	if (ft_strlen(d->map_file) < 4 || \
		ft_strcmp(d->map_file + ft_strlen(d->map_file) - 4, ".ber"))
		ft_print_error("Map must be \".ber\" type.\n");
	fd = open(d->map_file, O_RDONLY);
	if (fd < 0)
		ft_print_error("Could not open map file.\n");
	get_map_dimensions(d, &fd);
	save_map(d, fd);
	check_map_validity(d);
	return ;
}
