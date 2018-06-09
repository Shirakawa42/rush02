#include "IMonitorDisplay.hpp"

IMonitorDisplay::IMonitorDisplay(void)
{
}

IMonitorDisplay::IMonitorDisplay(const IMonitorDisplay &b)
{
	(void)b;
}

IMonitorDisplay::~IMonitorDisplay(void)
{
}

IMonitorDisplay	&IMonitorDisplay::operator=(const IMonitorDisplay &b)
{
	(void)b;
	return (*this);
}

void	IMonitorDisplay::draw(const IMonitorModule &module)
{
	(void)module;
}

void	IMonitorDisplay::render(void)
{
}
