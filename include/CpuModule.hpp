#ifndef CPU_MODULE_HPP
# define CPU_MODULE_HPP

# include "IMonitorModule.hpp"
# include "CPU.hpp"

class	CpuModule : public IMonitorModule
{
	public:
		CpuModule(void);
		CpuModule(const CpuModule &b);
		CpuModule(int x, int y, int width, int height);
		~CpuModule(void);

		CpuModule	&operator=(const CpuModule &b);

		void	drawTerm(Terminal &terminal);
		void	drawWin(Window &window);
		void	drawRAM(Window &window);

	private:
};

#endif
