##
## EPITECH PROJECT, 2023
## raytracer
## File description:
## Makefile for raytracer
##

NAME 		=  	Projet

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	COMPILER 	= 	clang++ -std=c++17
else ifeq ($(UNAME_S),Linux)
    COMPILER	=	g++
else
    $(error "Système d'exploitation non supporté")
endif

SRC 		=	src/main.cpp						\
				src/class/Socket.cpp				\
				src/class/MyOauth.cpp				\
				src/class/Environnement.cpp			\
				src/class/Token.cpp 				\

OBJ			=	$(SRC:.cpp=.o)

INCLUDE		=	-I ./includes/ -I ./includes/**/ -I ./includes/class/

CXX_FLAGS 	= 	-Wall -Wextra

LIBS		=	-lcurl -loauth

TOTAL_FILES = 	$(words $(SRC))

counter 	=	0

all:		$(NAME)

COMPLETE_TEXT:
			@$(ECHO) $(BOLD) $(BLUE)"BUILD COMPELTED 🏗️"

CLEAN_TEXT:
			@$(ECHO) $(BOLD) $(BLUE)"CLEANING 🧹"

$(NAME): 	$(OBJ)
			@$(COMPILER) -o $(NAME) $(OBJ) $(CXX_FLAGS) $(INCLUDE) $(LIBS)
			@make -s COMPLETE_TEXT

%.o: %.cpp
			$(eval counter=$(shell echo $$(($(counter)+1))))
			$(eval percentage=$(shell echo $$((($(counter) * 100) /\
			$(TOTAL_FILES)))))
			@printf "$(PYELLOW)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)" "$(subst $(shell pwd)/,,$<)"
			@$(COMPILER) -c $(CXX_FLAGS) $(INCLUDE) $< -o $@
			@printf "\r$(PGREEN)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)\n" "$(subst $(shell pwd)/,,$<)"

clean:
			@make -s CLEAN_TEXT
			@rm -f $(OBJ)

fclean:		clean
			@rm -f $(NAME)

re:			fclean	all

debug:		CXX_FLAGS += -g3 -ggdb
debug:		re
			@printf "$(PYELLOW)$(PBOLD) ⚠ Debug mode ON$(PRESET)\n"
			@printf "\033[1m\033[37mflags: $(CXX_FLAGS)\033[0m\n\n"

ECHO    		=       /bin/echo -e
DEFAULT 		=       "\033[00m"

DEFAULT 		=       "\e[0m"
BOLD    		=       "\e[1m"
DIM     		=       "\e[2m"
UNDLN   		=       "\e[4m"
SHINE   		=       "\e[5;37m"
RODE    		=       "\e[9;37m"

BLACK   		=       "\e[30m"
RED     		=       "\e[31m"
GREEN   		=       "\e[32m"
YELLOW  		=       "\e[33m"
BLUE    		=       "\e[34m"
MAGEN   		=       "\e[35m"
CYAN    		=       "\e[36m"
WHITE   		=       "\e[1;37m"

LIGHT_RED       =       "\e[91m"
LIGHT_GREEN     =       "\e[92m"
LIGHT_YELLOW    =       "\e[93m"
LIGHT_BLUE      =       "\e[94m"
LIGHT_MAGEN     =       "\e[95m"
LIGHT_CYAN      =       "\e[96m"

PGREEN = \033[32m
PYELLOW = \033[33m
PRESET = \033[0m
PBOLD = \033[1m
