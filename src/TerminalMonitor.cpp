#include "TerminalMonitor.hpp"
#include <iostream>
#include "Log.hpp"

TerminalMonitor::TerminalMonitor(void)
{
}

TerminalMonitor::TerminalMonitor(const TerminalMonitor &b)
{
	(void)b;
}

TerminalMonitor::~TerminalMonitor(void)
{
}

IMonitorDisplay	&TerminalMonitor::operator=(const IMonitorDisplay &b)
{
	(void)b;
	return (*this);
}

Terminal	&TerminalMonitor::getTerm(void)
{
	return (_term);
}

void	TerminalMonitor::draw(IMonitorModule &module)
{
	module.drawTerm(_term);
	_term.drawBox(module.getX() - 1, module.getY() - 1, module.getWidth() + 2, module.getHeight() + 2);
}

void	TerminalMonitor::render(void)
{
	_term.swapBuffers();
}
