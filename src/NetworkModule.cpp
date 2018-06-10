#include "NetworkModule.hpp"
#include "Log.hpp"
#include <iostream>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>
#include <SDL2/SDL.h>
#include <Window.hpp>
#include <iostream>

NetworkModule::NetworkModule(void)
{
	input_speed = 0;
	output_speed = 0;
	prev_input = 0;
	prev_output = 0;
	refresh_rate = 1000000;
	prev = (struct timeval){0, 0};
	this->_speedHistory.reserve(100);
	this->_speedHistory2.reserve(100);
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

size_t	get_max(std::vector<size_t> &vector)
{
	size_t	max = 0;

	for (size_t i = 0; i < vector.size(); i++)
		if (vector[i] > max)
			max = vector[i];
	return (max);
}

void	NetworkModule::drawTerm(Terminal &terminal)
{
	static struct timeval	prev;
    size_t					len;
	size_t					input;
	size_t					output;
	int						mib[] = {
        CTL_NET,
        PF_ROUTE,
        0,
        0,
        NET_RT_IFLIST2,
        0
    };
	char					*buffer;
	struct if_msghdr		*next;
	size_t					refresh_rate = 1000000;
	std::string				s;

	printText(terminal, "Network", (getWidth() - 7) / 2, 1);
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return ;
	try
	{
		buffer = new char[len];
	}
	catch (const std::exception &e)
	{
		_log << e.what() << std::endl;
		return ;
	}
	if (sysctl(mib, sizeof(mib) / sizeof(int), buffer, &len, NULL, 0) < 0)
		return ;

	input = 0;
	output = 0;
	for (next = reinterpret_cast<struct if_msghdr *>(buffer); static_cast<void *>(next) < buffer + len; next = reinterpret_cast<struct if_msghdr *>(reinterpret_cast<size_t>(next) + next->ifm_msglen))
		if (next->ifm_type == RTM_IFINFO2)
        {
			input += reinterpret_cast<struct if_msghdr2 *>(next)->ifm_data.ifi_ibytes;
			output += reinterpret_cast<struct if_msghdr2 *>(next)->ifm_data.ifi_obytes;
		}

	delete buffer;

	s = "Input: ";
	if ((input / (1 << 30)) % 1024)
		s.append(std::to_string((input / (1 << 30)) % 1024)).append(" Go ");
	if ((input / (1 << 20)) % 1024)
		s.append(std::to_string((input / (1 << 20)) % 1024)).append(" Mo ");
	if ((input / (1 << 10)) % 1024)
		s.append(std::to_string((input / (1 << 10)) % 1024)).append(" Ko ");
	if (input % 1024)
		s.append(std::to_string(input % 1024)).append(" bytes");
	printText(terminal, s, 2, 3);
	s = "Output: ";
	if ((output / (1 << 30)) % 1024)
		s.append(std::to_string((output / (1 << 30)) % 1024)).append(" Go ");
	if ((output / (1 << 20)) % 1024)
		s.append(std::to_string((output / (1 << 20)) % 1024)).append(" Mo ");
	if ((output / (1 << 10)) % 1024)
		s.append(std::to_string((output / (1 << 10)) % 1024)).append(" Ko ");
	if (output % 1024)
		s.append(std::to_string(output % 1024)).append(" bytes");
	printText(terminal, s, 2, 4);

	struct timeval			now;
	size_t					diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - prev.tv_sec) * 1000000 + (now.tv_usec - prev.tv_usec);
	if (diff >= refresh_rate)
	{
		input_speed = (1000000 * (input - prev_input)) / diff;
		output_speed = (1000000 * (output - prev_output)) / diff;
		prev_input = input;
		prev_output = output;
		if (_speedHistory.size() == 100)
			_speedHistory.erase(_speedHistory.begin());
		_speedHistory.push_back(input_speed);

		if (_speedHistory2.size() == 100)
			_speedHistory2.erase(_speedHistory2.begin());
		_speedHistory2.push_back(output_speed);
		prev = now;
	}
	s = "Input speed: ";
	if ((input_speed / (1 << 30)) % 1024)
		s.append(std::to_string((input_speed / (1 << 30)) % 1024)).append(" Go ");
	if ((input_speed / (1 << 20)) % 1024)
		s.append(std::to_string((input_speed / (1 << 20)) % 1024)).append(" Mo ");
	if ((input_speed / (1 << 10)) % 1024)
		s.append(std::to_string((input_speed / (1 << 10)) % 1024)).append(" Ko ");
	if (input_speed % 1024)
		s.append(std::to_string(input_speed % 1024)).append(" bytes");
	printText(terminal, s, 2, 6);
	s = "Output speed: ";
	if ((output_speed / (1 << 30)) % 1024)
		s.append(std::to_string((output_speed / (1 << 30)) % 1024)).append(" Go ");
	if ((output_speed / (1 << 20)) % 1024)
		s.append(std::to_string((output_speed / (1 << 20)) % 1024)).append(" Mo ");
	if ((output_speed / (1 << 10)) % 1024)
		s.append(std::to_string((output_speed / (1 << 10)) % 1024)).append(" Ko ");
	if (output_speed % 1024)
		s.append(std::to_string(output_speed % 1024)).append(" bytes");
	printText(terminal, s, 2, 7);

	if (getHeight() > 9)
	{
		int		x, y;
		for (int i = 0; i < getWidth(); i++)
		{
			x = _speedHistory.size() - getWidth() + i;
			if (x >= 0 && get_max(_speedHistory))
				y = 9 + (getHeight() - 9) / 2 - (_speedHistory[x] * ((getHeight() - 9) / 2)) / get_max(_speedHistory);
			else
				y = 9 + (getHeight() - 9) / 2;
			for (int j = y; j < 9 + (getHeight() - 9) / 2; j++)
				terminal.print(i + getX(), j + getY(), COLOR_GRAPH_RX, ' ');

			x = _speedHistory2.size() - getWidth() + i;
			if (x >= 0 && get_max(_speedHistory2))
				y = 9 + (getHeight() - 9) / 2 + (_speedHistory2[x] * ((getHeight() - 9) / 2)) / get_max(_speedHistory2);
			else
				y = 9 + (getHeight() - 9) / 2 - 1;
			for (int j = y; j >= 9 + (getHeight() - 9) / 2; j--)
				terminal.print(i + getX(), j + getY(), COLOR_GRAPH_TX, ' ');
		}
	}
}

