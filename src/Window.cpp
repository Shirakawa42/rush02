#include "Window.hpp"

Window::Window(void)
{
	_window = SDL_CreateWindow("ft_gkrellm",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, 0);
}

Window::Window(const Window &b)
{
	(void)b;
	_window = SDL_CreateWindow("ft_gkrellm",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, 0);
}

Window::~Window(void)
{
	SDL_DestroyWindow(_window);
}

Window	&Window::operator=(const Window &b)
{
	(void)b;
	return (*this);
}
