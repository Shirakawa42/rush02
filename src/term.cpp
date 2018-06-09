#include "ft_gkrellm.hpp"
#include <ncurses.h>

void	manage_term_inputs(void)
{
	int		c;

	if ((c = getch()) != ERR)
	{
//		_log << "key '" << (long)c << "'' pressed" << std::endl;
		switch (c)
		{
			case 27:
				exit(1);
				break ;
			default:
//				_log << "key '" << (long)c << "' not handled" << std::endl;
				break;
		}
	}
}
