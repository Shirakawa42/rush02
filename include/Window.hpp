#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <IMonitorDisplay.hpp>

# define POLICE 20


class	Window : virtual public IMonitorDisplay
{
	public:
		Window(void);
		Window(const Window &b);
		virtual ~Window(void);

		Window	&operator=(const Window &b);

		SDL_Renderer *getRenderer(void);
		SDL_Window *getWindow(void);
		SDL_Surface *getSurface(void);
		void	draw(const IMonitorModule &module);
		void	render(void);
		void	writeText(int x,int y, std::string text, SDL_Color color);
		SDL_Color 		white;
		SDL_Color 		lightgrey;
		SDL_Color 		grey;
	private:
		SDL_Window		*window;
		SDL_Surface		*surface;
		SDL_Renderer	*renderer;
		TTF_Font 		*font;
		void			init_colors(void);
};

extern Window *window;

#endif