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
	size_t	i = 8;

	sysctlbyname("hw.cpufrequency", &cpu, &i, NULL, 0);
	_current_frequency = cpu;
}

void		CPU::setMaxFrequency(void)
{
	size_t	cpu;
	size_t	i = 8;

	sysctlbyname("hw.cpufrequency_max", &cpu, &i, NULL, 0);
	_max_frequency = cpu;
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
	size_t	i = 8;

	sysctlbyname("hw.ncpu", &cpu, &i, NULL, 0);
	_number_of_cores = cpu;
}

void		CPU::setMemorySize(void)
{
	size_t	cpu;
	size_t	i = 8;

	sysctlbyname("hw.memsize", &cpu, &i, NULL, 0);
	_memory_size = cpu;
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
