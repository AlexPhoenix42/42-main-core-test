# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile-libft.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 05:56:55 by codespace         #+#    #+#              #
#    Updated: 2025/01/07 17:38:53 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Remember that "make" may fail because of whitespace around ":=" or "="
# https://openjdk.org/groups/build/doc/code-conventions.html
# https://www.gnu.org/software/make/manual/make.html

# Mac C man 3 page: https://manp.gs/mac/3/
# https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/system.3.html

# 42 Holygraph:
# https://github.com/akaylee/42-holygraph
# https://drive.google.com/file/d/1hAfM56LkN2UYlraN56vDx9dsMf-dB49L/view (pdf)

# Library name:
NAME		:=	libft.a

# Compiler and flags:
CC			:=	cc
CFLAGS		:= -g
#-Wall -Wextra -Werror

# Directories:rm
SRC_DIR	:=	src
INC_DIR	:=	inc
OBJ_DIR	:=	obj
DEP_DIR	:=	dep
BIN_DIR	:=	bin

# Files:
SRCS	:=	$(wildcard $(SRC_DIR)/*.c)
INCS	:=	$(wildcard $(INC_DIR)/*.h)
OBJS	:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS	:=	$(patsubst $(OBJ_DIR)/%.o, $(DEP_DIR)/%.d, $(OBJS))

#OBJS	:=	$(SRCS:.c=.o)
#DEPS	:=	$(SRCS:.c=.d)

# Debugging:
# $(info SRCS: $(SRCS))
# $(info INCS: $(INCS))
# $(info OBJS: $(OBJS))
# $(info DEPS: $(DEPS))
# $(info INC_DIR: $(INC_DIR))

# Automatic dependency generation
# -include $(DEPS)
-include $(wildcard $(DEPS))
#-include $(OBJS:.o=.d)

# INCLUDES	:= -I../includes/

#HEADER_DIR	:=	../includes
#HEADER_FLS	:=	$(wildcard ../includes/libft.h)

#BONUS_SRCS	:=	$(wildcard ./_bonus/*.c)
#BONUS_OBJS	:=	$(BONUS_SRCS:.c=.o)

.PHONY: all bonus clean fclean re rebonus install_headers run_cleaned \
		clean_whitespace print_dep

TARGET ?= $(NAME)

all : run_cleaned
#$(NAME)
#run_cleaned

$(NAME): $(OBJS)
	@echo "Library is being Updated..."
	@ar -rcs $(BIN_DIR)/$(NAME) $(OBJS)
#	@rm -f $(OBJ_DIR)/*.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) $(DEP_DIR)/%.d | $(OBJ_DIR) $(DEP_DIR)
	@echo "Standard Object files are being Updated..."
	@echo "Compiling $< to $@"
	@echo "Using include path: $(INC_DIR)"
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@


#.SECONDARY: $(DEPS)
$(DEP_DIR)/%.d: ;
	@true

print_dep:
	@echo "DEPS = " $(DEPS)

#	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

#	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
#	@$(CC) $(CFLAGS) $(INCLUDES) -MM $< > $(@:.o=.d)

# $(DEP_DIR)/%.d: $(SRC_DIR)/%.c | $(DEP_DIR)
# 	$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -MP -MF $@ -c $<

# Q: should the bonus be dependent on the main?
# A: yes to make sure everything is up to date.
bonus: $(NAME) $(BONUS_OBJS)
	@echo "Bonus Object files are being added to the Library..."
	@ar -rcs $(NAME) $(BONUS_OBJS)

install_headers:
	@mkdir -p $(HEADER_DIR)
	@cp $(HEADER_FLS) $(HEADER_DIR)
	@echo "Headers installed to $(HEADER_DIR)"

clean:
	@echo "Object files are being deleted..."
	@rm -f Makefile-cleaned.mk
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(OBJS) $(BONUS_OBJS)
	@rm -f $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

fclean: clean
	@echo "$(NAME) is being deleted..."
	@rm -f $(BIN_DIR)/$(NAME)

re: fclean all

rebonus: fclean bonus

run_cleaned:
	$(MAKE) -f Makefile-libft.mk clean_whitespace
	$(MAKE) -f Makefile-libft-cleaned.mk $(TARGET)
#	$(MAKE) -f Makefile-libft-cleaned.mk clean
	@rm -f Makefile-libft-cleaned.mk

clean_whitespace:
	@sed -e 's/[ \t]*=[ \t]*/=/g' \
		 -e 's/[ \t]*:=[ \t]*/:=/g' \
		 $(firstword $(MAKEFILE_LIST)) > Makefile-libft-cleaned.mk
	@echo "Processed Makefile written to Makefile-libft-cleaned.mk"
