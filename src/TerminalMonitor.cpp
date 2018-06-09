#include "TerminalMonitor.hpp"

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

void	TerminalMonitor::draw(const IMonitorModule &module)
{
	module.drawTerm(_term);
}

void	TerminalMonitor::render(void)
{
	_term.swapBuffers();
}
