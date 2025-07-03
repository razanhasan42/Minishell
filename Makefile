NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra


EXECUTION_DIR = execution
EXPAND_DIR = expand
MAIN_DIR = main
TOKENIZER_DIR = tokenizer
REDIRECTION_DIR = redirection
PARSE_DIR = parse
UTILS_DIR = utils

SRC = $(MAIN_DIR)/main.c $(MAIN_DIR)/execution_main.c $(MAIN_DIR)/signals.c $(MAIN_DIR)/input.c \
		$(TOKENIZER_DIR)/tokenize_utils.c $(TOKENIZER_DIR)/tokenize.c   \
		$(EXPAND_DIR)/expand.c $(EXPAND_DIR)/expand_utils.c $(EXPAND_DIR)/env.c \
		$(EXECUTION_DIR)/execution.c $(EXECUTION_DIR)/execution2.c $(EXECUTION_DIR)/exec_bulit_in_utils.c \
		$(EXECUTION_DIR)/exec_bulit_in_utils2.c $(EXECUTION_DIR)/expr.c $(EXECUTION_DIR)/built_in_export.c $(EXECUTION_DIR)/utils_free.c \
		$(EXECUTION_DIR)/child.c $(EXECUTION_DIR)/parent.c $(EXECUTION_DIR)/set_env.c $(EXECUTION_DIR)/exec_built_in.c \
		$(EXECUTION_DIR)/execution_utils.c $(EXECUTION_DIR)/execution_utils2.c $(EXECUTION_DIR)/execution_main.c \
		$(REDIRECTION_DIR)/heredoc.c $(REDIRECTION_DIR)/redirection1.c $(REDIRECTION_DIR)/heredoc_signal.c $(REDIRECTION_DIR)/handling_heredoc_fun.c   $(REDIRECTION_DIR)/heredoc_utils2.c\
		$(REDIRECTION_DIR)/heredoc_utils.c $(REDIRECTION_DIR)/heredoc_expander.c $(REDIRECTION_DIR)/redirection2.c $(REDIRECTION_DIR)/redirction_utils.c \
		$(PARSE_DIR)/parser3.c $(PARSE_DIR)/parser_pipe.c $(PARSE_DIR)/parser_pipe_utils.c $(PARSE_DIR)/parse_utils.c \
		$(UTILS_DIR)/handle_list.c $(UTILS_DIR)/qoutes.c $(UTILS_DIR)/utils.c


LIBFT = libft/libft.a

OBJS = $(SRC:.c=.o)

INCLUDE = -I include

all : $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFT) -lreadline -o $(NAME)

clean:
	@$(MAKE) clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
