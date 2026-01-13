#include "../inc/cub3d.h"

void draw_line(t_player *player, t_game *game, float start_x, int i, int scale)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			draw_minimap_ray(ray_x, ray_y, scale, game);  // Use scale here
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (DEBUG)
		return;
	
	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	float height = (BLOCK / dist) * (WIN_W / 2);

	int wall_top = (WIN_H - height) / 2;
	int wall_bottom = wall_top + height;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > WIN_H)
		wall_bottom = WIN_H;
	
	/* CEILING */
	for (int y = 0; y < wall_top; y++)
		put_pixel(i, y, game->ceiling_color, game);

	/* WALL */
	for (int y = wall_top; y < wall_bottom; y++)
		put_pixel(i, y, WALL_COLOR, game);

	/* FLOOR */
	for (int y = wall_bottom; y < WIN_H; y++)
		put_pixel(i, y, game->floor_color, game);
}

int	draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(&game->player, game);
	clear_image(game);
	
	int scale = 1;
	if (DEBUG)
	{
		draw_map(game, &scale);
		draw_minimap_player(game, scale);
	}
	
	float fraction = PI / 3 / WIN_W;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIN_W)
	{
		draw_line(player, game, start_x, i, scale);  // Pass scale here
		start_x += fraction;
		i++;
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
