#pragma once
#include "Game.h"

void Render(SDL_Renderer *renderer, struct Game game, struct Colors colors, struct Entity **entity);
void Vignette(SDL_Renderer *renderer, int x, int y);
