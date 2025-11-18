# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 22:07:00 by dancel            #+#    #+#              #
#    Updated: 2025/03/21 16:39:51 by chajeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables de Compilation
# ============================
CUB3D          = cub3D
CUB3D_BONUS    = cub3D_bonus
CC             = cc
CFLAGS         = -Wall -Werror -Wextra -g3

# Fichiers et bibliothèques
# ============================
LFT			= ./lib/libft/libft.a
LMLX		= ./lib/libmlx42.a
LIBFT		= ./lib/libft
LIBMLX		= ./lib/MLX42
MAKE_LIBFT	= ${MAKE} --no-print-directory -C ${LIBFT}
MAKE_LIBMLX	= @cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j4
INCLUDES	= -I ./include -I $(LIBMLX)/include -Ilib/libft
LIBS		= ${LFT} ${LMLX} -ldl -lglfw -pthread -lm

# Fichiers source
# ============================
SRC_FILES   = sources/display.c sources/init_mlx.c sources/parsing.c sources/utils_bonus.c sources/ray_utils.c sources/hooker.c sources/main.c sources/ray_cast.c sources/utils.c
SRCB_FILES   = sources/display.c sources/init_mlx.c sources/parsing.c sources/utils_bonus.c sources/ray_utils.c sources/hooker.c sources/main_bonus.c sources/ray_cast.c sources/utils.c
OBJ_FILES   = $(SRC_FILES:sources/%.c=objects/%.o)
OBJB_FILES   = $(SRCB_FILES:sources/%.c=objects/%.o)

# Cible principale
# ============================

all: $(CUB3D)

bonus: $(CUB3D_BONUS)

$(LFT): 
	@$(MAKE_LIBFT)

$(LMLX):
	@$(MAKE_LIBMLX) --no-print-directory
	@mv $(LIBMLX)/build/libmlx42.a ./lib/

$(CUB3D): $(LFT) $(LMLX) $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(CUB3D) $(OBJ_FILES) $(LIBS) $(INCLUDES)
	
$(CUB3D_BONUS): $(LFT) $(LMLX) $(OBJB_FILES)
	@$(CC) $(CFLAGS) -o $(CUB3D_BONUS) $(OBJB_FILES) $(LIBS) $(INCLUDES)

objects/%.o: sources/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBMLX):
	@make -s -C lib/minilibx-linux/

$(LIBFT):
	@make -s -C lib/libft

# Nettoyage des fichiers
# ============================
clean:
	@make clean -s -C lib/libft
	@rm -rf $(LIBMLX)/build
	rm -rf objects

fclean: clean
	@make fclean -s -C lib/libft
	@rm lib/libmlx42.a
	@rm -f cub3D
	@rm -f cub3D_bonus


# Rebuild
# ============================
re: fclean all

# Cibles "fantômes"
# ============================
.PHONY: all clean fclean re libmlx bonus

