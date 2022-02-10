#include "Draw.h"

void Draw_Box(SDL_Renderer *renderer, int x, int y, int w, int h, struct Color c, bool o) {
	int s = 2;
	SDL_Rect rect;
	if (o) {
		rect.x = x - s;
		rect.y = y - s;
		rect.w = w + 2*s;
		rect.h = h + 2*s;
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderDrawRect(renderer, &rect);
	}
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}

void Draw_Texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect rect = {
		x, y, w, h
	};

	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void Draw_Text(SDL_Renderer *renderer, int x, int y, TTF_Font *font, const char *str, ...) {
	SDL_Color color = {
		0xff,0xff,0xff,0xff
	};
	SDL_Surface *surface = TTF_RenderText_Blended(font, str, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	Draw_Texture(renderer, texture, x, y, 0, 0); 

	SDL_FreeSurface(surface);
}

