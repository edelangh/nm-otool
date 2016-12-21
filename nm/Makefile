
NAME = ft_nm
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror -g
OBJDIR = obj/
SRCS = main.c \
	   nm.c \
	   nm_error.c \
	   parse_file.c \
	   nm_magic_64.c \
	   get_sections.c \
	   nm_sym.c

INCLUDES = -I ../libft/includes/
LIBS = -L ../libft/ -lft
OBJS = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS)))

all: $(NAME) $(LIBS)

$(NAME): $(OBJS)
	$(CC) $(CFLAG) -o $@ $(OBJS) $(LIBS)

$(LIBS):
	@make -C ../libft/

$(OBJS): | $(OBJDIR)

$(OBJDIR)%.o : %.c $(HEADER)
	$(CC) $(FLAG) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then \
		mkdir $(OBJDIR);\
		fi

clean:
	@make clean -C ../libft
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

proper: all clean

re: fclean all
