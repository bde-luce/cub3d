/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:08:42 by bde-luce          #+#    #+#             */
/*   Updated: 2026/01/23 16:08:42 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * Handles key press events for the player.
 */
int	key_press(int keycode, t_config *config)
{
	t_player	*player;

	player = &config->game.player;
	if (keycode == 65307)
	{
		cleanup_mlx(config);
		free_config(config);
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

/**
 * Handles key press events for the player.
 */
int	key_release(int keycode, t_config *config)
{
	t_player	*player;

	player = &config->game.player;
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

/**
 * Handles key press events for the player.
 */
int	handle_close(void *param)
{
	t_config	*config;

	config = (t_config *)param;
	cleanup_mlx(config);
	free_config(config);
	exit(0);
}
