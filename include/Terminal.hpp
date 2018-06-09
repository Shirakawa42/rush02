#ifndef TERMINAL_HPP
# define TERMINAL_HPP

# include <string>

# define COLOR_RESET	0
# define COLOR_GREY		8
# define COLOR_BOX		1

typedef struct		s_color
{
	unsigned char	color;
	char			character;
}					t_color;

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
		void		print(int x, int y, unsigned char color, char c);
		void		print(int x, int y, unsigned char color, const std::string &str);
		void		swapBuffers(void);
		void		drawBox(int x, int y, int width, int height);
	private:
		int				_width;
		int				_height;
		t_color			*_buffer[2];
		unsigned char	_index;
};

#endif
