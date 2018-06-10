#ifndef TERMINAL_HPP
# define TERMINAL_HPP

# include <string>

# define COLOR_RESET		0
# define COLOR_GREY			8
# define COLOR_CYAN2		9
# define COLOR_GREEN2		10
# define COLOR_CYAN3		11
# define COLOR_MAGENTA3		12
# define COLOR_BLUE2		13
# define COLOR_BOX			1
# define COLOR_GRAPH_CPU	2
# define COLOR_GRAPH_RAM	3
# define COLOR_GRAPH_RX		4
# define COLOR_GRAPH_TX		5

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
