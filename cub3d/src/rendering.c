#include "../inc/cub3d.h"

static int get_side(float prev_x, float prev_y, float ray_x, float ray_y)
{
	int prev_cell_x;
	int prev_cell_y;
	int cell_x;
	int cell_y;

	prev_cell_x = (int)(prev_x / BLOCK);
	prev_cell_y = (int)(prev_y / BLOCK);
	cell_x = (int)(ray_x / BLOCK);
	cell_y = (int)(ray_y / BLOCK);
	if (prev_cell_x != cell_x)
		return (0);
	else if (prev_cell_y != cell_y)
		return (1);
	return (-1);
}

static void	get_right_tex(t_hit *hit, t_game *game)
{
	if (hit->side == 0)
	{
		if (hit->dir_x > 0)
			hit->tex = &game->ea;
		else
			hit->tex = &game->we;
	}
	else
	{
		if (hit->dir_y > 0)
			hit->tex = &game->so;
		else
			hit->tex = &game->no;
	}
}

static void	get_tex_x(t_hit *hit)
{
	float wallX;

	if (hit->side == 0)
		wallX = fmodf(hit->ray_y, BLOCK) / BLOCK;
	else
		wallX = fmodf(hit->ray_x, BLOCK) / BLOCK;
	if (wallX < 0)
		wallX += 1.0f;

	hit->tex_x = (int)(wallX * (hit->tex->width - 1));
	if (hit->tex_x < 0)
		hit->tex_x = 0;
	if (hit->tex_x >= hit->tex->width)
		hit->tex_x = hit->tex->width - 1;

	if ((hit->side == 0 && hit->dir_x < 0) || (hit->side == 1 && hit->dir_y > 0))
		hit->tex_x = hit->tex->width - 1 - hit->tex_x;
}

static void draw_texture_line(t_hit *hit, t_game *game)
{
	int lineHeight = hit->bottom - hit->top;
	float step = (float)hit->tex->height / (float)lineHeight;
	float texPos = (hit->top - WIN_H / 2.0f + lineHeight / 2.0f) * step;

	int y = hit->top;
	while (y < hit->bottom)
	{
		int texY = (int)texPos;

		if (texY < 0)
			texY = 0;
		if (texY >= hit->tex->height)
			texY = hit->tex->height - 1;

		int index = texY * hit->tex->size_line + hit->tex_x * (hit->tex->bpp / 8);
		int color = hit->tex->data[index] | (hit->tex->data[index + 1] << 8) | (hit->tex->data[index + 2] << 16);

		put_pixel(hit->screen_x, y, color, game);

		texPos += step;
		y++;
	}
}

static void	init_hit_ray(t_hit *hit, t_player *player, float angle, int screen_x)
{
	hit->ray_x = player->x;
	hit->ray_y = player->y;
	hit->dir_x = cos(angle);
	hit->dir_y = sin(angle);
	hit->screen_x = screen_x;
}

static void cast_ray(t_hit *hit, t_game *game, float start_x, int scale)
{
	float cos_angle;
	float sin_angle;
	float prev_x;
	float prev_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	prev_x = hit->ray_x;
	prev_y = hit->ray_y;

	while (!touch(hit->ray_x, hit->ray_y, game))
	{
		if (DEBUG)
			draw_minimap_ray(hit->ray_x, hit->ray_y, scale, game); // Use scale here
		prev_x = hit->ray_x;
		prev_y = hit->ray_y;
		hit->ray_x += cos_angle;
		hit->ray_y += sin_angle;
	}
	if (DEBUG)
		return;
	hit->side = get_side(prev_x, prev_y, hit->ray_x, hit->ray_y);
}

static void	compute_wall_slice(t_hit *hit, t_player *player, t_game *game)
{
	float dist;
	float height;

	dist = fixed_dist(player->x, player->y, hit->ray_x, hit->ray_y, game);
	height = (BLOCK / dist) * (WIN_W / 2);

	hit->top = (WIN_H - height) / 2;
	hit->bottom = hit->top + height;

	if (hit->top < 0)
		hit->top = 0;
	if (hit->bottom > WIN_H)
		hit->bottom = WIN_H;
}

void draw_line(t_player *player, t_game *game, float start_x, int i, int scale)
{
	t_hit	hit;
	int		y;

	init_hit_ray(&hit, player, start_x, i);
	cast_ray(&hit, game, start_x, scale);

	get_right_tex(&hit, game);
	get_tex_x(&hit);

	compute_wall_slice(&hit, player, game);

	// CEILING
	y = 0;
	while (y < hit.top)
		put_pixel(i, y++, game->ceiling_color, game);

	// WALL
	draw_texture_line(&hit, game);

	// FLOOR
	y = hit.bottom;
	while (y < WIN_H)
		put_pixel(i, y++, game->floor_color, game);
}

int draw_loop(t_game *game)
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
		draw_line(player, game, start_x, i, scale); // Pass scale here
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
