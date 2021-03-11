#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define FD_LIMIT 3
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

int		get_next_line(int fd, char **line);

#endif
