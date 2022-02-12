#include "Update.h"

void Update(struct Game *game, struct Entity *entity) {
	if (game->paused)
		return;

	// Stars
	for (int i = 0; i < 64; i++) {
		entity->star[i].x -= entity->star[i].size / 2;
		if (entity->star[i].x + entity->star[i].size < 0) {
			entity->star[i].x = rand()%game->w;
			entity->star[i].x = rand()%game->h-48;
			entity->star[i].size = Random_Int(2,12);
			entity->star[i].x = game->w + entity->star[i].size;
		}
	}
	

	// Update Bird Gravity
	entity->bird.dy += entity->bird.dy < 24;
	entity->bird.y += entity->bird.dy;

	// Keep Bird on screen
	if (entity->bird.y < 0) {
		entity->bird.y = 0;
	} else if (entity->bird.y + entity->bird.h > game->h) {
		entity->bird.y = game->h - entity->bird.h;
		entity->bird.score = 0;
	}

	// Update Bird Score
	if (!entity->bird.hit && entity->bird.queued) {
		entity->bird.score++;
		entity->bird.queued = false;
	}
	if (entity->bird.score > entity->bird.highscore) {
		entity->bird.highscore = entity->bird.score;
		if (entity->bird.highscore > game->highscore) {
			game->highscore = entity->bird.highscore;
		}
	}
	sprintf(entity->bird.score_str , "Score: %d / %d / %d", entity->bird.score, entity->bird.highscore, game->highscore);


	// Update Pipes
	entity->bird.hit = false;
	for (int i = 0; i < 2; i++) {
		// Move Pipes
		entity->pipe[i].x -= 7;
		
		// Create hole
		entity->pipe[i].yb = entity->pipe[i].yt + entity->pipe[i].h + entity->pipe[i].gap;
		
		// Check collision
		if (entity->pipe[i].x < entity->bird.x + entity->bird.w &&
			entity->pipe[i].x + entity->pipe[i].w > entity->bird.x) {
			if (entity->pipe[i].yt + entity->pipe[i].h > entity->bird.y ||
				entity->pipe[i].yb < entity->bird.y + entity->bird.h) {
				// Reset score
				entity->bird.score = 0;
				entity->bird.hit = false;
				entity->bird.queued = false;
				// Set hit indication color
				entity->pipe[i].r = 0xff;
				entity->pipe[i].g = 0x00;
			} else {
				entity->bird.hit = true;
			}
		} else {
			// Reset pipe color
			entity->pipe[i].r = 0x00;
			entity->pipe[i].g = 0xff;
		}

		// Bring Pipes back around
		if (entity->pipe[i].x + entity->pipe[i].w < 0) {
			// Reset Y
			entity->pipe[i].yt = Random_Int((entity->pipe[i].h - entity->pipe[i].gap) * -1,
												game->h - 2*entity->pipe[i].h);
			// Reset X
			entity->pipe[i].x = game->w;
		}
	
		// Autoplay	
		if (game->autoplay) {
			if (entity->pipe[i].x < game->w / 3 &&
				entity->pipe[i].x + entity->pipe[i].w >
				entity->bird.x + entity->bird.w) {
				if (entity->bird.y + entity->bird. h / 2 >
					entity->pipe[i].yb - entity->pipe[i].gap / 2 + 7) {
					entity->bird.dy = -14;
				}
			} else if (entity->bird.y > game->h - game->h / 3) {
				entity->bird.dy = -14;
			}
		}
	}
	// Queue score
	if (entity->bird.hit)
		entity->bird.queued = true;
}
