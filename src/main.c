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
    w->window = NULL;
    w->renderer = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &w->window, &w->renderer))
        exit (1);
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

    double posX = 22, posY = 12;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    // double time = 0; //time of current frame
    // double oldTime = 0; //time of previous frame

    while (w->running)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            //calculate ray position and direction
            double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            int mapX = (int)posX;
            int mapY = (int)posY;
        
            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;
        
             //length of ray from one x or y-side to next x or y-side
            double deltaDistX = fabs(1 / rayDirX);
            double deltaDistY = fabs(1 / rayDirY);
            double perpWallDist;
        
            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;
        
            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?
            if (rayDirX < 0)
            {
              stepX = -1;
              sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
              stepX = 1;
              sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
              stepY = -1;
              sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
              stepY = 1;
              sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            //perform DDA
            while (hit == 0)
            {
              //jump to next map square, OR in x-direction, OR in y-direction
              if (sideDistX < sideDistY)
              {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
              }
              else
              {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
              }
              //Check if ray has hit a wall
              if (worldMap[mapX][mapY] > 0) hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (side == 0) 
                perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else
                perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

            //Calculate height of line to draw on screen
            int lineHeight = (int)(HEIGHT / perpWallDist);
        
            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + HEIGHT / 2;
            if(drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2 + HEIGHT / 2;
            if(drawEnd >= HEIGHT)
                drawEnd = HEIGHT - 1;
            SDL_Color color;
            switch(worldMap[mapX][mapY])
            {
                case 1:  color.r = 255; color.g = 0; color.b = 0;  break; //red
                case 2:  color.r = 0; color.g = 128; color.b = 0;  break; //green
                case 3:  color.r = 0; color.g = 0; color.b = 255;   break; //blue
                case 4:  color.r = 255; color.g = 255; color.b = 255;  break; //white
                default: color.r = 255; color.g = 255; color.b = 0; break; //yellow
            }

            //give x and y sides different brightness
            if (side == 1) {color.r /= 2; color.g /= 2; color.b /= 2;}

            //draw the pixels of the stripe as a vertical line
            //verLine(x, drawStart, drawEnd, color);
            SDL_SetRenderDrawColor(w->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(w->renderer, x, drawStart, x, drawEnd);
            SDL_RenderPresent(w->renderer);
        }
        //timing for input and FPS counter
        // oldTime = time;
        // time = getTicks();
        // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
        // print(1.0 / frameTime); //FPS counter
        // redraw();
        // cls();

        //speed modifiers
        // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
        // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
        while (SDL_PollEvent(&w->event))
            if((SDL_QUIT == w->event.type) || (SDL_KEYDOWN == w->event.type 
                && SDL_SCANCODE_ESCAPE == w->event.key.keysym.scancode))
                    w->running = 0;
    }
        
    
    SDL_DestroyWindow(w->window);
    SDL_Quit();
    
    return (0);
}
