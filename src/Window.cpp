#include <Window.hpp>
#include <iostream>

#include <IMonitorDisplay.hpp>

#include "Log.hpp"

Window::Window(void)
{
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		init_colors();
		this->font = TTF_OpenFont("futura.ttf", POLICE);
		this->window = SDL_CreateWindow(
		"ft_gkrellm",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1920,
		1080,
		SDL_WINDOW_OPENGL
		);
		if (window == NULL) {
			std::cout << "Could not create window:" << SDL_GetError() << std::endl;
		}
		this->renderer = SDL_CreateRenderer(this->window, -1, 0);
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}

Window::Window(const Window &b)
{
	*this = b;
}

Window::~Window(void)
{
	SDL_DestroyWindow(this->window);
}

Window	&Window::operator=(const Window &rhs)
{
	this->window = rhs.window;
	this->renderer = rhs.renderer;
	return (*this);
}

void	Window::init_colors(void)
{
	white.r = 255;
	white.g = 255;
	white.b = 255;
	lightgrey.r = 211;
	lightgrey.g = 211;
	lightgrey.b = 211;
	grey.r = 180;
	grey.g = 180;
	grey.b = 180;
}

void Window::draw(IMonitorModule &module)
{
	module.drawWin(*this);
}


void Window::render(void)
{

}

SDL_Renderer *Window::getRenderer(void)
{
	return (this->renderer);
}
SDL_Window *Window::getWindow(void)
{
	return (this->window);
}

void	Window::writeText(int x, int y, std::string text, SDL_Color color)
{
	int 	x_text = 0;
	int 	y_text = 0;

	SDL_Surface	*surfaceMessage = TTF_RenderText_Solid(this->font, text.c_str(), color);
	SDL_Texture	*message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
	SDL_QueryTexture(message, NULL, NULL, &x_text, &y_text);
	SDL_Rect 	textRect = {x, y, x_text, y_text};
	SDL_RenderCopy(this->renderer, message, NULL, &textRect);
}