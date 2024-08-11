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