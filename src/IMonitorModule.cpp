#include "IMonitorModule.hpp"
#include <Log.hpp>

IMonitorModule::IMonitorModule(void)
{
}

IMonitorModule::IMonitorModule(const IMonitorModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
}

IMonitorModule::IMonitorModule(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}

IMonitorModule::~IMonitorModule(void)
{
}

IMonitorModule	&IMonitorModule::operator=(const IMonitorModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
	return (*this);
}

void	IMonitorModule::drawTerm(Terminal &terminal)
{
	for (int x = _x; x < _x + _width; x++)
		for (int y = _y; y < _y + _height; y++)
			terminal.print(x, y, COLOR_RESET, 'O');
}

void	IMonitorModule::drawWin(Window &window) const
{
	(void)window;
}

void	IMonitorModule::printText(Terminal &terminal, const std::string &s, int x, int y) const
{
	std::string	out;

	x += _x;
	y += _y;
	if (x >= _x && x < _width + _x &&
		y >= _y && y < _height + _y)
	{
		out = s;
		if (x + static_cast<int>(s.length()) > _width + _x)
		{
			out.resize(_width - y);
			if (out.length() <= 3)
			{
				for (size_t i = 0; i < out.length(); i++)
					out[i] = '.';
			}
			else
			{
				out.pop_back();
				out.pop_back();
				out.pop_back();
				out.push_back('.');
				out.push_back('.');
				out.push_back('.');
			}
		}
		terminal.print(x, y, COLOR_RESET, out);
	}
}

void	IMonitorModule::setWidth(int width)
{
	_width = width;
}

void	IMonitorModule::setHeight(int height)
{
	_height = height;
}

void	IMonitorModule::setX(int x)
{
	_x = x;
}

void	IMonitorModule::setY(int y)
{
	_y = y;
}

int		IMonitorModule::getWidth(void) const
{
	return (_width);
}

int		IMonitorModule::getHeight(void) const
{
	return (_height);
}

int		IMonitorModule::getX(void) const
{
	return (_x);
}

int		IMonitorModule::getY(void) const
{
	return (_y);
}
