#ifndef NETWORK_MODULE_HPP
# define NETWORK_MODULE_HPP

# include "IMonitorModule.hpp"

class	NetworkModule : public IMonitorModule
{
	public:
		NetworkModule(void);
		NetworkModule(const NetworkModule &b);
		NetworkModule(int x, int y, int width, int height);
		~NetworkModule(void);

		NetworkModule	&operator=(const NetworkModule &b);

		void	drawTerm(Terminal &terminal) const;
		void	drawWin(Window &window) const;
	private:
};

#endif
