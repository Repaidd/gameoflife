#include <vector>
#include "SDL.h"

#pragma once

class Square
{
private:

	SDL_Texture* texture;
	SDL_Rect rect;

public:

	static const int square_size = 20;
	int x, y;

	bool on = false;
	bool new_state = false;

	Square(int px, int py, SDL_Renderer* renderer, SDL_Window* win);

	~Square();

	void draw(SDL_Renderer* renderer);

	void updateState(std::vector<Square*>v);

};