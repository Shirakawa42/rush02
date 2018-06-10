#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <SDL2/SDL.h>

#include <IMonitorDisplay.hpp>


class	Window : virtual public IMonitorDisplay
{
	public:
		Window(void);
		Window(const Window &b);
		~Window(void);

		Window	&operator=(const Window &b);

		SDL_Renderer *getRenderer(void);
		SDL_Window *getWindow(void);
		SDL_Surface *getSurface(void);
		void	draw(const IMonitorModule &module);
		void	render(void);

	private:
		SDL_Window *window;
		SDL_Surface *surface;
		SDL_Renderer *renderer;
};

extern Window *window;

#endif