#include "CPU.hpp"
#include <sys/sysctl.h>

CPU cpu;

CPU::CPU()
{
	setName();
	setMaxFrequency();
	setNumberOfCores();
	setMemorySize();
	this->_freqHistory.reserve(100);
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
	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;
	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);
	_previousTotalTicks = totalTicks;
	_previousIdleTicks  = idleTicks;
	return ret;
}

float	CPU::GetCPULoad()
{
	host_cpu_load_info_data_t cpuinfo;
	mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
	{
		unsigned long long totalTicks = 0;
		for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
		return CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
	}
	else
		return -1.0f;
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
	char		cpu[128];
	size_t		i = 128;

	sysctlbyname("machdep.cpu.brand_string", &cpu, &i, NULL, 0);
	_name = cpu;
}

void		CPU::setCurrentUsage(void)
{
	_current_usage = GetCPULoad() * 100.0f;
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

void		CPU::setUsedMemory(void)
{
	vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {;
        long long usedMemory = (vm_stats.active_count +
                                 vm_stats.inactive_count +
                                 vm_stats.wire_count) *  page_size;
        _used_memory = usedMemory;
        return ;
    }
    _used_memory = 0;
}

size_t		CPU::getUsedMemory(void)
{
	setUsedMemory();
	return _used_memory;
}

size_t		CPU::getMemorySize(void)
{
	return _memory_size;
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
	if (this->_freqHistory.size() == 100)
		this->_freqHistory.erase(this->_freqHistory.begin());
	_freqHistory.push_back(this->_current_usage);
	return _current_usage;
}

size_t		CPU::getNumberOfCores(void)
{
	return _number_of_cores;
}

std::vector<int> const			&CPU::getHistory(void) const
{
	return (_freqHistory);
}


