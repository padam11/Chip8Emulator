#include "Platform.hpp"
#include </Users/rohanbuch/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h>
//#include <SDL2_audio.h>

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
    SDL_Init(SDL_INIT_VIDEO); //INIT or Init?

    //window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    

    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    

    //texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
    
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
    
}

Platform::~Platform()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Platform::Update(void const* buffer, int pitch)
{
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Platform::ProcessInput(uint8_t* keys)
{
    bool quit = false;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                quit = true;
            } break;

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        quit = true;
                    } break;

                    case SDLK_x:
                    {
                        keys[0] = 1;
                    } break;

                    case SDLK_1:
                    {
                        keys[1] = 1;
                    } break;

                    case SDLK_2:
                    {
                        keys[2] = 1;
                    } break;

                    case SDLK_3:
                    {
                        keys[3] = 1;
                    } break;

                    case SDLK_q:
                    {
                        keys[4] = 1;
                    } break;

                    case SDLK_w:
                    {
                        keys[5] = 1;
                    } break;

                    case SDLK_e:
                    {
                        keys[6] = 1;
                    } break;

                    case SDLK_a:
                    {
                        keys[7] = 1;
                    } break;

                    case SDLK_s:
                    {
                        keys[8] = 1;
                    } break;

                    case SDLK_d:
                    {
                        keys[9] = 1;
                    } break;

                    case SDLK_z:
                    {
                        keys[0xA] = 1;
                    } break;

                    case SDLK_c:
                    {
                        keys[0xB] = 1;
                    } break;

                    case SDLK_4:
                    {
                        keys[0xC] = 1;
                    } break;

                    case SDLK_r:
                    {
                        keys[0xD] = 1;
                    } break;

                    case SDLK_f:
                    {
                        keys[0xE] = 1;
                    } break;

                    case SDLK_v:
                    {
                        keys[0xF] = 1;
                    } break;
                
                }
            } break;

            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_x:
                    {
                        keys[0] = 0;
                    } break;

                    case SDLK_1:
                    {
                        keys[1] = 0;
                    } break;

                    case SDLK_2:
                    {
                        keys[2] = 0;
                    } break;

                    case SDLK_3:
                    {
                        keys[3] = 0;
                    } break;

                    case SDLK_q:
                    {
                        keys[4] = 0;
                    } break;

                    case SDLK_w:
                    {
                        keys[5] = 0;
                    } break;

                    case SDLK_e:
                    {
                        keys[6] = 0;
                    } break;

                    case SDLK_a:
                    {
                        keys[7] = 0;
                    } break;

                    case SDLK_s:
                    {
                        keys[8] = 0;
                    } break;

                    case SDLK_d:
                    {
                        keys[9] = 0;
                    } break;

                    case SDLK_z:
                    {
                        keys[0xA] = 0;
                    } break;

                    case SDLK_c:
                    {
                        keys[0xB] = 0;
                    } break;

                    case SDLK_4:
                    {
                        keys[0xC] = 0;
                    } break;

                    case SDLK_r:
                    {
                        keys[0xD] = 0;
                    } break;

                    case SDLK_f:
                    {
                        keys[0xE] = 0;
                    } break;

                    case SDLK_v:
                    {
                        keys[0xF] = 0;
                    } break;
                }
            } break;
        }
    }

    return quit;
}

//void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes)
//{
    //Sint16 *buffer = (Sint16*)raw_buffer;
    //int length = bytes / 2; // 2 bytes per sample for AUDIO_S16SYS
    //int &sample_nr(*(int*)user_data);

    //for(int i = 0; i < length; i++, sample_nr++)
    //{
        //double time = (double)sample_nr / (double)SAMPLE_RATE;
        //buffer[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * 441.0f * time)); // render 441 HZ sine wave
    //}
//}