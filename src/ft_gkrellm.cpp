#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#include "ft_gkrellm.hpp"
#include <sys/sysctl.h>
#include <iostream>

int	main(void)
{
	host_cpu_load_info_data_t	cpuinfo;
	mach_msg_type_number_t		count = HOST_CPU_LOAD_INFO_COUNT;
	// Terminal					term;

	host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count);
	std::cout << cpuinfo.cpu_ticks[CPU_STATE_IDLE] << std::endl;
	return (0);
}
