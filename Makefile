NAME =  minishell

S_SRC_BUILTIN =  bi_cd.c  bi_echo.c  bi_env.c  bi_export.c  bi_pwd.c  bi_unset.c  env_utils.c  pipi.c
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

SRC =  $(SRC_UTILS)  $(SRC_EXEC)  $(SRC_BUILTIN)  main.c  signal_handling.c  ad_main.c
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

SRC	+=	prompt/generate_prompt.c\
		prompt/write_prompt.c

D_INC = inc/ src/printf/includes/ src/printf/libft/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

D_LIBPRINTF = $(D_SRC)printf/
LIBPRINTF	=	$(D_SRC)/printf/libftprintf.a

CC =  cc
FLAGS =  -Wall -Wextra -Werror -MMD -g
F_INC =  $(addprefix -I, $(D_INC))
F_LIB =  -lreadline -lncurses -L$(D_LIBPRINTF) $(LIBPRINTF) 

RM =  rm -rf

.DEFAULT_GOAL := all

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o$@ $^ 

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(F_INC) -c $< -o $@ 

$(LIBPRINTF):
	make bonus -C srcs/printf

clean:
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

S_TREE_SRC = make_base.c  test_exec.c  make_utils.c  debug_base.c  in_logic_opp.c  make_utils2.c
TREE_SRC = $(addprefix src/exec/make_tree/, $(S_TREE_SRC))  src/utils/utils.c  src/utils/free.c

tree:	
	$(CC) $(FLAGS) $(TREE_SRC) -I$(D_INC) -o $@

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM) tree

