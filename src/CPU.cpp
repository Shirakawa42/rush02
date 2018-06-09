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

float	CPU::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
/*	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;
	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);
	_previousTotalTicks = totalTicks;
	_previousIdleTicks  = idleTicks;
	return ret;*/
	return 0.0f;
}

float	CPU::GetCPULoad()
{
/*	host_cpu_load_info_data_t cpuinfo;
	mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
	{
		unsigned long long totalTicks = 0;
		for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
		return CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
	}
	else*/
		return -1.0f;
}

void		CPU::setCurrentFrequency(void)
{

}

void		CPU::setMaxFrequency(void)
{
//	size_t	cpu;
//	size_t	i = 8;

//	sysctlbyname("hw.cpufrequency_max", &cpu, &i, NULL, 0);
//	_max_frequency = cpu;
}

void		CPU::setName(void)
{
//	char		cpu[128];
//	size_t		i = 128;

//	sysctlbyname("machdep.cpu.brand_string", &cpu, &i, NULL, 0);
//	_name = cpu;
}

void		CPU::setCurrentUsage(void)
{
//	_current_usage = GetCPULoad() * 100.0f;
}

void		CPU::setNumberOfCores(void)
{
//	size_t	cpu;
//	size_t	i = 8;

//	sysctlbyname("hw.ncpu", &cpu, &i, NULL, 0);
//	_number_of_cores = cpu;
}

void		CPU::setMemorySize(void)
{
//	size_t	cpu;
//	size_t	i = 8;

//	sysctlbyname("hw.memsize", &cpu, &i, NULL, 0);
//	_memory_size = cpu;
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

float		CPU::getCurrentUsage(void)
{
	setCurrentUsage();
	return _current_usage;
}

size_t		CPU::getNumberOfCores(void)
{
	return _number_of_cores;
}
