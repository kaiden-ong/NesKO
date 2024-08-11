#pragma once
#include <cstdint>

class CPU {
    public:
        uint16_t PC; // Program Counter
        uint8_t stack_pointer; 
        uint8_t A; // Accumulator
        uint8_t X; // Index Register
        uint8_t Y; // Index Register

        // variable to hold processor status (must be specified values)
        uint8_t PS;

        uint8_t ram[0xFFFF];

        CPU(); // create a cpu object
        bool initialize(); // handle cpu initialize functionality like setting registers
};