#include "../inc/cub3d.h"

float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

bool touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;

	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	move_player(t_player *player, t_game *game)
{
	int speed = 5;
	float angle_speed = 0.04;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;

	if (player->right_rotate)
		player->angle += angle_speed;
	
	float new_x = player->x;
	float new_y = player->y;

	if (player->angle > 2 * PI)
		player->angle = 0;
	
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (player->key_down)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		new_x += sin_angle * speed;
		new_y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		new_x -= sin_angle * speed;
		new_y += cos_angle * speed;
	}

	if (!touch(new_x, player->y, game))
        player->x = new_x;
    if (!touch(player->x, new_y, game))
        player->y = new_y;
}
