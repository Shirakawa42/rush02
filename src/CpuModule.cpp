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
	static struct timeval	prev;
	static size_t			refresh_time = 500000;
	static float			prev_usage = 0;
	struct timeval			now;
	std::string				s;

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
	gettimeofday(&now, NULL);
	if (static_cast<size_t>((now.tv_sec - prev.tv_sec) * 1000000 +
		(now.tv_usec - prev.tv_usec)) >= refresh_time)
	{
		prev_usage = cpu.getCurrentUsage();
		prev = now;
	}
	s.append(std::to_string(prev_usage));
	printText(terminal, s, 2, 6);
}

void	CpuModule::drawWin(Window &window) const
{
	(void)window;
}
