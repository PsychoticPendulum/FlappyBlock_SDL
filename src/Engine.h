#pragma once
#include "Game.h"

struct Bird {
	int w;
	int h;
	int x;
	int y;
	int dy;
	int score;
	int highscore;
	char *score_str;
	bool hit;
	bool queued;
	bool hitqueued;
};

struct Pipe {
	int w;
	int h;
	int x;
	int yt;
	int yb;
	int gap;
	int r;
	int g;
	int b;
	int a;
};

struct Star {
	int x;
	int y;
	int size;
	int r;
	int g;
	int b;
	int a;
};

struct Entity {
	struct Bird bird;
	struct Pipe pipe[2];
	struct Star star[64];
};

void Loop(SDL_Window *window, SDL_Renderer *renderer, struct Game game);
void Handle_Event(struct Game *game, struct Entity *entity);

// Mathematical Functions
double Get_Distance(int x1, int y1, int x2, int y2);
int Random_Int(int min, int max);
