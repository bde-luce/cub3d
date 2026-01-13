#include "../inc/cub3d.h"

int rgb_to_int(char *rgb)
{
    char **c;
    int r, g, b;
    int color;

    c = ft_split(rgb, ',');
    if (!c)
        return (-1);

    r = ft_atoi(c[0]);
    g = ft_atoi(c[1]);
    b = ft_atoi(c[2]);

    free_arr(c);

    color = (r << 16) | (g << 8) | b;
    return (color);
}

void	cleanup_mlx(t_cub3d *cub3d)
{
	if (cub3d->game.img)
		mlx_destroy_image(cub3d->game.mlx, cub3d->game.img);
	if (cub3d->game.win)
		mlx_destroy_window(cub3d->game.mlx, cub3d->game.win);
	if (cub3d->game.mlx)
	{
		mlx_destroy_display(cub3d->game.mlx);
		free(cub3d->game.mlx);
	}
}
