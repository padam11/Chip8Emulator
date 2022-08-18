#pragma once

#include <cstdint>
#include <random>

const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int STACK_LEVELS = 16;
const unsigned int REGISTER_COUNT = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;

class Chip8
{
    public:
        Chip8(); //set PC to 0x200 and clear memory
        void LoadRom(const char* filename);
        void Cycle();

        uint8_t keypad[KEY_COUNT]{};
        uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT]{};


    private:
        uint8_t registers[REGISTER_COUNT]{}; //all the important components of CHIP8
        uint8_t memory[MEMORY_SIZE]{}; //memory of chip8!
        uint16_t index{};
        uint16_t pc{};
        uint16_t stack[STACK_LEVELS]{};
        uint8_t sp{};
        //uint8_t sp{}; fixed ERROR: duplicate member.
        uint8_t delayTimer{};
        uint8_t soundTimer{};
        //uint8_t keypad[16]{}; fixed ERROR: duplicate member.
        //uint32_t video[64 * 32]{}; fixed ERROR: duplicate member.
        uint16_t opcode{};

        void Table0();
        void Table8();
        void TableE();
        void TableF();

        void OP_NULL();

        void OP_00E0(); //clear the display
        void OP_00EE(); //return from subroutine
        void OP_1nnn(); //jump to address nnn
        void OP_2nnn(); //call subroutine at nnn
        void OP_3xkk(); //skip next instruction if Vx == kk
        void OP_4xkk(); //skip next instruction if Vx != kk
        void OP_5xy0(); //skip next instruction if Vx == Vy
        void OP_6xkk(); //set Vx = kk
        void OP_7xkk(); //set Vx = Vx + kk
        void OP_8xy0(); //set Vx = Vy
        void OP_8xy1(); //set Vx = Vx | Vy
        void OP_8xy2(); //set Vx = Vx & Vy
        void OP_8xy3(); //set Vx = Vx ^ Vy
        void OP_8xy4(); //set Vx = Vx + Vy, set VF = carry
        void OP_8xy5(); //set Vx = Vx - Vy, set VF = not borrow
        void OP_8xy6(); //set Vx = Vx >> 1, set VF = lsb
        void OP_8xy7(); //set Vx = Vy - Vx, set VF = not borrow
        void OP_8xyE(); //set Vx = Vx << 1, set VF = msb
        void OP_9xy0(); //skip next instruction if Vx != Vy
        void OP_Annn(); //set I = nnn
        void OP_Bnnn(); //jump to address nnn + V0
        void OP_Cxkk(); //set Vx = random byte & kk
        void OP_Dxyn(); //draw sprite at (Vx, Vy), n bytes long
        void OP_Ex9E(); //skip next instruction if key with value Vx is pressed
        void OP_ExA1(); //skip next instruction if key with value Vx is not pressed
        void OP_Fx07(); //set Vx = delay timer
        void OP_Fx0A(); //wait for key press, set Vx = key pressed
        void OP_Fx15(); //set delay timer = Vx
        void OP_Fx18(); //set sound timer = Vx
        void OP_Fx1E(); //set I = I + Vx
        void OP_Fx29(); //set I = location of sprite for digit Vx
        void OP_Fx33(); //set memory[I] = decimal representation of Vx
        void OP_Fx55(); //store registers V0 to Vx in memory starting at location I
        void OP_Fx65(); //read registers V0 to Vx from memory starting at location I

        //uint8_t memory[MEMORY_SIZE]{};
        //uint8_t registers[REGISTER_COUNT]{};
        //uint16_t index{};
        //uint16_t pc{};
        //uint8_t delayTimer{};
        //uint8_t soundTimer{};
        //uint16_t stack[STACK_LEVELS]{};
        //uint8_t sp{};
        //uint16_t opcode{};

        std::default_random_engine randGen; //one of the instructions asks for random. this can be achieved physically
        //with a dedicated RNG chip. but for now, we'll use this.
        std::uniform_int_distribution<uint8_t> randByte;

        typedef void (Chip8::*Chip8Func)();
        Chip8Func table[0xF + 1]{&Chip8::OP_NULL};
        Chip8Func table0[0xE + 1]{&Chip8::OP_NULL};
        Chip8Func table8[0xE + 1]{&Chip8::OP_NULL};
        Chip8Func tableE[0xE + 1]{&Chip8::OP_NULL};
        Chip8Func tableF[0x65 + 1]{&Chip8::OP_NULL};




};