static double remap(double value, double low1, double high1, double low2, double high2)
{
	return (low2 + (value - low1) * (high2 - low2) / (high1 - low1));
}



void	NetworkModule::drawWin(Window &window)
{
	size_t				len;
	size_t				input;
	size_t				output;
	int					mib[] = {
        CTL_NET,
        PF_ROUTE,
        0,
        0,
        NET_RT_IFLIST2,
        0
    };
	char				*buffer;
	struct if_msghdr	*next;


	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return ;
	try
	{
		buffer = new char[len];
	}
	catch (const std::exception &e)
	{
		_log << e.what() << std::endl;
		return ;
	}
	if (sysctl(mib, sizeof(mib) / sizeof(int), buffer, &len, NULL, 0) < 0)
		return ;

	input = 0;
	output = 0;
	for (next = reinterpret_cast<struct if_msghdr *>(buffer); static_cast<void *>(next) < buffer + len; next = reinterpret_cast<struct if_msghdr *>(reinterpret_cast<size_t>(next) + next->ifm_msglen))
		if (next->ifm_type == RTM_IFINFO2)
        {
			input += reinterpret_cast<struct if_msghdr2 *>(next)->ifm_data.ifi_ibytes;
			output += reinterpret_cast<struct if_msghdr2 *>(next)->ifm_data.ifi_obytes;
		}

	delete buffer;

	struct timeval			now;
	size_t					diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - prev.tv_sec) * 1000000 + (now.tv_usec - prev.tv_usec);
	if (diff >= refresh_rate)
	{
		input_speed = (1000000 * (input - prev_input)) / diff;
		output_speed = (1000000 * (output - prev_output)) / diff;
		prev_input = input;
		prev_output = output;
		prev = now;
	}

	if (this->_speedHistory.size() == 100)
		this->_speedHistory.erase(this->_speedHistory.begin());
	_speedHistory.push_back(this->input_speed);

	if (this->_speedHistory2.size() == 100)
		this->_speedHistory2.erase(this->_speedHistory2.begin());
	_speedHistory2.push_back(this->output_speed);





	int x = this->getX();
	int y = this->getY();
	int w = this->getWidth();
	int h = this->getHeight();

	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h/2;


	SDL_SetRenderDrawColor(window.getRenderer(), 52, 62, 77, 255);
	SDL_RenderFillRect(window.getRenderer(), &r);


	SDL_SetRenderDrawColor(window.getRenderer(), 78, 142, 168, 255);

	size_t i = 0;
	SDL_Point list[ _speedHistory.size()];
	std::vector<size_t>	cpy = _speedHistory;
	std::sort(cpy.begin(), cpy.end());
	size_t top = cpy.back();
	while (i < _speedHistory.size())
	{
		double realx = remap(static_cast<double>(i), static_cast<double>(0), static_cast<double>(99), static_cast<double>(0), static_cast<double>(w) );

		double realy = remap(static_cast<double>(100 - remap(_speedHistory[i],0,top, 0, 99)), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h/2) );
		list[i].x = x + realx;
		list[i].y = y + realy;
		i++;
	}
	SDL_RenderDrawLines(window.getRenderer(), list, _speedHistory.size());
	window.writeText(x+10, y+10, std::string("Download speed (100 sec): "), window.white);
	window.writeText(x+10, y+30, std::string("Current download speed : ") + std::to_string(input_speed/1000000) + "Mbps", window.white);
	window.writeText(x+10, y+50, std::string("Max download speed : ") + std::to_string(top/1000000) + "Mbps", window.white);
	{

		r.x = x;
		r.y = y+h/2;
		r.w = w;
		r.h = h/2;


		SDL_SetRenderDrawColor(window.getRenderer(), 52, 62, 77, 255);
		SDL_RenderFillRect(window.getRenderer(), &r);


		SDL_SetRenderDrawColor(window.getRenderer(), 78, 142, 168, 255);
		size_t i = 0;
		SDL_Point list[ _speedHistory2.size()];
		std::vector<size_t>	cpy = _speedHistory2;
		std::sort(cpy.begin(), cpy.end());
		size_t top = cpy.back();
		while (i < _speedHistory2.size())
		{
			double realx = remap(static_cast<double>(i), static_cast<double>(0), static_cast<double>(99), static_cast<double>(0), static_cast<double>(w) );

			double realy = remap(static_cast<double>(100 - remap(_speedHistory2[i],0,top, 0, 99)), static_cast<double>(0), static_cast<double>(100), static_cast<double>(0), static_cast<double>(h/2) );
			list[i].x = x + realx;
			list[i].y = (y+h/2) + realy;
			i++;
		}
		SDL_RenderDrawLines(window.getRenderer(), list, _speedHistory2.size());
		window.writeText(x+10, y+h/2+10, std::string("Upload speed (100 sec): "), window.white);
		window.writeText(x+10, y+h/2+30, std::string("Current Upload speed : ") + std::to_string(output_speed/1000000) + "Mbps", window.white);
		window.writeText(x+10, y+h/2+50, std::string("Max Upload speed : ") + std::to_string(top/1000000) + "Mbps", window.white);
	}


}

