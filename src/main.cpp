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
#include <vector>
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




double remap(double value, double low1, double high1, double low2, double high2)
{
	return (low2 + (value - low1) * (high2 - low2) / (high1 - low1));
}



void renderGraph(int x, int y, int w, int h)
{

	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;


	std::vector<int> cpuHistoryGraph;
	cpuHistoryGraph.reserve(100);
	while (cpuHistoryGraph.size() != cpuHistoryGraph.capacity())
			cpuHistoryGraph.push_back(rand()%101);
	
	int currentPercantage = cpuHistoryGraph[cpuHistoryGraph.size()-1];

	SDL_SetRenderDrawColor(s.renderer, 52, 62, 77, 255);
	SDL_RenderFillRect(s.renderer, &r);

	SDL_Rect	r2;
	int offset = remap(static_cast<double>(100-currentPercantage), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h) );
	r2.x = x;
	r2.y = y + offset;
	r2.w = w;
	r2.h = h  - offset;

	SDL_SetRenderDrawColor(s.renderer, 47, 85, 101, 255);
	int i0 = 50;
	while (i0 < w)
	{
		SDL_RenderDrawLine(s.renderer, x + i0, y, x + i0, y+h);
		i0 += 50;
	}

	SDL_SetRenderDrawColor(s.renderer, 57, 104, 123, 255);
	SDL_RenderFillRect(s.renderer, &r2);

	SDL_SetRenderDrawColor(s.renderer, 78, 142, 168, 255);
	int i = 0;
	SDL_Point list[ cpuHistoryGraph.size()];
	while (i < cpuHistoryGraph.size())
	{
		double realx = remap(static_cast<double>(i), static_cast<double>(0), static_cast<double>(99), static_cast<double>(0), static_cast<double>(w) );
		double realy = remap(static_cast<double>(100-cpuHistoryGraph[i]), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h) );
		list[i].x = x + realx;
		list[i].y = y + realy;
		i++;
	}
	SDL_RenderDrawLines(s.renderer, list, cpuHistoryGraph.size());


	SDL_RenderPresent(s.renderer);
}

void	renderRect(void)
{
	static int	pos = 0;
	SDL_Rect	r;

	r.x = 50;
	r.y = 50;
	r.w = 200;
	r.h = 200;
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
    SDL_SetRenderDrawColor(s.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	renderGraph(500,500,1000,200);
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
