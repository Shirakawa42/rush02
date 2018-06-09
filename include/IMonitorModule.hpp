#ifndef I_MONITOR_MODULE_HPP
# define I_MONITOR_MODULE_HPP

# include "Terminal.hpp"
# include "Window.hpp"

class	IMonitorModule
{
	public:
		IMonitorModule(void);
		IMonitorModule(const IMonitorModule &b);
		~IMonitorModule(void);

		virtual	IMonitorModule	&operator=(const IMonitorModule &b);

		virtual void	drawTerm(Terminal &terminal) const;
		virtual void	drawWin(Window &window) const;

		void	setWidth(int width);
		void	setHeight(int height);
		void	setX(int x);
		void	setY(int y);
		int		getWidth(void) const;
		int		getHeight(void) const;
		int		getX(void) const;
		int		getY(void) const;
	private:
		int		_width;
		int		_height;
		int		_x;
		int		_y;
};

#endif
