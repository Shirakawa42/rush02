#include "NetworkModule.hpp"

NetworkModule::NetworkModule(void)
{
}

NetworkModule::NetworkModule(const NetworkModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
}

NetworkModule::NetworkModule(int x, int y, int width, int height)
{
	setX(x);
	setY(y);
	setWidth(width);
	setHeight(height);
}

NetworkModule::~NetworkModule(void)
{
}

NetworkModule	&NetworkModule::operator=(const NetworkModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
	return (*this);
}

void	NetworkModule::drawTerm(Terminal &terminal) const
{
	std::string	s;

	printText(terminal, "Network", (getWidth() - 3) / 2, 1);
}

void	NetworkModule::drawWin(Window &window) const
{
	(void)window;
}

