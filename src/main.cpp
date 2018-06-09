#include "CPU.hpp"
#include "IMonitorDisplay.hpp"
#include "IMonitorModule.hpp"
#include "Log.hpp"
#include "Terminal.hpp"
#include "Window.hpp"

int		main(void)
{
	CPU		cpu;

	std::cout << cpu.getMaxFrequency() << std::endl;
	std::cout << cpu.getNumberOfCores() << std::endl;
	std::cout << cpu.getMemorySize() << std::endl;
	return 0;
}
