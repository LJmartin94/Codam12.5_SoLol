/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 17:12:24 by limartin      #+#    #+#                 */
/*   Updated: 2022/12/07 18:30:00 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* Includes */
# include <stdio.h> // size_t
# include <unistd.h> // write(), read()
# include <stdlib.h> // exit(), malloc()
# include <fcntl.h> // open()

/* Data structs */
typedef struct s_data
{
	char	*map_file;
	char	**map;
	int		map_len;
	int		map_width;
}	t_data;

/* Prototypes */
//utils.c
size_t	ft_strlen(const char *str);
void	ft_print_msg(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
void	*ft_safe_malloc(size_t size);

//parsing.c
void	parsing(t_data *d, int argc, char **argv);

#endif