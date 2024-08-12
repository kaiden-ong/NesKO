#include "cpu.h"
#include "ppu.h"

typedef enum {
	RUNNING,
	PAUSED,
	QUIT
} nes_state_t;

typedef struct {
	int width;
	int height;
	int scale;
	bool outline;
} config_t;

class NES {
    public:
        nes_state_t state;
        config_t config;
        bool display[256*240];
        CPU cpu;
        PPU ppu;
        NES() : cpu(), ppu() {}
        bool init_nes();
};