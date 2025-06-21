NAME =  miniexec

S_SRC_BUILTIN =  bi_env.c  bi_export.c  bi_unset.c  env_utils.c  pipi.c
D_SRC_BUILTIN =  built_in/
SRC_BUILTIN =  $(addprefix $(D_SRC_BUILTIN), $(S_SRC_BUILTIN))

S_SRC_HDOC=  heredoc.c  expand_heredoc.c  heredoc_noexp.c
D_SRC_HDOC =  heredoc/
SRC_HDOC =  $(addprefix $(D_SRC_HDOC), $(S_SRC_HDOC))

S_SRC_MKTREE =  debug_base.c  in_logic_opp.c  make_base.c  make_utils2.c  make_utils.c
D_SRC_MKTREE =  make_tree/
SRC_MKTREE =  $(addprefix $(D_SRC_MKTREE), $(S_SRC_MKTREE))

S_SRC_EXEC =  $(SRC_HDOC)  $(SRC_MKTREE)  create_argv.c  exec.c  exec_cmd.c  exec_pipe_cmd.c  exec_ppl.c  exec_redir.c  find_exe.c
D_SRC_EXEC =  exec/
SRC_EXEC =  $(addprefix $(D_SRC_EXEC), $(S_SRC_EXEC))

S_SRC_UTILS =  utils.c  free.c  errors.c
D_SRC_UTILS =  utils/
SRC_UTILS =  $(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

SRC =  $(SRC_UTILS)  $(SRC_EXEC)  $(SRC_BUILTIN)  main.c  signal_handling.c
D_SRC = src/

D_INC = inc/  

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))


CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g

RM =  rm -rf

.DEFAULT_GOAL := all

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o$@ $^

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I$(D_INC) -c $< -o $@ 

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

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM) tree  heredoc

