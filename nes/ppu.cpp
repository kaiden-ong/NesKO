#include "ppu.h"
#include <iostream>

PPU::PPU() {}

bool PPU::initialize() {
    std::cout << "Initializing PPU..." << std::endl;
    for (int i = 0; i < sizeof(ram); i++) {
		ram[i] = 0;
	}

    chr_pointer = 0x0;
    vram_pointer = 0x2000;
    palette_pointer = 0x3F00;

    std::cout << "PPU init done..." << std::endl;
    return true;
}