#include "nes.h"
#include <iostream>

bool NES::init_nes() {
    std::cout << "Initializing NES..." << std::endl;
    if (!cpu.initialize()) {
        std::cout << "Failed to init CPU" << std::endl;
        return false;
    }
    if (!ppu.initialize()) {
        std::cout << "Failed to init PPU" << std::endl;
        return false;
    }

    // display init
    config.width = 256;
	config.height = 240;
	config.scale = 4;
	config.outline = true;
    for (int i = 0; i < config.width * config.height; i++) {
		display[i] = 0;
	}
    state = RUNNING;
    return true;
}