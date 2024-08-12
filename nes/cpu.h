#pragma once
#include <cstdint>

typedef enum {
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    Indirect,
    IndirectX,
    IndirectY,
    Accumlator,
    Relative,
    Implied,
    Immediate,
    None
} addressing_mode_t;

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
        void execute(); // executes an instruction

        uint8_t mem_read(uint16_t addr);
        uint16_t mem_read16(uint16_t addr);

        // interrupts
        // void NMI_req();
        // void IRQ_req();

        // addressing
        uint16_t handleAddressingMode(addressing_mode_t mode);


};