#ifndef I_MONITOR_MODULE_HPP
# define I_MONITOR_MODULE_HPP

# include "Terminal.hpp"
//# include "Window.hpp"


class Window;

class	IMonitorModule
{
	public:
		IMonitorModule(void);
		IMonitorModule(const IMonitorModule &b);
		IMonitorModule(int x, int y, int width, int height);
		virtual	~IMonitorModule(void);

		virtual	IMonitorModule	&operator=(const IMonitorModule &b);

		virtual void	drawTerm(Terminal &terminal);
		virtual void	drawWin(Window &window);

		void			printText(Terminal &terminal, const std::string &s, int x, int y) const;

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
