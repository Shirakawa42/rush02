#ifndef TERMINAL_MONITOR_HPP
# define TERMINAL_MONITOR_HPP

# include "IMonitorDisplay.hpp"
# include "Terminal.hpp"

class	TerminalMonitor : public IMonitorDisplay
{
	public:
		TerminalMonitor(void);
		TerminalMonitor(const TerminalMonitor &b);
		~TerminalMonitor(void);

		IMonitorDisplay	&operator=(const IMonitorDisplay &b);

		void	draw(const IMonitorModule &module);
		void	render(void);
	private:
		Terminal	_term;
};

#endif
