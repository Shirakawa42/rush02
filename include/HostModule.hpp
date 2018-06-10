#ifndef HOST_MODULE_HPP
# define HOST_MODULE_HPP

# include "IMonitorModule.hpp"

class	HostModule : public IMonitorModule
{
	public:
		HostModule(void);
		HostModule(const HostModule &b);
		HostModule(int x, int y, int width, int height);
		~HostModule(void);

		HostModule	&operator=(const HostModule &b);

		void	drawTerm(Terminal &terminal) const;
		void	drawWin(Window &window) const;
	private:
};

#endif
