#ifndef TERMINAL_HPP
# define TERMINAL_HPP

class	Terminal
{
	public:
		Terminal(void);
		Terminal(const Terminal &b);
		~Terminal(void);

		Terminal	&operator=(const Terminal &b);

		int			getWidth(void) const;
		int			getHeight(void) const;

		void		resize(int width, int height);
		void		clear(void);
		void		print(char c, int x, int y);
		void		swapBuffers(void);
	private:
		int				_width;
		int				_height;
		char			*_buffer[2];
		unsigned char	_index;
};

#endif
