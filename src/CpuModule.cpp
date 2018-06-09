#include "CpuModule.hpp"
#include "Log.hpp"
#include <iostream>

CpuModule::CpuModule(void)
{
}

CpuModule::CpuModule(const CpuModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
}

CpuModule::CpuModule(int x, int y, int width, int height)
{
	setX(x);
	setY(y);
	setWidth(width);
	setHeight(height);
}

CpuModule::~CpuModule(void)
{
}

CpuModule	&CpuModule::operator=(const CpuModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
	return (*this);
}

void	CpuModule::drawTerm(Terminal &terminal) const
{
	std::string	s;

	printText(terminal, "CPU", (getWidth() - 3) / 2, 1);
	s = "Name: ";
	s.append(cpu.getName());
	printText(terminal, s, 2, 3);
	s = "Frequency: ";
	s.append(std::to_string(static_cast<double>(cpu.getMaxFrequency()) / 1000000000)).append(" Ghz");
	printText(terminal, s, 2, 4);
	s = "Cores: ";
	s.append(std::to_string(cpu.getNumberOfCores()));
	printText(terminal, s, 2, 5);
	s = "Usage: ";
	s.append(std::to_string(cpu.getCurrentUsage()));
	printText(terminal, s, 2, 6);
}

void	CpuModule::drawWin(Window &window) const
{
	(void)window;
}
