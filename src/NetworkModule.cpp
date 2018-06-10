#include "NetworkModule.hpp"
#include "Log.hpp"
#include <iostream>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>

NetworkModule::NetworkModule(void)
{
	input_speed = 0;
	output_speed = 0;
	prev_input = 0;
	prev_output = 0;
	refresh_rate = 1000000;
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

void	NetworkModule::drawTerm(Terminal &terminal)
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
	std::string			s;

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
}

void	NetworkModule::drawWin(Window &window) const
{
	(void)window;
}
