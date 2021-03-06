#ifndef I_MONITOR_DISPLAY_HPP
# define I_MONITOR_DISPLAY_HPP

# include "IMonitorModule.hpp"

class	IMonitorDisplay
{
	public:
		IMonitorDisplay(void);
		IMonitorDisplay(const IMonitorDisplay &b);
		~IMonitorDisplay(void);

		virtual	IMonitorDisplay	&operator=(const IMonitorDisplay &b);

		virtual	void	draw(IMonitorModule &module);
		virtual	void	render(void);
	private:
};

#endif
