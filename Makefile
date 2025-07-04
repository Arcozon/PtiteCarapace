# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 16:22:31 by malfwa            #+#    #+#              #
#    Updated: 2025/07/04 12:54:37 by gaeudes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  minishell

include src/printf/libft/libft_vars.mk
include src/printf/printf_vars.mk

S_SRC_BUILTIN =  bi_cd.c  bi_echo.c  bi_clear.c bi_env.c  bi_export.c  bi_pwd.c  bi_unset.c  bi_exit.c  env_utils.c bi_alias.c
D_SRC_BUILTIN =  built_in/
SRC_BUILTIN =  $(addprefix $(D_SRC_BUILTIN), $(S_SRC_BUILTIN))

S_SRC_HDOC=  heredoc.c  expand_heredoc.c  heredoc_noexp.c
D_SRC_HDOC =  heredoc/
SRC_HDOC =  $(addprefix $(D_SRC_HDOC), $(S_SRC_HDOC))

S_SRC_MKTREE =  debug_base.c  in_logic_opp.c  make_base.c  make_utils2.c  make_utils.c
D_SRC_MKTREE =  make_tree/
SRC_MKTREE =  $(addprefix $(D_SRC_MKTREE), $(S_SRC_MKTREE))

S_SRC_EXEC =  $(SRC_HDOC)  $(SRC_MKTREE)  create_argv.c  exec.c  exec_simple_cmd.c  exec_pipe_cmd.c  exec_opp.c  exec_ppl.c  exec_redir.c  find_exe.c
D_SRC_EXEC =  exec/
SRC_EXEC =  $(addprefix $(D_SRC_EXEC), $(S_SRC_EXEC))

S_SRC_UTILS =  utils.c  free.c  errors.c
D_SRC_UTILS =  utils/
SRC_UTILS =  $(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

SRC =  $(SRC_UTILS)  $(SRC_EXEC)  $(SRC_BUILTIN)  signal_handling.c  ad_main.c  arco_prompt.c  arco_get_next_line.c
D_SRC = src/

SRC +=	gnl/get_next_line_utils.c\
		gnl/get_next_line.c\
		gnl/get_next_null.c\
		gnl/gnl.c\
		gnl/gnl_utils.c\
		gnl/utils.c

SRC	+=	history/manage_history.c

SRC	+=	signal/handler.c

SRC	+=	ad_utils/utils.c\
		ad_utils/sep_func.c

SRC	+=	parsing/readline.c\
		parsing/hash.c\
		parsing/tilde.c\
		parsing/manage_rcfile.c\
		parsing/parse_rc.c\
		parsing/snippet.c\
		parsing/word_len.c\
		parsing/hash_utils.c\
		parsing/syntaxe/check_syntaxe.c\
		parsing/syntaxe/alias.c\
		parsing/wildcard/wildcard.c\
		parsing/wildcard/manage_files.c

SRC +=	$(addprefix printf/srcs/, $(SRC_PRINTF))
SRC +=	$(addprefix printf/libft/, $(SRC_LIBFT))

D_INC = inc/ src/printf/includes/ src/printf/libft/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

D_LIBPRINTF = $(D_SRC)printf/
LIBPRINTF	=	$(D_SRC)printf/libftprintf.a

CC =  cc
FLAGS =  -Wall -Wextra -Werror -MMD -g
F_INC =  $(addprefix -I, $(D_INC))
F_LIB =  -lreadline -lncurses -L$(D_LIBPRINTF) $(LIBPRINTF) 

RM =  rm -rf

TOTAL := $(shell echo $(SRC) | wc -w) 

MINISHELLRC = .minishellrc

.DEFAULT_GOAL := all

all:	$(MINISHELLRC) counter.sh set_counter $(NAME)
	@rm -rf /tmp/ms_counter

$(NAME):	$(OBJ) 
	@$(CC) -o $@ $^ $(F_LIB)
	@echo "\033[1;32m$@ linked!\033[0m"

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	@./counter.sh $< $(TOTAL)
	@$(CC) $(FLAGS) $(F_INC) -c $< -o $@ 

clean:
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)


$(MINISHELLRC):
	@echo "❌ Missing $@. Creating...";
	@echo "alias l='ls -l'" >> $@;
	@echo "alias la='ls -la'" >> $@;
	@echo "✅ $@ created";


.PHONY: re fclean clean all set_counter


set_counter:
	@count=$$( $(MAKE) -n $(NAME) | grep "Wall" | wc -l );\
		printf "$$(($(TOTAL) - $$count))" > /tmp/ms_counter

counter.sh:
	@printf '#! /bin/bash\n\
\n\
file=$$1\n\
total=$$2\n\
\n\
counter_file="/tmp/ms_counter"\n\
\n\
count=$$(cat "$$counter_file")\n\
count=$$((count + 1))\n\
echo "[$$count/$$total]: 🔧 Compiling $$file"\n\
echo $$count > "$$counter_file"\n' > counter.sh
	chmod +x counter.sh
