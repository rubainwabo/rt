# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/16 16:11:42 by krutten           #+#    #+#              #
#    Updated: 2019/12/14 15:02:56 by rkamegne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: fclean clean all re

NAME = rt

PARSER = parse.c object_utils.c parse_objects.c manage_object.c exit_protocol.c

RENDER = sphere.c cone.c cylinder.c cap.c mat3_scale.c reflect.c ft_thread.c utils.c\
		ray_utils.c main.c lighting.c event.c plane.c initialise.c colouring.c texture.c
PATH_P = parser/
SRC_NAME = $(addprefix $(PATH_P), $(PARSER))
PATH_R = render/
SRC_NAME += $(addprefix $(PATH_R), $(RENDER))

SRC_PATH = src/
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

FLAGS = -Wall -Wextra -Werror -Ofast

HEADER = ./header
HEAD_PATH = header/rtv1.h

MLX_PATH = includes/minilibx_macos/
MLX = $(addprefix $(MLX_PATH), libmlx.a)

LIBFT_PATH = includes/libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

FRAMEWORKS = -framework OpenGl -framework Appkit

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ)
	@gcc $(FLAGS) -o $@ $(OBJ) -L $(MLX_PATH) -lmlx -L $(LIBFT_PATH) -lft $(FRAMEWORKS)
	@echo "\n\033[1;32m---------->[RT IS READY]<----------- \033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD_PATH)
	@mkdir -p obj/render/
	@mkdir -p obj/parser/
	gcc $(FLAGS) -o $@ -c $< -I $(HEADER)

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "\n\033[1;31m---------->[.O REMOVED]<----------- \033[0m"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "\n\033[1;31m----------->[RTV1 REMOVED]<-------- \033[0m"

re: fclean all
