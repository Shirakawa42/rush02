#ifndef I_MONITOR_DISPLAY_HPP
# define I_MONITOR_DISPLAY_HPP

# include "IMonitorModule.hpp"

class	IMonitorDisplay
{
	public:
		IMonitorDisplay(void);
		IMonitorDisplay(const IMonitorDisplay &b);
		virtual	~IMonitorDisplay(void);

		virtual	IMonitorDisplay	&operator=(const IMonitorDisplay &b);

		virtual	void	draw(const IMonitorModule &module);
		virtual	void	render(void);
	private:
};

#endif
