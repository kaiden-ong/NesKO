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
	int width;
	int height;
	int scale;
	bool outline;
} config_t;

typedef struct {
	nes_state_t state;
	uint8_t ram[0xFFFF];
	bool display[256*240];
	uint16_t PC; // Program Counter
	uint8_t stack_pointer; 
	uint8_t A; // Accumulator
	uint8_t X; // Index Register
	uint8_t Y; // Index Register
	const char *romName;
} nes_t;

bool init_config(config_t *config, int argc, char **argv) {
	config->width = 256;
	config->height = 240;
	config->scale = 4;
	config->outline = true;
	return true;
}

bool init_sdl(const config_t config, sdl_t* sdl) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	sdl->window = SDL_CreateWindow("NesKO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.scale * config.width, config.scale * config.height, SDL_WINDOW_ALLOW_HIGHDPI);
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

bool init_nes(nes_t *nes, const config_t config) {
	cout << "Initializing NES..." << endl;
	for (int i = 0; i < sizeof(nes->ram); i++) {
		nes->ram[i] = 0;
	}
	cout << "Initialized RAM." << endl;
	for (int i = 0; i < config.width * config.height; i++) {
		nes->display[i] = 0;
	}
	cout << "Initialized Display with size: " << config.width * config.height << endl;
	nes->state = RUNNING;
	cout << "set state" << endl;
	return true;
}

void update_screen(SDL_Renderer* renderer, const config_t config, const nes_t nes) {
	SDL_Rect rect = {0, 0, config.scale, config.scale};
	for (uint32_t i = 0; i < sizeof nes.display; i++) {
		rect.x = (i % config.width) * config.scale;
		rect.y = (i / config.width) * config.scale;
		if (nes.display[i]) {
		SDL_SetRenderDrawColor(renderer, 31, 171, 38, 1);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderDrawRect(renderer, &rect);
		} else {
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
		SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}

void handle_input(nes_t *nes) {
	SDL_Event windowEvent;
	while (SDL_PollEvent(&windowEvent)) {
		switch (windowEvent.type) {
		case SDL_QUIT:
			nes->state = QUIT; 
			break;
		default:
			break;
		}
	}
}

void final_cleanup(sdl_t sdl) {
	SDL_DestroyRenderer(sdl.renderer);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
}

int main(int argc, char **argv) {
	config_t config;
	if (!init_config(&config, argc, argv)) {
	exit(EXIT_FAILURE);
	}

	cout << "Set configs" << endl;

	sdl_t sdl;
	if (!init_sdl(config, &sdl)) {
		exit(EXIT_FAILURE);
	}

	cout << "Set up SDL" << endl;

	nes_t nes;
	if (!init_nes(&nes, config)) {
		cout << "Failed to initialize NES" << endl;
		final_cleanup(sdl);
		exit(EXIT_FAILURE);
	}

	cout << "Init NES" << endl;

	SDL_Event windowEvent;
	while (nes.state == RUNNING) {
		handle_input(&nes);
		update_screen(sdl.renderer, config, nes);
		SDL_Delay(8); // about 120 fps: 1000ms / 8ms delay
	}

	final_cleanup(sdl);
	exit(EXIT_SUCCESS);
}
