/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:59:41 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/12/10 15:59:42 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include "../include/wolf3d.h"

void initialize(t_wolf *w)
{
    w->center.x = WIDTH / 2;
    w->center.y = HEIGHT / 2;
    w->distance = w->center.x / tan(((FOV / 2) * PI) / 180.0);
    w->rays_angle = FOV / WIDTH;
    w->player_dir.x = 96;
    w->player_dir.y = 224;
    w->running = 1;
}

float count_Xa(float angle, int ya)
{
    return (ya / tan(angle * PI / 180.0));
}

int main()
{
    t_wolf *w;

    w = (t_wolf *)malloc(sizeof(t_wolf));

    initialize(w);

    SDL_Init(SDL_INIT_EVERYTHING);
    if (!(w->window = SDL_CreateWindow("Hello SDL World", 
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, 
    HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI)))
        exit (1);
    
    while (w->running)
    {
        SDL_PollEvent(&w->event);
        if((SDL_QUIT == w->event.type) || (SDL_KEYDOWN == w->event.type 
            && SDL_SCANCODE_ESCAPE == w->event.key.keysym.scancode))
                w->running = 0;
    }
        
    
    SDL_DestroyWindow(w->window);
    SDL_Quit();
    
    return (0);
}
