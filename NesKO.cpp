#include <iostream>
#include <filesystem>
#include <string>
#include <SDL2/SDL.h>
#include "src/nes.h"
using namespace std;

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} sdl_t;

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


void update_screen(SDL_Renderer* renderer, const config_t config, NES nes) {
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

void handle_input(NES *nes) {
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
	NES nes;

	if (!nes.init_nes()) {
		cout << "Failed to initialize NES" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "Init NES" << endl;

	sdl_t sdl;
	if (!init_sdl(nes.config, &sdl)) {
		exit(EXIT_FAILURE);
	}

	cout << "Set up SDL" << endl;


	SDL_Event windowEvent;
	while (nes.state == RUNNING) {
		handle_input(&nes);
		update_screen(sdl.renderer, nes.config, nes);
		SDL_Delay(8); // about 120 fps: 1000ms / 8ms delay
	}

	final_cleanup(sdl);
	exit(EXIT_SUCCESS);
}
