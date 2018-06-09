#include "IMonitorModule.hpp"
#include <Log.hpp>

IMonitorModule::IMonitorModule(void)
{
}

IMonitorModule::IMonitorModule(const IMonitorModule &b)
{
	(void)b;
}

IMonitorModule::~IMonitorModule(void)
{
}

IMonitorModule	&IMonitorModule::operator=(const IMonitorModule &b)
{
	(void)b;
	return (*this);
}

void	IMonitorModule::drawTerm(Terminal &terminal) const
{
	for (int x = _x; x < _x + _width; x++)
		for (int y = _y; y < _y + _height; y++)
			terminal.print('O', x, y);
}

void	IMonitorModule::drawWin(Window &window) const
{
	(void)window;
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
