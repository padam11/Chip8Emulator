#include "Chip8.hpp"
#include "Platform.hpp"
#include </Users/rohanbuch/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h>
#include <chrono>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std:: cerr << "Usage: " << argv[0] << " <Scale> <Delay> <Rom>\n" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int videoScale = std::stoi(argv[1]);
    int cycleDelay = std::stoi(argv[2]);
    char const* romFilename = argv[3];

    Platform platform("CHIP8", videoScale * VIDEO_WIDTH, videoScale * VIDEO_HEIGHT, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8;
    chip8.LoadRom(romFilename);

    int videoPitch = sizeof(chip8.video[0] * VIDEO_WIDTH);

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = platform.ProcessInput(chip8.keypad);

        auto currentTime = std::chrono::high_resolution_clock::now();

        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;
            chip8.Cycle();
            platform.Update(chip8.video, videoPitch);
        }
    }
    return 0;
}