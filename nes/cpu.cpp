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

void CPU::execute() {}

uint8_t mem_read(uint16_t addr) {
    if(addr <= 0x1FFF) {
        // 2KB internal RAM, section mirrored 3 times
        return ram[addr & 0x07FF];
    }
}

uint16_t mem_read16(uint16_t addr) {}

uint16_t CPU::handleAddressingMode(addressing_mode_t mode) {
    switch(mode) {
        case Immediate:
            return PC++;
        case Implied:
            return 0;

    }
}