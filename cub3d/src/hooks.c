#include "../inc/cub3d.h"

int	key_press(int keycode, t_cub3d *cub3d)
{
	t_player *player = &cub3d->game.player;
	
	if (keycode == 65307)
	{
		cleanup_mlx(cub3d);
		free_all(cub3d);
		exit(0);
	}
	if (keycode == W)
		player->key_up = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_cub3d *cub3d)
{
	t_player *player = &cub3d->game.player;
	
	if (keycode == W)
		player->key_up = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

int	handle_key(int keycode, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (keycode == 65307)
	{
		cleanup_mlx(cub3d);
		free_all(cub3d);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	cleanup_mlx(cub3d);
	free_all(cub3d);
	exit(0);
	return (0);
}
