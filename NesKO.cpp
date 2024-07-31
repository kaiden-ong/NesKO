#include <iostream>
#include <filesystem>
#include <string>
#include <SDL2/SDL.h>
using namespace std;

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_t;

typedef enum {
	RUNNING,
	PAUSED,
	QUIT
} nes_state_t;

typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t scale;
	bool outline;
} config_t;

typedef struct {
	nes_state_t state;
	uint16_t ram[0xFFFF];
	uint16_t PC; // Program Counter
	uint8_t stack_pointer; 
	uint8_t A; // Accumulator
	uint8_t X; // Index Register
	uint8_t Y; // Index Register
	const char *romName;
} nes_t;

bool init_config(config_t *config, int argc, char **argv) {
	config->width = 64;
	config->height = 32;
	config->scale = 20;
	config->outline = true;
	return true;
}

bool init_sdl(config_t *config, sdl_t* sdl) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	sdl->window = SDL_CreateWindow("NesKO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config->scale * config->width, config->scale * config->height, SDL_WINDOW_ALLOW_HIGHDPI);
	if (sdl->window == NULL) {
		cout << "SDL Window Init Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl->renderer == NULL) {
		cout << "SDL Renderer Init Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		return 1;
	}
	return true;
}

bool init_nes(nes_t *nes, const config_t config, const char rom_name[]) {
	const uint32_t entry = 0x200;
	for (uint16_t i = 0; i < sizeof(nes->ram); i++) {
		nes->ram[i] = 0;
	}
	nes->state = RUNNING;
	return true;
}

int main(int argc, char **argv) {
	config_t config;
	if (!init_config(&config, argc, argv)) {
	exit(EXIT_FAILURE);
	}

	sdl_t sdl;
	if (!init_sdl(&config, &sdl)) {
		exit(EXIT_FAILURE);
	}
	// nes_t nes;
	// const char *rom_name = argv[1];
	// if (!init_nes(&nes, config, rom_name)) {
	// 	exit(EXIT_FAILURE);
	// }
	exit(EXIT_SUCCESS);
}
