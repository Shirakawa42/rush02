#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SDL2/SDL.h>

class	Window
{
	public:
		Window(void);
		Window(const Window &b);
		~Window(void);

		Window	&operator=(const Window &b);
	private:
		SDL_Window	*_window;
};

#endif
