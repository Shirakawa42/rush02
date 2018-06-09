#ifndef CPU_HPP

# define CPU_HPP

#include <iostream>
#include <string>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#include <sys/sysctl.h>

class	CPU
{
	public:
		CPU();
		~CPU();
		CPU( const CPU & );
		CPU &	operator = ( const CPU & );
		void		setCurrentFrequency(void);
		void		setMaxFrequency(void);
		void		setName(void);
		void		setCurrentUsage(void);
		void		setNumberOfCores(void);
		void		setMemorySize(void);
		size_t		getCurrentFrequency(void);
		size_t		getMaxFrequency(void);
		std::string	getName(void);
		float		getCurrentUsage(void);
		size_t		getNumberOfCores(void);
		size_t		getMemorySize(void);

	private:
		float				CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
		float				GetCPULoad(void);
		unsigned long long	_previousTotalTicks;
		unsigned long long	_previousIdleTicks;
		size_t				_current_frequency;
		size_t				_max_frequency;
		std::string			_name;
		float				_current_usage;
		size_t				_number_of_cores;
		size_t				_memory_size;
};

extern CPU	cpu;

#endif
