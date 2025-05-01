# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yulpark <yulpark@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 23:59:08 by yulpark           #+#    #+#              #
#    Updated: 2025/05/02 00:54:24 by yulpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

CFLAGS = -Wall -Werror -Wextra -g -pthread

INCLUDE = includes
HEADER = $(INCLUDE)/philo.h

SRCS_DIR = srcs
SRCS = $(SRCS)/main.c \
		$(SRCS)/handle_error.c \
		$(SRCS)/handle_input.c \

OBJS_DIR = objs
OBJS = $(patsubst $(SCRS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDE) -o $(NAME)
	@echo "\n$(GREEN)philo  ✅$(RESET)\n"

$(OBJS_DIR)/%.o: $(SCRS_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(GREEN)Compiling: $< into $@$(RESET)"

clean:
	@$(MAKE) --no-print-directory clean -C 
	@if [ -d $(OBJS_DIR) ]; then \
		echo "$(YELLOW)Object files have been removed   ✅$(RESET)"; \
	fi
	@rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) --no-print-directory fclean -C
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable file has been removed ✅$(RESET)"

re: fclean all
	@echo "$(GREEN)Rebuild complete! All files cleaned and recompiled ✅$(RESET)\n"
.PHONY: all clean fclean re