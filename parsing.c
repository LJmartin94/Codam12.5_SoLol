/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 17:16:10 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/02 19:59:37 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_print_error(const char *msg)
{
	ft_print_msg(msg);
	exit(0);
}

void	save_valid_map(t_data *d, int fd)
{
	char	*gnl_ret;
	int		i;

	i = 0;
	d->map_len = 0;
	gnl_ret = mini_gnl(fd);
	while (gnl_ret != NULL)
	{
		d->map[i] = gnl_ret;
		gnl_ret = mini_gnl(fd);
	}
	// while (gnl_ret != NULL)
	// {
	// 	d->map[i] = gnl_ret;
	// 	gnl_ret = mini_gnl(fd);
	// }
	return ;
}

void get_map_dimensions(t_data *d, int *fd)
{
	int read_ret;
	int	total_chars;
	char buf;

	d->map_width = 0;
	d->map_len = 0;
	while (d->map_len == 0)
	{
		read_ret = read(fd, &buf, 1);
		if (read_ret < 0)
			ft_print_error("Error whilst reading from file.\n");
		if (read_ret == 0 || buf == '\n')
			d->map_len++;
		d->map_width++;
	}
	
}

/* This function will exit() if an error is encountered, 
or init our data struct with the relevant information if not.*/
void	parsing(t_data *d, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		ft_print_error("Please provide exactly one argument.\n");
	if (ft_strlen(argv[1]) < 4 || \
		ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber"))
		ft_print_error("Map must be \".ber\" type.\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_print_error("Could not open map file.\n");
	get_map_dimensions(d, &fd);
	save_valid_map(d, fd);
	return ;
}

// save map as an array of strings (char **)
// check for invalid characters
// check if the map is rectangular (strs are equal length)
// check if there is a requered amount of valid characters 
//(1 exit, at least 1 collectable, 1 player)
// check if map is walled off 
//(top and bottom strings are walls, 
//first and the last char in other strings is a wall)
// exit and all of the collectables are reachable