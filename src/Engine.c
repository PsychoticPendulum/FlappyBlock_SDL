#include "Engine.h"

void Handle_Event(struct Game *game, struct Entity *entity) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		// Make game quitable
		case SDL_QUIT:
			game->running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				// Quit game
				case SDLK_q:
					game->running = false;
					break;
				// Pause game
				case SDLK_SPACE:
					game->paused = !game->paused;
					break;
				// Jump
				case SDLK_UP:
					entity->bird.dy = -24;
					break;
				// Enable Autoplay
				case SDLK_a:
					game->autoplay = !game->autoplay;
					break;
			}
			break;
	}
}

void Loop(SDL_Window *window, SDL_Renderer *renderer, struct Game game) {
	struct Colors colors = Init_Colors();

	// Create Bird
	struct Bird bird = {
		24, 24, 400, 0, 0, 0, 0, malloc(sizeof(char)*16), false, false, false
	};

	// Create Pipes
	struct Pipe pipes[2];
	for (int i = 0; i < 2; i++) {
		pipes[i].w = 48;
		pipes[i].h = game.h;
		pipes[i].x = game.w / 2 - pipes[i].w / 2;
		pipes[i].yt = -game.h / 2;
		pipes[i].yb = 0;
		pipes[i].gap = 250;
		pipes[i].r = 0x0;
		pipes[i].g = 0xff;
		pipes[i].b = 0x0;
		pipes[i].a = 0xff;
	}
	pipes[1].x = game.w;

	// Create Stars
	struct Star star[64];
	for (int i = 0; i < 64; i++) {
		star[i].x = rand()%game.w;
		star[i].y = rand()%game.h-48;
		star[i].size = Random_Int(2,12);
		star[i].r = Random_Int(0x80, 0xff);
		star[i].g = Random_Int(0x80, 0xff);
		star[i].b = Random_Int(0x80, 0xff);
		star[i].a = 0xff;
	}

	// Fill Entity Structure
	struct Entity *entity_ptr, entity;
	entity_ptr = &entity;
	entity_ptr->bird = bird;
	entity_ptr->pipe[0] = pipes[0];
	entity_ptr->pipe[1] = pipes[1];
	for (int i = 0; i < 64; i++)
		entity_ptr->star[i] = star[i];

	// Main Loop
	while (game.running) {
		Handle_Event(&game, entity_ptr);
		Update(&game, entity_ptr);
		Render(renderer, game, colors, entity_ptr);
	}
	
	// Save progress
	Save_Highscore(game.highscore);
}

double Get_Distance(int x1, int y1, int x2, int y2) {
	double xdst = x1-x2;
	double ydst = y1-y2;
	return sqrt(xdst*xdst+ydst*ydst);
}

int Random_Int(int min, int max) {
	return min + rand() % (max + 1 - min);
}
