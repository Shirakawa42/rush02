#include "CpuModule.hpp"
#include "Log.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <Window.hpp>

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

void	CpuModule::drawTerm(Terminal &terminal)
{
	static struct timeval	prev;
	static size_t			refresh_time = 500000;
	static float			prev_usage = 0;
	static size_t			prev_used_memory = 0;
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
		prev_used_memory = cpu.getUsedMemory();
		prev = now;
	}
	s.append(std::to_string(prev_usage));
	printText(terminal, s, 2, 6);
	s = "RAM: ";
	if ((prev_used_memory / (1 << 30)) % 1024)
		s.append(std::to_string((prev_used_memory / (1 << 30)) % 1024)).append(" Go ");
	if ((prev_used_memory / (1 << 20)) % 1024)
		s.append(std::to_string((prev_used_memory / (1 << 20)) % 1024)).append(" Mo ");
	if ((prev_used_memory / (1 << 10)) % 1024)
		s.append(std::to_string((prev_used_memory / (1 << 10)) % 1024)).append(" Ko ");
	if (prev_used_memory % 1024)
		s.append(std::to_string(prev_used_memory % 1024)).append(" bytes");
	s.append(" / ");
	if ((cpu.getMemorySize() / (1 << 30)) % 1024)
		s.append(std::to_string((cpu.getMemorySize() / (1 << 30)) % 1024)).append(" Go ");
	if ((cpu.getMemorySize() / (1 << 20)) % 1024)
		s.append(std::to_string((cpu.getMemorySize() / (1 << 20)) % 1024)).append(" Mo ");
	if ((cpu.getMemorySize() / (1 << 10)) % 1024)
		s.append(std::to_string((cpu.getMemorySize() / (1 << 10)) % 1024)).append(" Ko ");
	if (cpu.getMemorySize() % 1024)
		s.append(std::to_string(cpu.getMemorySize() % 1024)).append(" bytes");
	printText(terminal, s, 2, 7);

	printText(terminal, "CPU History:", 2, 9);
	if (getHeight() > 12)
	{
		std::vector<int>	cpuHistoryGraph = cpu.getHistory();
		int					x, y;
		for (int i = 0; i < getWidth(); i++)
		{
			x = cpuHistoryGraph.size() - getWidth() + i;
			if (x >= 0)
				y = (cpuHistoryGraph[x] * (getHeight() - 12)) / -100 + getHeight();
			else
				y = getHeight() + 1;
			for (int j = y; j < getHeight() + 1; j++)
				terminal.print(i + getX(), j + getY(), COLOR_GRAPH_CPU, ' ');
		}
	}
}

double remap(double value, double low1, double high1, double low2, double high2)
{
	return (low2 + (value - low1) * (high2 - low2) / (high1 - low1));
}


void	CpuModule::drawWin(Window &window)

{
	int x = this->getX();
	int y = this->getY();
	int w = this->getWidth();
	int h = this->getHeight()/2;

	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	double cpuUsage = cpu.getCurrentUsage();
	std::vector<int> cpuHistoryGraph = cpu.getHistory();
	int currentPercantage = cpuHistoryGraph[cpuHistoryGraph.size()-1];
	SDL_SetRenderDrawColor(window.getRenderer(), 52, 62, 77, 255);
	SDL_RenderFillRect(window.getRenderer(), &r);

	SDL_Rect	r2;
	int offset = remap(static_cast<double>(100-currentPercantage), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h) );
	r2.x = x;
	r2.y = y + offset;
	r2.w = w;
	r2.h = h  - offset;

	SDL_SetRenderDrawColor(window.getRenderer(), 47, 85, 101, 255);
	int i0 = 50;
	
	while (i0 < w)
	{
		SDL_RenderDrawLine(window.getRenderer(), x + i0, y, x + i0, y+h);
		i0 += 50;
	}
	SDL_SetRenderDrawColor(window.getRenderer(), 57, 104, 123, 255);
	SDL_RenderFillRect(window.getRenderer(), &r2);

	SDL_SetRenderDrawColor(window.getRenderer(), 78, 142, 168, 255);
	size_t i = 0;
	SDL_Point list[ cpuHistoryGraph.size()];
	while (i < cpuHistoryGraph.size())
	{
		double realx = remap(static_cast<double>(i), static_cast<double>(0), static_cast<double>(99), static_cast<double>(0), static_cast<double>(w) );
		double realy = remap(static_cast<double>(100-cpuHistoryGraph[i]), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h) );
		list[i].x = x + realx;
		list[i].y = y + realy;
		i++;
	}
	SDL_RenderDrawLines(window.getRenderer(), list, cpuHistoryGraph.size());


	window.writeText(x+10, y+10, std::string("CPU usage: ") + std::to_string(static_cast<int>(cpuUsage)) + '%', window.white);
	window.writeText(x+10, y+30, std::string("Number of cores : ") + std::to_string(cpu.getNumberOfCores()) , window.white);
	window.writeText(x+10, y+50, std::string("CPU Name: ") + cpu.getName() , window.white);
	drawRAM(window);
}

void	CpuModule::drawRAM(Window &window)
{
	int x = this->getX();
	int y = this->getY() + this->getHeight()/2+5;
	int w = this->getWidth();
	int h = this->getHeight()/2-5;

	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	size_t ram = cpu.getUsedMemory();
	std::vector<int> ramHistoryGraph = cpu.getRamHistory();
	SDL_SetRenderDrawColor(window.getRenderer(), 52, 62, 77, 255);
	SDL_RenderFillRect(window.getRenderer(), &r);

	SDL_SetRenderDrawColor(window.getRenderer(), 47, 85, 101, 255);

	int i0 = 50;
	
	while (i0 < w)
	{
		SDL_RenderDrawLine(window.getRenderer(), x + i0, y, x + i0, y+h);
		i0 += 50;
	}
	SDL_SetRenderDrawColor(window.getRenderer(), 57, 104, 123, 255);

	SDL_SetRenderDrawColor(window.getRenderer(), 78, 142, 168, 255);
	size_t i = 0;
	SDL_Point list[ ramHistoryGraph.size()];
	while (i < ramHistoryGraph.size())
	{
		double realx = remap(static_cast<double>(i), static_cast<double>(0), static_cast<double>(99), static_cast<double>(0), static_cast<double>(w) );
		double realy = remap(static_cast<double>(100-ramHistoryGraph[i]), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h) );
		list[i].x = x + realx;
		list[i].y = y + realy;
		i++;
	}
	SDL_RenderDrawLines(window.getRenderer(), list, ramHistoryGraph.size());


	window.writeText(x+10, y+10, std::string("Used Memory: ") + std::to_string(ram / 1024 / 1024) + std::string(" Mb"), window.white);

}

