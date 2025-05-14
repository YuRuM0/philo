# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 23:59:08 by yulpark           #+#    #+#              #
#    Updated: 2025/05/14 17:55:10 by yulpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

CFLAGS = -Wall -Werror -Wextra -g -pthread

INCLUDE = include
HEADER = $(INCLUDE)/philo.h

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/utils.c \
		$(SRCS_DIR)/input_handle.c

OBJS_DIR = objs
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDE) -o $(NAME)
	@echo "\n$(GREEN)philo  ✅$(RESET)\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(GREEN)Compiling: $< into $@$(RESET)"

clean:
	@if [ -d $(OBJS_DIR) ]; then \
		echo "$(YELLOW)Object files have been removed   ✅$(RESET)"; \
	fi
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable file has been removed ✅$(RESET)"

re: fclean all
	@echo "$(GREEN)Rebuild complete! All files cleaned and recompiled ✅$(RESET)\n"
.PHONY: all clean fclean re