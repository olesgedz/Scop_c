# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/28 20:37:14 by olesgedz          #+#    #+#              #
#    Updated: 2021/01/06 15:43:21 by jblack-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Scop
FLAGS = -g  -Wall -Wextra -Werror
CC = clang

INCLUDES = -I include/ -I./libs/glfw/include/ -I./libs/glad/include/ -I./include/ \
 -I./libs/stb_image/ -I./libs/libft/includes/ -I./libs/libmath/includes/ -I./libs/cimgui/ #-I./libs/imgui/examples/

HEADERS_DIRECTORY = 
HEADERS_LIST = 
HEADERS = 

DIRECTORY =  $(shell pwd)
GLAD_DIRECTORY := $(DIRECTORY)/libs/glad/
GLAD := $(GLAD_DIRECTORY)libglad.a
GLFW_DIRECTORY := $(DIRECTORY)/libs/glfw/
GLFW := $(GLFW_DIRECTORY)src/libglfw3.a
LIBFT_DIRECTORY := $(DIRECTORY)/libs/libft/
LIBFT:= $(LIBFT_DIRECTORY)/libft.a
LIBMATH_DIRECTORY := $(DIRECTORY)/libs/libmath/
LIBMATH := $(LIBMATH_DIRECTORY)libmath.a
SRCS_DIRECTORY = ./src/
SRCS_LIST = main.c \
			initgl.c\
			shader.c\
			shader_set.c\
			parser.c\
			parser_load.c\
			camera.c\
			bmp.c\
			model.c\
			texture.c\
			utils.c
		

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))
MAKES = makes

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CLEAR_LINE	:= \033[2K
BEGIN_LINE	:= \033[A
COL_END		:= \033[0m
COL_RED		:= \033[1;31m
COL_GREEN	:= \033[1;32m
COL_YELLOW	:= \033[1;33m
COL_BLUE	:= \033[1;34m
COL_VIOLET	:= \033[1;35m
COL_CYAN	:= \033[1;36m
COL_WHITE	:= \033[1;37m

TOTAL_FILES := $(shell echo $(SRCS_LIST) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(DIRECTORY)/objects/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')
START_FILES = $(shell find $(DIRECTORY)/objects/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')
START_FILES_N := $(START_FILES)

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif

ifeq ($(detected_OS),Linux)
	LIBRARIES += -L./libs/libft/ -lft  -L./libs/glad/ -lglad -ldl  -lGL -L./libs/glfw/src/ -lglfw3 -L./libs/libmath/ -lmath
	LIBRARIES += -lXrandr -lXrender -lXi -lXfixes -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lm -ldl
endif
ifeq ($(detected_OS),Darwin)  
	LIBRARIES = -L./libs/libft/ -lft  -L./libs/glad/ -lglad -L./libs/glfw/src/ -lglfw3  -L./libs/libmath/ -lmath   # Mac OS X
	LIBRARIES +=  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif


.PHONY: clean fclean re

all:  $(MAKES) $(NAME) 


$(NAME): $(OBJS) $(HEADERS) $(GLFW)
	@$(CC) $(FLAGS)  $(INCLUDES) $(OBJS)  -o $(NAME) $(LIBRARIES)
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES) `%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(MAKES):
	$(MAKE) -sC $(GLAD_DIRECTORY)
	$(MAKE) -sC $(LIBFT_DIRECTORY)
	$(MAKE) -sC $(LIBMATH_DIRECTORY)


$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -MMD -c $(INCLUDES) $< -o $@
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES) `%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Compiling file [$(COL_VIOLET)$<$(COL_GREEN)].($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

$(GLFW):
	@cd libs/glfw/ && cmake . && make glfw; 

sub:
	git submodule update --init --recursive;

this:
	@rm -rf $(OBJS_DIRECTORY) && make;

clean:
	@rm -rf $(OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	$(MAKE) -sC $(LIBMATH_DIRECTORY) fclean


re:
	@$(MAKE) fclean
	@$(MAKE) all

-include $(OBJS:.o=.d)
