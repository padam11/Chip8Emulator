# Chip8Emulator
A Chip8 Emulator built in C++

# Background

Chip8 is an interpreted programming language, first used in do-it-yourself computers in the 1970's. CHIP-8 was created by RCA engineer Joe Weisbecker in 1977 for the COSMAC VIP microcomputer. It was intended as a simpler way to make small programs and games for the computer. Instead of using machine language for the VIP’s CDP1802 processor, you could type in simple hexadecimal instructions (with the VIP’s hex keypad) that resembled machine code, but which was actually interpreted on the fly by a small program.

# Specifications

CHIP-8 has the following components:

- Memory: CHIP-8 has direct access to up to 4 kilobytes of RAM
- Display: 64 x 32 pixels (or 128 x 64 for SUPER-CHIP) monochrome, ie. black or white
- A program counter, often called just “PC”, which points at the current instruction in memory
- One 16-bit index register called “I” which is used to point at locations in memory
- A stack for 16-bit addresses, which is used to call subroutines/functions and return from them
- An 8-bit delay timer which is decremented at a rate of 60 Hz (60 times per second) until it reaches 0
- An 8-bit sound timer which functions like the delay timer, but which also gives off a beeping sound as long as it’s not 0
- 16 8-bit (one byte) general-purpose variable registers numbered 0 through F hexadecimal, ie. 0 through 15 in decimal, called V0 through VF
-- VF is also used as a flag register; many instructions will set it to either 1 or 0 based on some rule, for example using it as a carry flag
- Audio will be implemented using SDL, in C++.

# Understanding the code

Emulation is built upon emulating opcodes. Not just opcodes, but also the keypad as well as the sound.

An emulator’s main task is simple. It runs in an infinite loop, and does these three tasks in succession:

- Fetch the instruction from memory at the current PC (program counter)
- Decode the instruction to find out what the emulator should do
- Execute the instruction and do what it tells you

Overall, this is the basic part of emulation, which can be covered in many different types of consoles (GBA, SENS, etc).

# Special Thanks To

- https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- https://austinmorlan.com/posts/chip8_emulator/
