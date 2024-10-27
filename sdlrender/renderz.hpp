#include <SDL.h>
#include "types.hpp"
void drawfilledcircle(SDL_Renderer* r, cgl::vec2 pos, int radius) {//yes i know its in a header file
	//i dont care about compilation time
	const int crad = radius;
	for (int j = 0; j <= crad; j++) {
		for (double i = 0; i < M_PI * radius * 2; i+=radius / 314.1) {

			SDL_RenderDrawPoint(r, cos(i) * radius + pos.x, sin(i) * radius + pos.y);
		}
		radius--;
	}
}
void drawcircle(SDL_Renderer* r, cgl::vec2 pos, int radius) {
	for (double i = 0; i < M_PI * radius * 2; i += radius / 314.1) {//so i optimised it :)

		SDL_RenderDrawPoint(r, cos(i) * radius + pos.x, sin(i) * radius + pos.y);
	}
}
void drawcircle(SDL_Renderer* r, cgl::vec2 pos, int radius, int width) {

	for (int j = 0; j <= width; j++) {
		for (double i = 0; i < M_PI * radius * 2; i += radius/ 314.1) {

			SDL_RenderDrawPoint(r, cos(i) * radius + pos.x, sin(i) * radius + pos.y);
		}
		radius--;
	}
}
