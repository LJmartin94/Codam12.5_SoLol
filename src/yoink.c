/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   yoink.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 00:40:08 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/12/09 18:19:57 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int	yoink(t_data *d)
{
	mlx_t		*mlx;
	int			width;
	int			height;
	t_coords	unit_dims;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_setting(MLX_FULLSCREEN, true); //Cinematic, baby!
	mlx = mlx_init(2560, 1440, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	unit_dims = (t_coords){width / d->map_width, height / d->map_len};
	printf("width: %d, height: %d, unit.x: %d, unit.y: %d\n", width, height, unit_dims.x, unit_dims.y);
	width = d->map_width * unit_dims.x;
	height = d->map_len * unit_dims.y;
	printf("width: %d, height: %d, unit.x: %d, unit.y: %d\n", width, height, unit_dims.x, unit_dims.y);

	mlx_set_window_size(mlx, width, height);

	width = mlx->width;
	height = mlx->height;
	


	
	g_img = mlx_new_image(mlx, unit_dims.x, unit_dims.y);
	mlx_image_t *wall;
	wall = mlx_new_image(mlx, unit_dims.x, unit_dims.y);
	memset(wall->pixels, 255, wall->width * wall->height * sizeof(int));

	int i = 0;
	while (i < d->map_width * d->map_len)
	{
		t_coords here = (t_coords){i % d->map_width, i / d->map_width};
		if (d->map[here.y][here.x] == '1')
			mlx_image_to_window(mlx, wall, here.x * unit_dims.x, \
			here.y * unit_dims.y);
		i++;
	}
	
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, d->player.x * unit_dims.x, d->player.y * unit_dims.y);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}