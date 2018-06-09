#ifndef I_MONITOR_MODULE_HPP
# define I_MONITOR_MODULE_HPP

class	IMonitorModule
{
	public:
		IMonitorModule(void);
		IMonitorModule(const IMonitorModule &b);
		virtual	~IMonitorModule(void);

		virtual	IMonitorModule	&operator=(const IMonitorModule &b);
	private:
};

#endif
