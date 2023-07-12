/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:35:03 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/07/10 13:20:19 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mouse_handler(double xpos, double ypos, void *param)
{
	t_struct	*cub;

	cub = (t_struct *)param;
	(void)ypos;
	if (xpos > cub->old_x && cub->Mouse_mode % 2 == 1)
		cub->player->turnDirection = 1;
	else if (xpos < cub->old_x && cub->Mouse_mode % 2 == 1)
		cub->player->turnDirection = -1;
	cub->old_x = xpos;
	move_player(cub);
	return (0);
}

void	key_hendler_v2(t_struct *cub)
{
	float	newplayerx;
	float	newplayery;

	newplayerx = 0;
	newplayery = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		newplayerx += cos(cub->player->rotationAngle + M_PI / 2) * 0.2;
		newplayery += sin(cub->player->rotationAngle + M_PI / 2) * 0.2;
	}
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		newplayerx += cos(cub->player->rotationAngle - M_PI / 2) * 0.2;
		newplayery += sin(cub->player->rotationAngle - M_PI / 2) * 0.2;
	}
	if (has_wall_at(cub, newplayerx + cub->player->x, newplayery
			+ cub->player->y) == false)
	{
		cub->player->x += newplayerx;
		cub->player->y += newplayery;
	}
}

void	key_hendler(t_struct *cub)
{
	cub->player->walkDirection = 0;
	cub->player->turnDirection = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub->player->walkDirection = 1;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub->player->walkDirection = -1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player->turnDirection = 1;
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player->turnDirection = -1;
	key_hendler_v2(cub);
}

int	key_press(mlx_key_data_t keydata, void *param)
{
	t_struct	*cub;

	cub = (t_struct *)param;
	(void)keydata;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_M))
		cub->HIDE_MAP++;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_TAB))
		cub->Mouse_mode++;
	if (cub->Mouse_mode % 2 == 0)
		mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
	else
		mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_DISABLED);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_E))
		cub->close_dor++;
	return (0);
}
