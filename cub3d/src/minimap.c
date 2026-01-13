#include "../inc/cub3d.h"

void draw_map(t_game *game, int *out_scale)
{
	char **map = game->map;
	int color = 0x0000FF;
	
	// Count map dimensions
	int map_height = 0;
	int map_width = 0;
	while (map[map_height])
	{
		int len = ft_strlen(map[map_height]);
		if (len > map_width)
			map_width = len;
		map_height++;
	}
	
	// Calculate scale to fit window
	int scale_x = WIN_W / map_width;
	int scale_y = WIN_H / map_height;
	int scale = (scale_x < scale_y) ? scale_x : scale_y;
	
	if (scale < 1)
		scale = 1;
	
	*out_scale = scale; // Return the scale for use elsewhere
	
	// Draw scaled map
	for (int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * scale, y * scale, scale, color, game);
}

void draw_minimap_player(t_game *game, int scale)
{
	// Draw player at correct scale
	int player_x = (game->player.x / BLOCK) * scale;
	int player_y = (game->player.y / BLOCK) * scale;
	draw_square(player_x, player_y, 10, 0x00FF00, game);
}

void draw_minimap_ray(float ray_x, float ray_y, int scale, t_game *game)
{
	// Scale the ray position for minimap
	int scaled_x = (ray_x / BLOCK) * scale;
	int scaled_y = (ray_y / BLOCK) * scale;
	put_pixel(scaled_x, scaled_y, 0xFF0000, game);
}
