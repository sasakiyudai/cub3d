# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 14:46:07 by syudai            #+#    #+#              #
#    Updated: 2020/12/19 21:13:01 by syudai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c utils.c utilsb.c utilsc.c seta.c setb.c \
		setc.c color.c error.c check.c load.c read.c \
		calc.c calcb.c g_save.c update.c utilsd.c \
		adjust.c
OBJS = $(SRCS:.c=.o)
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
LIBS = -lXext -lX11
else
LIBS = libmlx.dylib -framework OpenGL -framework AppKit
endif
NAME = cub3D
CC = gcc -Wall -Wextra -Werror -g
RM = rm -f
ifeq ($(UNAME), Linux)
$(NAME): $(OBJS)
	$(MAKE) -C ./minilibx-linux
	cp ./minilibx-linux/libmlx_Linux.a .
	$(CC) $(OBJS) -L. -L.minilibx-linux -lmlx_Linux $(LIBS) -lm -o $(NAME)
all: $(NAME)
clean:
	$(MAKE) clean -C ./minilibx-linux
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) clean -C ./minilibx_mms_20200219
	$(RM) $(NAME) libmlx_Linux.a img.bmp
re: fclean all
.PHONY: all clean fclean re .c.o
else
$(NAME): $(OBJS)
	$(MAKE) -C ./minilibx_mms_20200219
	cp ./minilibx_mms_20200219/libmlx.dylib ./
	$(CC) $(OBJS) $(LIBS) -lm -o $(NAME)
all: $(NAME)
clean:
	$(MAKE) clean -C ./minilibx_mms_20200219
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) clean -C ./minilibx_mms_20200219
	$(RM) $(NAME) libmlx.dylib img.bmp
re: fclean all
endif