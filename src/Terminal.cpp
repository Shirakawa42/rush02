#include "Terminal.hpp"
#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <exception>
#include <iostream>
#include "Log.hpp"

Terminal::Terminal(void)
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	getmaxyx(stdscr, _height, _width);
	start_color();
	init_color(COLOR_GREY, 200, 200, 200);
	init_color(COLOR_CYAN2, 200, 300, 200);
	init_pair(COLOR_RESET, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_BOX, COLOR_CYAN2, COLOR_GREY);
	_log << "termsize(" << static_cast<long>(_width) << ";" <<
		static_cast<long>(_height) << ")" << std::endl;
	start_color();
	try
	{
		_buffer[0] = new t_color[_width * _height];
		_buffer[1] = new t_color[_width * _height];
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	_index = 0;
}

Terminal::Terminal(const Terminal &b)
{
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	_width = b.getWidth();
	_height = b.getHeight();
	start_color();
	init_color(COLOR_BOX, 500, 500, 500);
	try
	{
		_buffer[0] = new t_color[_width * _height];
		_buffer[1] = new t_color[_width * _height];
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
			_buffer[0] = new t_color[_width * _height];
			_buffer[1] = new t_color[_width * _height];
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
			_buffer[0] = new t_color[_width * _height];
			_buffer[1] = new t_color[_width * _height];
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
		{
			_buffer[_index][i].color = COLOR_RESET;
			_buffer[_index][i].character = ' ';
		}
}

void		Terminal::print(int x, int y, unsigned char color, char c)
{
	if (x >= 0 && x < _width &&
		y >= 0 && y < _height)
	{
		_buffer[_index][y * _width + x].color = color;
		_buffer[_index][y * _width + x].character = c;
	}
}

void		Terminal::print(int x, int y, unsigned char color, const std::string &str)
{
	for (int i = 0; i < static_cast<int>(str.length()); i++)
		if (x + i >= 0 && x + i < _width &&
			y >= 0 && y < _height)
		{
			_buffer[_index][y * _width + x + i].color = color;
			_buffer[_index][y * _width + x + i].character = str[i];
		}
}

void		Terminal::swapBuffers(void)
{
	unsigned char	index = (_index + 1) % 2;

	for (int i = 0; i < _width * _height; i++)
		if (_buffer[_index][i].character != _buffer[index][i].character ||
			_buffer[_index][i].color != _buffer[index][i].color)
		{
			attrset(COLOR_PAIR(_buffer[_index][i].color));
			mvaddch(i / _width, i % _width, _buffer[_index][i].character);
		}
	_index = index;
	refresh();
	clear();
}

void	Terminal::drawBox(int x, int y, int width, int height)
{
	attrset(COLOR_PAIR(COLOR_BOX));
	for (int i = 0; i < width; i++)
	{
		print(x + i, y, COLOR_BOX, '-');
		print(x + i, y + height - 1, COLOR_BOX, '-');
	}
	for (int i = 0; i < height; i++)
	{
		print(x, y + i, COLOR_BOX, '|');
		print(x + width - 1, y + i, COLOR_BOX, '|');
	}
	print(x, y, COLOR_BOX, '+');
	print(x + width - 1, y, COLOR_BOX, '+');
	print(x, y + height - 1, COLOR_BOX, '+');
	print(x + width - 1, y + height - 1, COLOR_BOX, '+');
	attrset(COLOR_PAIR(COLOR_RESET) | A_NORMAL);
}
