#include <iostream>
#include <vector>

#include "SDL.h"
#include "Square.h"

#define WIDTH 1000
#define HEIGHT 600

#define FPS 60

std::vector<Square*>v;

static bool game = false;

SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

class Game {
public:

	static void updateDisplay(SDL_Renderer* renderer) {

		SDL_RenderClear(renderer);

		for (auto* square : v) {
			square->draw(renderer);
		}

		SDL_RenderPresent(renderer);

	}

	static void click() {
		
		int mx, my;
		SDL_GetMouseState(&mx, &my);

		for (auto square : v) {
			if (square->x < mx && mx < square->x + Square::square_size && square->y < my && my < square->y + Square::square_size) {
				square->on = !square->on;
			}
		}

	}

	static void updateSquares() {
		for (auto square : v) square->updateState(v);
		for (auto square : v) square->on = square->new_state;
	}
	
	static void reset() {if (!game) for (auto square : v) { square->on = false; square->new_state = false; }}

};

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	win = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, 0);

	SDL_Event event;

	bool interrupted = false;

	for (int i = 0; i < WIDTH; i += Square::square_size) {
		for (int j = 0; j < HEIGHT; j += Square::square_size) {
			v.push_back(new Square(i, j, renderer, win));
		}
	}

	while (!interrupted) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				interrupted = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT && !game) {
					Game::click();
				}
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) game = !game;
				if (event.key.keysym.sym == SDLK_r) Game::reset();
			}
		}

		if (game) Game::updateSquares();

		Game::updateDisplay(renderer);

		SDL_Delay(FPS);

	}

	SDL_Quit();

	return 0;
}