# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 18:23:24 by rkamegne          #+#    #+#              #
#    Updated: 2019/11/22 19:08:22 by rkamegne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_isalpha.c ft_isalnum.c ft_isprint.c ft_isdigit.c ft_isascii.c ft_bzero.c ft_strcat.c ft_strchr.c ft_strcmp.c\
	ft_strcpy.c ft_strdup.c ft_strlen.c ft_strncat.c ft_strncpy.c ft_strncmp.c ft_strrchr.c ft_strnstr.c ft_strstr.c ft_tolower.c\
	ft_toupper.c ft_memcpy.c ft_memcmp.c ft_memchr.c ft_memccpy.c ft_memset.c ft_strlcat.c ft_memmove.c ft_memdel.c ft_memalloc.c\
	ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c\
	ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putendl_fd.c\
	ft_putstr_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_cisspace.c\
	ft_cisupper.c ft_replace.c ft_count_words.c ft_strlen_err.c ft_sqrt.c get_next_line.c ft_strdup_at.c ft_atoi_base.c ft_ispace.c ft_atof.c vec3/vec3_init.c vec3/vec3_add.c\
	vec3/vec3_cross.c vec3/vec3_scale.c vec3/vec3_dot.c vec3/matrix_ops.c ft_error.c\
	vec3/rot_matrix.c ft_max.c ft_abs.c ft_min.c

OBJ = $(SRC:.c=.o)

HEADERS=libft.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@ar -rcs $(NAME) $(OBJ)

clean:
	@/bin/rm -f $(OBJ)

fclean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY : fclean clean all re
