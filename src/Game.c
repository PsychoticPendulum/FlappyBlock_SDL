#include "Game.h"

void Clean(SDL_Window *window, SDL_Renderer *renderer, struct Game game) {
	printf("\n  -> Renderer ...\t");
	SDL_DestroyRenderer(renderer);
	printf("Done!\n  -> Window ...\t\t");
	SDL_DestroyWindow(window);
	printf("Done!\n  -> Fontcache ...\t");
	TTF_CloseFont(game.font);
	TTF_Quit();
	printf("Done!\n  -> SDL ...\t\t");
	SDL_Quit();
	printf("Done!\n");
}

bool Init() {
	struct Game game = {
		"title", true, false, 1920, 1080, NULL
	};

	// Initialize SDL
	printf("Initializing SDL ...\t");
	if (SDL_Init(SDL_INIT_VIDEO) || TTF_Init()) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	game.font = TTF_OpenFont("/usr/share/fonts/TTF/Roboto-Medium.ttf", 24);
	if (!game.font) {
		printf("Error initializing font: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	printf("Done!\n");

	// Create Window
	printf("Creating Window ...\t");
	Uint32 window_flags = 0;
	SDL_Window *window = SDL_CreateWindow(game.title, CENTERED, CENTERED, game.w, game.h, window_flags);
	if (!window) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	printf("Done!\n");

	// Create renderer
	printf("Creating Renderer ...\t");
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);
	if (!renderer) {
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	printf("Done!\n");

	Loop(window, renderer, game);	

	// Clean up and exit
	printf("Cleaning up:");
	Clean(window, renderer, game);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
	return Init();
}
