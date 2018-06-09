#include "CPU.hpp"
#include <sys/sysctl.h>

CPU::CPU()
{
	setName();
	setMaxFrequency();
	setNumberOfCores();
	setMemorySize();
}

CPU::~CPU()
{
	
}

CPU::CPU( const CPU & cpy )
{
	*this = cpy;
}

CPU &	CPU::operator = ( const CPU & cpy )
{
	(void)cpy;
	return *this;
}

void		CPU::setCurrentFrequency(void)
{
	size_t	cpu;
	size_t	i;

	_current_frequency = sysctlbyname("hw.cpufrequency", &cpu, &i, NULL, 0);
}

void		CPU::setMaxFrequency(void)
{
	size_t	cpu;
	size_t	i;

	_max_frequency = sysctlbyname("hw.cpufrequency_max", &cpu, &i, NULL, 0);
}

void		CPU::setName(void)
{

}

void		CPU::setCurrentUsage(void)
{

}

void		CPU::setNumberOfCores(void)
{
	size_t	cpu;
	size_t	i;

	_number_of_cores = sysctlbyname("hw.ncpu", &cpu, &i, NULL, 0);
}

void		CPU::setMemorySize(void)
{
	size_t	cpu;
	size_t	i;

	_memory_size = sysctlbyname("hw.memsize", &cpu, &i, NULL, 0);
}

size_t		CPU::getMemorySize(void)
{
	return _memory_size;
}

size_t		CPU::getCurrentFrequency(void)
{
	setCurrentFrequency();
	return _current_frequency;
}

size_t		CPU::getMaxFrequency(void)
{
	return _max_frequency;
}

std::string	CPU::getName(void)
{
	return _name;
}

size_t		CPU::getCurrentUsage(void)
{
	setCurrentUsage();
	return _current_usage;
}

size_t		CPU::getNumberOfCores(void)
{
	return _number_of_cores;
}
