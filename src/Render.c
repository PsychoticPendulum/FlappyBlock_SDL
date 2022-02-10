#include "Render.h"

struct Color starcol;

void Render(SDL_Renderer *renderer, struct Game game, struct Colors colors, struct Entity **entity) {
	// Flush buffer
	SDL_RenderClear(renderer);

	// Draw Stars
	for (int i = 0; i < 64; i++) {
		starcol.r = (*entity)->star[i].r;
		starcol.g = (*entity)->star[i].g;
		starcol.b = (*entity)->star[i].b;
		Draw_Box(renderer,
				(*entity)->star[i].x,
				(*entity)->star[i].y,
				(*entity)->star[i].size,
				(*entity)->star[i].size,
				starcol,
				false);
	}

	// Draw Pipes
	for (int i = 0; i < 2; i++) {
		struct Color pipecol = {
			(*entity)->pipe[i].r,
			(*entity)->pipe[i].g,
			(*entity)->pipe[i].b,
			0xff
		};

		Draw_Box(renderer,
				(*entity)->pipe[i].x,
				(*entity)->pipe[i].yt,
				(*entity)->pipe[i].w,
				(*entity)->pipe[i].h,
				pipecol, true);
		Draw_Box(renderer,
				(*entity)->pipe[i].x,
				(*entity)->pipe[i].yb,
				(*entity)->pipe[i].w,
				(*entity)->pipe[i].h,
				pipecol, true);
	}

	// Draw Floor
	Draw_Box(renderer, 0, game.h - 48, game.w, 48, colors.DARK_GREEN, true);

	// Draw Bird
	Draw_Box(renderer,
			(*entity)->bird.x,
			(*entity)->bird.y,
			(*entity)->bird.w,
			(*entity)->bird.h,
			colors.YELLOW, true); 

	// Draw paused
	if (game.paused) {
		Draw_Box(renderer, game.w / 2 - 20, game.h / 2 - 25, 15, 50, colors.WHITE, true); 
		Draw_Box(renderer, game.w / 2 + 5, game.h / 2 - 25, 15, 50, colors.WHITE, true); 
	}

	// Draw Score
	Draw_Text(renderer, 50, 50, game.font, (*entity)->bird.score_str);

	// Draw background
	SDL_SetRenderDrawColor(renderer, 0xf, 0xf, 0xf, 0xff);
	SDL_RenderPresent(renderer);
}
