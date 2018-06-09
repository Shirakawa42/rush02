#ifndef LOG_HPP
# define LOG_HPP

# include <string>
# include <fstream>

class	Log
{
	public:
		Log(void);
		Log(const Log &b);
		Log(const std::string &file);
		~Log(void);

		Log		&operator=(const Log &b);
		Log		&operator<<(const std::string &s);
		Log		&operator<<(long n);
		Log		&operator<<(unsigned long n);
		Log		&operator<<(std::ostream& (*pf)(std::ostream&));

		std::string	getFile(void) const;
	private:
		std::string		_file;
		std::ofstream	_stream;
		bool			_nl;
};

extern Log	_log;

#endif
