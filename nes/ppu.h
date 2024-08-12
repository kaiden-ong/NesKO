#include <cstdint>

class PPU {
    public:
        uint8_t ram[0xFFFF];
        uint16_t chr_pointer;
        uint16_t vram_pointer;
        uint16_t palette_pointer;

        PPU(); // create a cpu object
        bool initialize(); // handle cpu initialize functionality like setting registers
};