/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:49:01 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/12/10 15:49:02 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include <math.h>

#define PI 3.14159265

# define WIDTH 320
# define HEIGHT 200
# define FOV 60
# define PLAYER_HEIGHT 32
# define WALL_HEIGHT 64

typedef short bool;

# define true 1;
# define false 0;

typedef struct	s_vector
{
	float x;
	float y;
}				t_vector;

typedef struct	s_wolf
{
	t_vector	player_dir;
	t_vector	center;
	int			distance;
	float		rays_angle;
	SDL_Window	*window;
	SDL_Event 	event;
	int			running;
}				t_wolf;




#endif