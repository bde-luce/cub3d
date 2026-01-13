#include "../inc/cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return;
	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void clear_image(t_game *game)
{
	for (int y = 0; y < WIN_H; y++)
		for (int x = 0; x <WIN_W; x++)
			put_pixel(x, y, 0, game);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}
