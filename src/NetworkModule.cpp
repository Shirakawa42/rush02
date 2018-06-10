#include "NetworkModule.hpp"
#include "Log.hpp"
#include <iostream>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>

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
	s.append(std::to_string((input / (1 << 30)) % 1024)).append(" Go ");
	s.append(std::to_string((input / (1 << 20)) % 1024)).append(" Mo ");
	s.append(std::to_string((input / (1 << 10)) % 1024)).append(" Ko ");
	s.append(std::to_string(input % 1024)).append(" bytes");
	printText(terminal, s, 2, 3);
	s = "Output: ";
	s.append(std::to_string((output / (1 << 30)) % 1024)).append(" Go ");
	s.append(std::to_string((output / (1 << 20)) % 1024)).append(" Mo ");
	s.append(std::to_string((output / (1 << 10)) % 1024)).append(" Ko ");
	s.append(std::to_string(output % 1024)).append(" bytes");
	printText(terminal, s, 2, 4);
}

void	NetworkModule::drawWin(Window &window) const
{
	(void)window;
}
