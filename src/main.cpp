#include "ft_gkrellm.hpp"
#include <iostream>
#include <signal.h>
#include "CPU.hpp"
#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"
#include "Log.hpp"
#include "Terminal.hpp"
#include "Window.hpp"
#include <iomanip>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>

# define POLICE 20

struct	t_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	TTF_Font 		*font;
	SDL_Color 		white;
	SDL_Color 		lightgrey;
	SDL_Color 		grey;
};

//TerminalMonitor	term;
CPU				cpu;
t_sdl			s;

void	print_usage(void)
{
	std::cerr << "./ft_gkrellm [-term | -win]" << std::endl;
	exit(EXIT_FAILURE);
}

void	clean_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	terminal(void)
{
	while (true)
	{
		manage_term_inputs();
	}
}

void	writeText(int x, int y, std::string text, SDL_Color color)
{
	int 	x_text = 0;
	int 	y_text = 0;

	SDL_Surface	*surfaceMessage = TTF_RenderText_Solid(s.font, text.c_str(), color);
	SDL_Texture	*message = SDL_CreateTextureFromSurface(s.renderer, surfaceMessage);
	SDL_QueryTexture(message, NULL, NULL, &x_text, &y_text);
	SDL_Rect 	textRect = {x, y, x_text, y_text};
	SDL_RenderCopy(s.renderer, message, NULL, &textRect);
}

void	renderRect(void)
{
	static int	pos = 0;
	SDL_Rect	r;

	r.x = 50;
	r.y = 50 + (pos * 25) + (pos * 297);
	r.h = 297;
	r.w = 1180;
	SDL_SetRenderDrawColor(s.renderer, 180, 180, 180, 255);
	SDL_RenderFillRect(s.renderer, &r);
	pos++;
}

void	windowed(void)
{
	if ((s.win = SDL_CreateWindow("ft_gkrellm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN)) == NULL)
		exit(0);
	s.renderer = SDL_CreateRenderer(s.win, -1, 0);
	SDL_SetRenderDrawColor(s.renderer, 211, 211, 211, 255);
	SDL_RenderClear(s.renderer);
	s.font = TTF_OpenFont("src/leadcoat.ttf", POLICE);
	renderRect();
	renderRect();
	writeText(50, 50, cpu.getName(), s.white);
	writeText(50, 75, "CPU USAGE", s.white);
	writeText(50, 100, "CPU MAX FREQUENCY", s.white);
	SDL_RenderPresent(s.renderer);
	SDL_Delay(5000);
	SDL_DestroyWindow(s.win);
	TTF_CloseFont(s.font);
	TTF_Quit();
	SDL_Quit();
}

void	init_colors(void)
{
	s.white.r = 255;
	s.white.g = 255;
	s.white.b = 255;
	s.lightgrey.r = 211;
	s.lightgrey.g = 211;
	s.lightgrey.b = 211;
	s.grey.r = 180;
	s.grey.g = 180;
	s.grey.b = 180;
}

int		main(int argc, char **argv)
{
//	TerminalMonitor	term;
	CPU				cpu;
	t_sdl			s;

	if (SDL_Init(SDL_INIT_VIDEO))
		return (EXIT_FAILURE);
	if (TTF_Init() == -1)
		return (EXIT_FAILURE);
	init_colors();
	windowed();
	//signal(SIGINT, reinterpret_cast<void (*)(int)>(&clean_exit));
	if (argc == 1)
		terminal();
	else if (argc == 2)
	{
		std::string	arg(argv[1]);

		if (arg == "-help" || arg == "-h" || arg == "--help")
			print_usage();
		if (arg == "-term")
			terminal();
		else if (arg == "-win")
			windowed();
		else
		{
			std::cerr << "invalid arg '" << arg << "', allowed: -term -win" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else
		print_usage();
	return (0);
}
