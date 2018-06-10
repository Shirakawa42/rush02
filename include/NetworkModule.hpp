#ifndef NETWORK_MODULE_HPP
# define NETWORK_MODULE_HPP

# include "IMonitorModule.hpp"

class	NetworkModule : public IMonitorModule
{
	public:
		NetworkModule(void);
		NetworkModule(const NetworkModule &b);
		NetworkModule(int x, int y, int width, int height);
		~NetworkModule(void);

		NetworkModule	&operator=(const NetworkModule &b);

		void	drawTerm(Terminal &terminal);
		void	drawWin(Window &window) const;
	private:
		size_t			input_speed;
		size_t			output_speed;
		size_t			prev_input;
		size_t			prev_output;
		struct timeval	prev;
		size_t			refresh_rate;
};

#endif
