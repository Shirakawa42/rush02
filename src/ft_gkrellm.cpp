#include "ft_gkrellm.hpp"
#include <iostream>
#include <signal.h>

TerminalMonitor	term;

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

void	windowed(void)
{
}

int	main(int argc, char **argv)
{
	signal(SIGINT, reinterpret_cast<void (*)(int)>(&clean_exit));
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
