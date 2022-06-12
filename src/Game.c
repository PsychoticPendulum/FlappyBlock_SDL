#include "Game.h"

int Load_Highscore() {
	// Create .data directory (will return 1 if already exists)
	mkdir(".data", S_IRWXU);

	// Open file
	char c;
	char *score = calloc(ceil(log10(INT_MAX)), sizeof(char));
	FILE *fptr = fopen(".data/scores.dat", "rb");
	if (fptr == NULL) {
		printf("Failed ...\n");	
		return 0;
	}

	// Read file
	int index = 0;
	while ((c = fgetc(fptr)) != EOF) {
		score[index++] = c;
	}
	
	// Convert to int and free memory
	int result = atoi(score);
	fclose(fptr);
	free(score);

	printf("Done!\n");
	return result;
}

void Save_Highscore(int score) {
	// Open file
	printf("Saving data ...\t\t");
	FILE *fptr = fopen(".data/scores.dat", "w");
	
	// Might fail is insufficient permissions to write file
	if (fptr == NULL) {
		printf("Failed ...\n");
		return;
	}

	// Write and close
	fprintf(fptr, "%d", score);
	fclose(fptr);
	printf("Done!\n");
}

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
		"FlappyBlock", true, false, false, 1920, 1080, 0, NULL
	};

	// Read scores.dat from disk
	printf("Reading data ...\t");
	game.highscore = Load_Highscore();

	// Initialize SDL
	printf("Initializing SDL ...\t");
	if (SDL_Init(SDL_INIT_VIDEO) || TTF_Init()) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	// Get SDL Version
	SDL_version compiled;
	SDL_version linked;
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	SDL_Log("SDL Version:\t%u.%u.%u\n",compiled.major, compiled.minor, compiled.patch);
	SDL_Log("SDL Linked:\t%u.%u.%u\n",linked.major, linked.minor, linked.patch);

	// Initialize SDL_TTF
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

int main(void) {
	return Init();
}
