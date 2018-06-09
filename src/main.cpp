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

int		main(int argc, char **argv)
{
	CPU		cpu = CPU();

	std::cout << "Max Frequency: " << std::fixed << std::setprecision(2) <<
		static_cast<float>(cpu.getMaxFrequency()) / 1000000000.0f << " GHz"<< std::endl;
	std::cout << "Current Frequency: " << std::fixed << std::setprecision(2) <<
		static_cast<float>(cpu.getCurrentFrequency()) / 1000000000.0f << " GHz"<< std::endl;
	std::cout << "Number of cores: " << cpu.getNumberOfCores() << " Cores" << std::endl;
	std::cout << "Max memory: " << cpu.getMemorySize() / 1000000 << " Mb" << std::endl;

	TerminalMonitor	term;

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
