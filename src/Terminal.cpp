#include "Terminal.hpp"
#include <ncurses.h>
#include <exception>
#include <iostream>

Terminal::Terminal(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	getmaxyx(stdscr, _height, _width);
	start_color();
	try
	{
		_buffer[0] = new char[_width * _height];
		_buffer[1] = new char[_width * _height];
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	_index = 0;
}

Terminal::Terminal(const Terminal &b)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	_width = b.getWidth();
	_height = b.getHeight();
	start_color();
	try
	{
		_buffer[0] = new char[_width * _height];
		_buffer[1] = new char[_width * _height];
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	_index = 0;
}

Terminal::~Terminal(void)
{
	endwin();
}

Terminal	&Terminal::operator=(const Terminal &b)
{
	if (_width != b.getWidth() || _height != b.getHeight())
	{
		_width = b.getWidth();
		_height = b.getHeight();
		try
		{
			delete[] _buffer[0];
			delete[] _buffer[1];
			_buffer[0] = new char[_width * _height];
			_buffer[1] = new char[_width * _height];
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (*this);
}

int			Terminal::getWidth(void) const
{
	return (_width);
}

int			Terminal::getHeight(void) const
{
	return (_height);
}

void		Terminal::resize(int width, int height)
{
	if (width != _width || height != _height)
	{
		_width = width;
		_height = height;
		try
		{
			delete[] _buffer[0];
			delete[] _buffer[1];
			_buffer[0] = new char[_width * _height];
			_buffer[1] = new char[_width * _height];
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void		Terminal::clear(void)
{
	int		i = 0;

	for (int x = 0; x < _width; x++)
		for (int y = 0; y < _height; y++ && i++)
			_buffer[_index][i] = ' ';
}

void		Terminal::print(char c, int x, int y)
{
	if (x >= 0 && x < _width &&
		y >= 0 && y < _height)
		_buffer[_index][y * _height + x] = c;
}

void		Terminal::swapBuffers(void)
{
	unsigned char	index = (_index + 1) % 2;
	int				i = 0;

	for (int x = 0; x < _width; x++)
		for (int y = 0; y < _height; y++ && i++)
			if (_buffer[_index][i] != _buffer[index][i])
				mvaddch(x, y, _buffer[_index][i]);
	_index = index;
	refresh();
	clear();
}
