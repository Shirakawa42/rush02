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

struct	t_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
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

void	renderRect(void)
{
	static int	pos = 0;
	SDL_Rect	r;

	r.x = 50;
	r.y = 50;
	r.w = 50;
	r.h = 50;
	SDL_RenderClear(s.renderer);
	SDL_SetRenderDrawColor(s.renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(s.renderer, &r);
	SDL_RenderPresent(s.renderer);
}

void	windowed(void)
{
	if ((s.win = SDL_CreateWindow("ft_gkrellm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN)) == NULL)
		exit(0);
	s.renderer = SDL_CreateRenderer(s.win, -1, 0);
	SDL_SetRenderDrawColor(s.renderer, 211, 211, 211, 255);
	SDL_RenderClear(s.renderer);
	SDL_RenderPresent(s.renderer);
	renderRect();
	SDL_Delay(5000);
	SDL_DestroyWindow(s.win);
	SDL_Quit();
}

int		main(int argc, char **argv)
{
//	TerminalMonitor	term;
	CPU				cpu;
	t_sdl			s;

	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
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
