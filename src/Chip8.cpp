#include <fstream>
#include "Chip8.hpp"
#include <cstdint>
#include <random>
#include <chrono>
#include <cstring>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int START_ADDRESS = 0x200;
uint8_t fontset[FONTSET_SIZE] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count())
    {
        pc = START_ADDRESS;
        //for (int i = 0; i < MEMORY_SIZE; i++)
        //{
            //memory[i] = 0;
        //}

        for (unsigned int i = 0; i < FONTSET_START_ADDRESS; i++)
        {
            memory[FONTSET_START_ADDRESS + i] = fontset[i];
        }

        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
        // function pointer table below
        table[0x0] = &Chip8::Table0;
        table[0x1] = &Chip8::OP_1nnn;
        table[0x2] = &Chip8::OP_2nnn;
        table[0x3] = &Chip8::OP_3xkk;
        table[0x4] = &Chip8::OP_4xkk;
        table[0x5] = &Chip8::OP_5xy0;
        table[0x6] = &Chip8::OP_6xkk;
        table[0x7] = &Chip8::OP_7xkk;
        table[0x8] = &Chip8::Table8;
        table[0x9] = &Chip8::OP_9xy0;
        table[0xA] = &Chip8::OP_Annn;
        table[0xB] = &Chip8::OP_Bnnn;
        table[0xC] = &Chip8::OP_Cxkk;
        table[0xD] = &Chip8::OP_Dxyn;
        table[0xE] = &Chip8::TableE;
        table[0xF] = &Chip8::TableF;

        table0[0x0] = &Chip8::OP_00E0;
        table0[0xE] = &Chip8::OP_00EE;

        table8[0x0] = &Chip8::OP_8xy0;
        table8[0x1] = &Chip8::OP_8xy1;
        table8[0x2] = &Chip8::OP_8xy2;
        table8[0x3] = &Chip8::OP_8xy3;
        table8[0x4] = &Chip8::OP_8xy4;
        table8[0x5] = &Chip8::OP_8xy5;
        table8[0x6] = &Chip8::OP_8xy6;
        table8[0x7] = &Chip8::OP_8xy7;
        table8[0xE] = &Chip8::OP_8xyE;

        tableE[0x1] = &Chip8::OP_ExA1;
        tableE[0xE] = &Chip8::OP_Ex9E;

        tableF[0x07] = &Chip8::OP_Fx07;
        tableF[0x0A] = &Chip8::OP_Fx0A;
        tableF[0x15] = &Chip8::OP_Fx15;
        tableF[0x18] = &Chip8::OP_Fx18;
        tableF[0x1E] = &Chip8::OP_Fx1E;
        tableF[0x29] = &Chip8::OP_Fx29;
        tableF[0x33] = &Chip8::OP_Fx33;
        tableF[0x55] = &Chip8::OP_Fx55;
        tableF[0x65] = &Chip8::OP_Fx65;
    }

    void Chip8::LoadROM(char const* filename)
    {
        std::ifstream file(filename, std::ios::binary);

        if (file.is_open())
        {
            std::streampos size = file.tellg(); //get size of file and allocate a buffer
            char* buffer = new char[size];

            file.seekg(0); //go to beginning of file
            file.read(buffer, size); //read file into buffer
            file.close(); //close file

            for (long i = 0; i < size; i++)
            {
                memory[START_ADDRESS + i] = buffer[i];
            }

            delete[] buffer;
        }
    }

    void Chip8::Cycle()
    {
        opcode = (memory[pc] << 8u) | memory[pc + 1]; //fetch

        pc += 2; //increment before execution

        ((*this).*(table[(opcode & 0xF000) >> 12u]))(); //decode and execute

        if (delayTimer > 0) //if set, decrement
        {
            --delayTimer;
        }

        if (soundTimer > 0) //if set, decrement
        {
            --soundTimer;
        }
    }

    void Chip8::Table0()
    {
        ((.this).*(table0[opcode & 0x000Fu]))();
    }

    void Chip8::Table8()
    {
        ((.this).*(table8[opcode & 0x000Fu]))();
    }

    void Chip8::TableE()
    {
        ((.this).*(tableE[opcode & 0x000Fu]))();
    }

    void Chip8::TableF()
    {
        ((.this).*(tableF[opcode & 0x000FFu]))();
    }

    void Chip8::OP_NULL()
    {
        //do nothing
    }

    void Chip8::OP_00E0()
    {
        memset(video, 0, sizeof(video)); //clear screen
    }

    void Chip8::OP_00EE()
    {
        --sp; //decrement stack pointer
        pc = stack[sp]; //set program counter to top of stack
    }

    void Chip8::OP_1nnn()
    {
        uint16_t address = opcode & 0x0FFFu;
        pc = address;
    }

    void Chip8::OP_2nnn()
    {
        uint16_t address = opcode & 0x0FFFu;
        
        pc = address;
    }

    void Chip8::OP_2nnn()
    {
        uint16_t address = opcode & 0x0FFFu;
    }

    void Chip8::OP_3xkk()
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t kk = opcode & 0x00FFu;

        if (registers[Vx] == byte)
        {
            pc += 2;
        }
    }
       