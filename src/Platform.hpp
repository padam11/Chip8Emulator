#pragma once
//use sdl to render the rom game.
#include <cstdint>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Platform
{
    public:
        Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
        ~Platform();
        void Update(void const* buffer, int pitch);
        bool ProcessInput(uint8_t* keys);
        void audio_callback(void* userdata, uint8_t* stream, int bytes);
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
    
};