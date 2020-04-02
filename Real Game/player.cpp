#include "player.h"
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 1344;
const int SCREEN_HEIGHT = 896;

player::player(SDL_Renderer* renderer, string filepath, int x, int y, int framex, int framey)
{
    SDL_Surface *surface = IMG_Load(filepath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
    position_rect.x = x;
    position_rect.y = y;

    texture_width = cropRect.w;
    texture_height = cropRect.h;
    cropRect.w /= framex;
    cropRect.h /= framey;

    frame_width = position_rect.w = cropRect.w;
    frame_height = position_rect.h = cropRect.h;

    active = false;

    static int player_number = 0;
    player_number++;

    if(player_number == 1)
    {
        keys[0] = SDL_SCANCODE_UP;
        keys[1] = SDL_SCANCODE_DOWN;
        keys[2] = SDL_SCANCODE_LEFT;
        keys[3] = SDL_SCANCODE_RIGHT;
    }
    else
    {
        keys[0] = SDL_SCANCODE_W;
        keys[1] = SDL_SCANCODE_S;
        keys[2] = SDL_SCANCODE_A;
        keys[3] = SDL_SCANCODE_D;
    }

    move_speed = 70.0f;
}

player::~player()
{
    SDL_DestroyTexture(texture);
}

void player::update(float delta, const Uint8 *keyState)
{
    active = true;
    if(keyState[keys[0]] && position_rect.y > 0) // up
    {
        position_rect.y -= move_speed * delta;
        cropRect.y = frame_height;
    }
    else if(keyState[keys[1]] && position_rect.y < SCREEN_HEIGHT - frame_height) // down
    {
        position_rect.y += move_speed * delta;
        cropRect.y = 0;
    }
    else if(keyState[keys[2]] && position_rect.x > 0) // left
    {
        position_rect.x -= move_speed * delta;
        cropRect.y = frame_height * 2;
    }
    else if(keyState[keys[3]] && position_rect.x < SCREEN_WIDTH - frame_width) // right
    {
        position_rect.x += move_speed * delta + 1;
        cropRect.y = frame_height * 3;
    }
    else active = false;

    if(active)
    {
        frame_counter += delta;

        if(frame_counter >= 0.25f)
        {
            frame_counter = 0;
            cropRect.x += frame_width;
            if(cropRect.x >= texture_width) cropRect.x = 0;
        }
    }
    else
    {
        frame_counter = 0;
        cropRect.x = 0;
    }
}

void player::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &cropRect, &position_rect);
}
