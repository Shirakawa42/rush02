#include "HostModule.hpp"
#include <unistd.h>
#include <sys/sysctl.h>
#include <SDL2/SDL_ttf.h>
#include <Window.hpp>
#include <iostream>

HostModule::HostModule(void)
{
}

HostModule::HostModule(const HostModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
}

HostModule::HostModule(int x, int y, int width, int height)
{
	setX(x);
	setY(y);
	setWidth(width);
	setHeight(height);
}

HostModule::~HostModule(void)
{
}

HostModule	&HostModule::operator=(const HostModule &b)
{
	setX(b.getX());
	setY(b.getY());
	setWidth(b.getWidth());
	setHeight(b.getHeight());
	return (*this);
}

void	HostModule::drawTerm(Terminal &terminal)
{
	char		buffer[128];
	size_t		len = sizeof(buffer);
	time_t		t = time(0);
	std::string	s;

	printText(terminal, "Host Infos", (getWidth() - 10) / 2, 1);
	if (gethostname(buffer, sizeof(buffer)))
		buffer[0] = '\0';
	s = "Hostname: ";
	s.append(buffer);
	printText(terminal, s, 2, 3);
	if (getlogin_r(buffer, sizeof(buffer)))
		buffer[0] = '\0';
	s = "Username: ";
	s.append(buffer);
	printText(terminal, s, 2, 4);
	s = "OS: ";
	if (sysctlbyname("kern.ostype", buffer, &len, NULL, 0))
		buffer[0] = '\0';
	s.append(buffer).append(" ");
	if (sysctlbyname("kern.osrelease", buffer, &len, NULL, 0))
		buffer[0] = '\0';
	s.append(buffer);
	printText(terminal, s, 2, 5);
	s.resize(20);
	s.resize(strftime(const_cast<char*>(s.c_str()), s.length(), "%H:%M:%S", localtime(&t)));
	printText(terminal, s, (getWidth() - s.length()) / 2, 7);
}

void	HostModule::drawWin(Window &window)
{
	int x = this->getX();
	int y = this->getY();
	int w = this->getWidth();
	int h = this->getHeight();

	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;



	SDL_SetRenderDrawColor(window.getRenderer(), 52, 62, 77, 255);
	SDL_RenderFillRect(window.getRenderer(), &r);



	char		buffer[128];
	size_t		len = sizeof(buffer);
	time_t		t = time(0);
	std::string	s;


	window.writeText(x+5, y+5, "Host Infos", window.white);

	if (gethostname(buffer, sizeof(buffer)))
		buffer[0] = '\0';
	s = "Hostname: ";
	s.append(buffer);

	window.writeText(x+5, y+25, s, window.white);
	if (getlogin_r(buffer, sizeof(buffer)))
		buffer[0] = '\0';
	s = "Username: ";
	s.append(buffer);
	window.writeText(x+5, y+50, s, window.white);
	s = "OS: ";
	if (sysctlbyname("kern.ostype", buffer, &len, NULL, 0))
		buffer[0] = '\0';
	s.append(buffer).append(" ");
	if (sysctlbyname("kern.osrelease", buffer, &len, NULL, 0))
		buffer[0] = '\0';
	s.append(buffer);
	//printText(terminal, s, 2, 5);
	window.writeText(x+5, y+75, s, window.white);
	s.resize(20);
	s.resize(strftime(const_cast<char*>(s.c_str()), s.length(), "%H:%M:%S", localtime(&t)));
	window.writeText(x+5, y+95, s, window.white);



	(void)window;
}
