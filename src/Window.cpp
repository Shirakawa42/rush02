#include <Window.hpp>
#include <iostream>

#include <IMonitorDisplay.hpp>



Window::Window(void)
{
SDL_Init(SDL_INIT_EVERYTHING);
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
		this->surface = SDL_GetWindowSurface(this->window);
		this->renderer = SDL_CreateSoftwareRenderer(this->surface);
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
	this->surface = rhs.surface;
	this->renderer = rhs.renderer;
	return (*this);
}

