# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 15:31:15 by codespace         #+#    #+#              #
#    Updated: 2025/01/07 17:38:34 by codespace        ###   ########.fr        #
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

NAME		:=	libftprintf.a

CC			:=	cc
CFLAGS		:=	-g
#-Wall -Werror -Wextra

# Directories:
SRC_DIR	:=	_src
INC_DIR	:=	_inc
OBJ_DIR	:=	_obj
DEP_DIR	:=	_dep
BIN_DIR	:=	_bin
LIB_DIR	:=	libft_srcs

# Files:
SRCS	:=	$(wildcard $(SRC_DIR)/*.c)
INCS	:=	$(wildcard $(INC_DIR)/*.h)
OBJS	:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS	:=	$(patsubst $(OBJ_DIR)/%.o, $(DEP_DIR)/%.d, $(OBJS))
LIBS	:=	$(LIB_DIR)/bin/libft.a

LIBFT	:= libft.a

-include $(wildcard $(DEPS))

# Debugging:
# $(info LIBS: $(LIBS))

# SRCS		:=	$(wildcard ./*.c)
# OBJS		:=	$(SRCS:.c=.o)
# LIBFT_DIR	:=	libft-srcs
# LIBFT		:=	$(LIBFT_DIR)/libft.a

# INCLUDES	:=	-I./includes/
# LIBSRC-PATH	:=	./libft-srcs/

# HEADER_DIR	:=	./includes
# HEADER_FLS	:=	$(wildcard ./includes/libft.h ./includes/ft_printf_lib.h)

# BONUS_SRCS	:=	$(wildcard ./_bonus/*.c)
# BONUS_OBJS	:=	$(BONUS_SRCS:.c=.o)


.PHONY: all bonus clean fclean re rebonus install_headers run_cleaned \
		clean_whitespace run_libft

TARGET ?= $(NAME)

# Automatic dependency generation
# -include $(OBJS:.o=.d)

all : $(LIBS) run_cleaned

$(LIBS):
	@echo "building libft.a"
	$(MAKE) -C $(LIB_DIR) -f Makefile-libft.mk

$(NAME): $(LIBS) $(OBJS)
	@echo "Building ft_printf.out..."
#	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) $(LIBS) -o $(BIN_DIR)/$(NAME)
	@ar -rcs $(BIN_DIR)/$(NAME) $(OBJS)
#	@rm -f $(OBJ_DIR)/*.o
	@cp $(INCS) ./
	@cp $(LIBS) ./
	@cp $(BIN_DIR)/$(NAME) ./$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) $(DEP_DIR)/%.d | $(OBJ_DIR) $(DEP_DIR)
	@echo "ft_printf Standard Object files are being Updated..."
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@


#	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
#	@$(CC) $(CFLAGS) -I$(INC_DIR) -MM $< > $@

#.SECONDARY: $(DEPS)
$(DEP_DIR)/%.d: ;
	@true

# Q: should the bonus be dependent on the main?
# A: yes to make sure everything is up to date.
bonus: $(NAME) $(BONUS_OBJS)
	@echo "Bonus Object files are being added to the Library..."
	@ar -rcs $(NAME) $(BONUS_OBJS)

install_headers:
	@if [ ! -z "$(HEADER_FLS)" ]; then \
		cp $(HEADER_FLS) ./; \
	else \
	echo "No header files found to copy."; \
	fi

#	@mkdir -p $(HEADER_DIR)
#	@cp $(HEADER_FLS) ./
#	@echo "Headers installed to $(HEADER_DIR)"

clean:
	@echo "Object files are being deleted..."
	@rm -f Makefile-cleaned.mk
	@rm -f $(OBJS) $(BONUS_OBJS)
	@rm -f $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

fclean: clean
	@echo "$(NAME) is being deleted..."
	$(MAKE) -C $(LIB_DIR) -f Makefile-libft.mk fclean
#	@if ls *.out >/dev/null 2>&1; then
#	for file in *.out; do \
#		[ -e "$$file" ] && rm -i "$$file"; \
#	done
#	fi

	@if ls *.out >/dev/null 2>&1; then \
		for file in *.out; do \
			[ -e "$$file" ] && rm -i "$$file"; \
		done; \
	fi
	@rm -f *.h
	@rm -f $(LIBFT)
	@rm -f $(BIN_DIR)/$(NAME)
	@rm -f $(NAME)

re: fclean all

rebonus: fclean bonus

run_libft:
	$(MAKE) -C $(LIB_DIR) -f Makefile-libft.mk

run_cleaned:
	$(MAKE) clean_whitespace
	$(MAKE) -f Makefile-cleaned.mk $(TARGET)
	@rm -f Makefile-cleaned.mk

clean_whitespace:
	@sed -e 's/[ \t]*=[ \t]*/=/g' \
		 -e 's/[ \t]*:=[ \t]*/:=/g' \
		 $(firstword $(MAKEFILE_LIST)) > Makefile-cleaned.mk
	@echo "Processed Makefile written to Makefile-cleaned.mk"
