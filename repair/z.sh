CC="cc"
CFLAGS="-Wall -Wextra -Werror"
LEAK="-fsanitize=leak"
SEGFA="-fsanitize=address"

HEAD="push_swap.h"
SRC="src/*.c"
LIBFT="libft/libft.a"

# $CC $CFLAGS $LEAK $HEAD $SRC $LIBFT

$CC $LEAK $HEAD $SRC $LIBFT
