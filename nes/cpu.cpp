#include "cpu.h"
#include "nes.h"
#include <iostream>

CPU::CPU() {}

bool CPU::initialize() {
    std::cout << "Initializing CPU..." << std::endl;
    for (int i = 0; i < sizeof(ram); i++) {
		ram[i] = 0;
	}

    std::cout << "CPU init done..." << std::endl;
    return true;
}

void CPU::emulate_instructions() {
    uint16_t opcode = ram[PC];
    decode_and_execute(opcode);
}

void CPU::decode_and_execute(uint8_t opcode) {
    switch (opcode) {
        // ADC ADC - Add with Carry
        // A,Z,C,N = A+M+C
        // This instruction adds the contents of a memory location to the accumulator together with the carry bit.
        // If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
        case 0x69:
            PC += 2;
            break;
        case 0x65:
            PC += 2;
            break;
        case 0x75:
            PC += 2;
            break;
        case 0x6D:
            PC += 3;
            break;
        case 0x7D:
            PC += 3;
            break;
        case 0x79:
            PC += 3;
            break;
        case 0x61:
            PC += 2;
            break;
        case 0x71:
            PC += 2;
            break;
        // AND - Logical AND
        // A,Z,N = A&M
        // A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
        // Processor Status after use:
        case 0x29:
            PC += 2;
            break;
        case 0x25:
            PC += 2;
            break;
        case 0x35:
            PC += 2;
            break;
        case 0x2D:
            PC += 3;
            break;
        case 0x3D:
            PC += 3;
            break;
        case 0x39:
            PC += 3;
            break;
        case 0x21:
            PC += 2;
            break;
        case 0x31:
            PC += 2;
            break;
        default:
            std::cout << "Unknown opcode" << std::endl;
            break;
    }
}