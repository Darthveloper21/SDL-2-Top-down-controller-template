#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "player.h"

using namespace std;

const int SCREEN_WIDTH = 1344;
const int SCREEN_HEIGHT = 896;
const int FPS = 60;
int prev_time = 0;
int current_time = 0;
float delta_time = 0;

const string WINDOW_TITLE = "Real game";

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quit_check(SDL_Window* window, SDL_Renderer* renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void loadmyimage_but_des(SDL_Texture* texture, SDL_Renderer* renderer, int xd, int yd, int width, int height);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) logSDLError(cout, "audio error", false);

    SDL_Texture* background = IMG_LoadTexture(renderer, "game resources/floor.png");
    SDL_Texture* texture1 = IMG_LoadTexture(renderer, "game resources/Grey_Brick.png");
    loadmyimage_but_des(background, renderer, 0, 0, 1344, 896);

    player player1(renderer, "game resources/Green-dude.png", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 3, 4);
    player1.draw(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event control;
    const Uint8 *keyState;
    keyState = SDL_GetKeyboardState(NULL);

    bool running = true;
    while(running)
    {
        prev_time = current_time;
        current_time = SDL_GetTicks();
        delta_time = (current_time - prev_time) / 250.0f;

        while(SDL_PollEvent(&control) != 0)
            if(keyState[SDL_SCANCODE_ESCAPE] || control.type == SDL_QUIT)
            {
                quitSDL(window, renderer);
                running = false;
            }

        SDL_RenderClear(renderer);
        loadmyimage_but_des(background, renderer, 0, 0, 1344, 896);

        player1.update(delta_time, keyState);
        player1.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quit_check(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Event control;
    const Uint8 *keyState;
    keyState = SDL_GetKeyboardState(NULL);

    while(true)
    {
        if(SDL_WaitEvent(&control) != 0 && (keyState[SDL_SCANCODE_ESCAPE] || control.type == SDL_QUIT))
        {
        	quitSDL(window, renderer);
            break;
        }
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Surface* iconimg = IMG_Load("game_resources/icon.png");
    SDL_SetWindowIcon(window, iconimg);
    SDL_FreeSurface(iconimg);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void loadmyimage_but_des(SDL_Texture* texture, SDL_Renderer* renderer, int xd, int yd, int width, int height)
{
    SDL_Rect rect;
    rect.x = xd;
    rect.y = yd;
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
