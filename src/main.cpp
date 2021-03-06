#include "ft_gkrellm.hpp"
#include <iostream>
#include <signal.h>
#include <vector>
#include "CPU.hpp"
#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"
#include "Log.hpp"
#include "Terminal.hpp"
#include <Window.hpp>
#include <iomanip>
#include <unistd.h>

TerminalMonitor					*term = NULL;
Window							*window;

std::vector<IMonitorModule*>	modules;


void	print_usage(void)
{
	std::cerr << "./ft_gkrellm [-term | -win]" << std::endl;
	exit(EXIT_FAILURE);
}

void	signal_handler(void)
{
	exit(EXIT_SUCCESS);
}

void	clean_exit(void)
{
	if (term)
	{
		delete term;
		term = NULL;
	}
	if (window)
	{
		delete window;
		window = NULL;
	}
}

void	addModule(IMonitorModule *module)
{
	static int	n = 3;
	static int	i = 0;
	int			width = term->getTerm().getWidth();
	int			height = term->getTerm().getHeight();

	if (width < height * 2)
	{
		module->setY(i++ * height / n + 1);
		module->setX(1);
		module->setWidth(width - 2);
		module->setHeight(height / n - 2);
	}
	else
	{
		module->setX(i++ * width / n + 1);
		module->setY(1);
		module->setWidth(width / n - 2);
		module->setHeight(height - 2);
	}
	modules.push_back(module);
}

void	terminal(void)
{
	struct timeval	start, end, prev;
	size_t			us;

	term = new TerminalMonitor();
	addModule(new HostModule());
	addModule(new CpuModule());
	addModule(new NetworkModule());
	while (true)
	{
		gettimeofday(&start, NULL);
		manage_term_inputs();
		for (size_t i = 0; i < modules.size(); i++)
			term->draw(*modules[i]);
		term->render();
		gettimeofday(&end, NULL);
		us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		if (us < 1000000 / FPS)
		{
			try
			{
				_log << 1000000 / ((end.tv_sec - prev.tv_sec) + (end.tv_usec - prev.tv_usec)) << " fps" << std::endl;
			}
			catch (const std::exception &e)
			{
				_log << e.what() << std::endl;
			}
			prev = end;
			usleep(1000000 / FPS - us);
		}
	}
}

SDL_Event e;

void	windowed(void)
{
	SDL_Surface *image = SDL_LoadBMP("norminet.bmp");

	window = new Window();
	modules.push_back(new CpuModule(50,50,600,550));
	modules.push_back(new HostModule(50,615,600,150));
	modules.push_back(new NetworkModule(700,50,600,550));

	while (true)
	{
		SDL_RenderClear(window->getRenderer());
		SDL_Texture* texture1 = SDL_CreateTextureFromSurface(window->getRenderer(), image);
		SDL_RenderCopy(window->getRenderer(), texture1, NULL, NULL);



		for (size_t i = 0; i < modules.size(); i++)
			window->draw(*modules[i]);
		SDL_RenderPresent(window->getRenderer());
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_DestroyRenderer(window->getRenderer());
				SDL_DestroyWindow(window->getWindow());
				SDL_Quit();
				exit(0);
			}
		}
		SDL_DestroyTexture(texture1);
		SDL_Delay(1000);
	}
}

int		main(int argc, char **argv)
{
	atexit(&clean_exit);
	signal(SIGINT, reinterpret_cast<void (*)(int)>(&signal_handler));
	signal(SIGHUP, reinterpret_cast<void (*)(int)>(&signal_handler));
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
