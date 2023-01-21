#include "Square.h"

Square::Square(int px, int py, SDL_Renderer* renderer, SDL_Window* win) {
	x = px; y = py;
	rect.x = x; rect.y = y; rect.w = square_size; rect.h = square_size;

	SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_Surface* screenSurface = SDL_GetWindowSurface(win);

	SDL_FillRect(surface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(screenSurface);
	SDL_FreeSurface(surface);
}

Square::~Square() {
	SDL_DestroyTexture(texture);
}

void Square::draw(SDL_Renderer* renderer){
	if(on){
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
}

void Square::updateState(std::vector<Square*>v) {

	int squares = 0;

	for (auto square : v) {
		if (x - square_size <= square->x && square->x <= x + square_size && y - square_size
		<= square->y && square->y <= y + square_size && !(square->x == x && square->y == y) && square->on) {
			squares++;
		}
	}
	if (squares < 2) new_state = false;
	else if (squares >= 2 && squares <= 3 && on) new_state = true;
	else if (squares > 3) new_state = false;
	else if (squares == 3 && !on) new_state = true;

}
