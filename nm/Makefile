
NAME = ft_nm
CC = gcc
FLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror
OBJDIR = obj/
SRCS = main.c \
	   nm.c \
	   nm_error.c \
	   parse_file.c \
	   nm_magic_64.c \
	   get_sections.c \
	   nm_sym.c \
	   add_elem.c

INCLUDES = -I ../libft/includes/
LIBS = -L ../libft/ -lft
OBJS = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS)))
EXTRA_DEPS = ../libft/libft.a Makefile

all: $(LIBS) $(NAME)

$(NAME): $(OBJS) $(EXTRA_DEPS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(LIBS):
	@make -C ../libft/

$(OBJS): | $(OBJDIR)

$(OBJDIR)%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

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
