#ifndef FT_GKRELLM_HPP
# define FT_GKRELLM_HPP

# include "Log.hpp"
# include "TerminalMonitor.hpp"
# include "Window.hpp"
# include "CpuModule.hpp"
# include "NetworkModule.hpp"
# include "HostModule.hpp"

# define FPS	60

void	manage_term_inputs(void);

extern TerminalMonitor		*term;
extern Window				*window;

extern std::vector<IMonitorModule*>	modules;

#endif
