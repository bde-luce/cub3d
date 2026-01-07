/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:46:43 by bde-luce          #+#    #+#             */
/*   Updated: 2025/05/13 12:46:43 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../mlx_linux/mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../src/libft/libft.h"

# define WIN_W 800
# define WIN_H 600

typedef struct s_mlx
{
	void *mlx;
	void *win;
}	t_mlx;

typedef struct s_cub3d
{
	char	**file;
	char	**map;
	int		rows;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	t_mlx mlx;

}	t_cub3d;

// MLX
void	init_mlx(t_mlx *mlx);

// HOOKS
int 	handle_key(int keycode, void *param);
int		handle_close(void *param);

// PARSING
void	file_convert(t_cub3d *cub3d, char **argv);
void	map_validate(t_cub3d *map);
void	free_all(t_cub3d *map);

#endif