#include "Log.hpp"
#include <iostream>

Log	_log("log");

Log::Log(void)
{
	_file = "log";
	_stream.open(_file, std::fstream::out | std::fstream::app);
	_nl = true;
}

Log::Log(const Log &b)
{
	_file = b.getFile();
	_stream.open(_file, std::fstream::out | std::fstream::app);
	_nl = true;
}

Log::Log(const std::string &file)
{
	_file = file;
	_stream.open(_file, std::fstream::out | std::fstream::app);
	_nl = true;
}

Log::~Log(void)
{
	if (_stream.is_open())
		_stream.close();
}

Log		&Log::operator=(const Log &b)
{
	_file = b.getFile();
	_nl = true;
	return (*this);
}

Log		&Log::operator<<(const std::string &s)
{
	if (_stream.is_open())
	{
		if (_nl == true)
		{
			std::string	str;
			time_t		t = time(0);

			str.resize(20);
			str.resize(strftime(const_cast<char*>(str.c_str()), str.length(), "%G%m%d_%H%M%S", localtime(&t)));
			_stream << "[" << str << "] ";
		}
		_stream << s;
		_nl = false;
	}
	return (*this);
}

Log		&Log::operator<<(long n)
{
	if (_stream.is_open())
	{
		if (_nl == true)
		{
			std::string	str;
			time_t		t = time(0);

			str.resize(20);
			str.resize(strftime(const_cast<char*>(str.c_str()), str.length(), "%G%m%d_%H%M%S", localtime(&t)));
			_stream << "[" << str << "] ";
		}
		_stream << n;
		_nl = false;
	}
	return (*this);
}

Log		&Log::operator<<(unsigned long n)
{
	if (_stream.is_open())
	{
		if (_nl == true)
		{
			std::string	str;
			time_t		t = time(0);

			str.resize(20);
			str.resize(strftime((char *)str.c_str(), str.length(), "%G%m%d_%H%M%S", localtime(&t)));
			_stream << "[" << str << "] ";
		}
		_stream << n;
		_nl = false;
	}
	return (*this);
}

Log		&Log::operator<<(std::ostream& (*pf)(std::ostream&))
{
	if (_stream.is_open())
	{
		pf(_stream);
		_nl = true;
	}
	return (*this);
}

std::string	Log::getFile(void) const
{
	return (_file);
}
