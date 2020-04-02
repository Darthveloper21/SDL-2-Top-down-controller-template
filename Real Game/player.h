#ifndef PLAYER_H
#define PLAYER_H
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

class player
{
private:
    SDL_Rect cropRect;
    SDL_Texture* texture;
    float move_speed;
    float frame_counter;
    int frame_width, frame_height;
    int texture_width, texture_height;
    bool active;
    SDL_Scancode keys[4];

public:
    player(SDL_Renderer* renderer, string filepath, int x, int y, int framex, int framey);
    virtual ~player();

    void update(float delta, const Uint8 *keyState);
    void draw(SDL_Renderer* renderer);
    SDL_Rect position_rect;

protected:
};

#endif // PLAYER_H
