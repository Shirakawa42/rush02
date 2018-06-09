#include "CPU.hpp"
#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"
#include "Log.hpp"
#include "Terminal.hpp"
#include "Window.hpp"
#include <iomanip>

int		main(void)
{
	CPU		cpu = CPU();

	std::cout << "Max Frequency: " << std::fixed << std::setprecision(2) <<
		static_cast<float>(cpu.getMaxFrequency()) / 1000000000.0f << " GHz"<< std::endl;
	std::cout << "Current Frequency: " << std::fixed << std::setprecision(2) <<
		static_cast<float>(cpu.getCurrentFrequency()) / 1000000000.0f << " GHz"<< std::endl;
	std::cout << "Number of cores: " << cpu.getNumberOfCores() << " Cores" << std::endl;
	std::cout << "Max memory: " << cpu.getMemorySize() / 1000000 << " Mb" << std::endl;
	return 0;
}
