NAME =  miniexec

S_SRC_BUILTIN =  bi_env.c  bi_export.c  bi_unset.c  env_utils.c
D_SRC_BUILTIN =  built_in/
SRC_BUILTIN =  $(addprefix $(D_SRC_BUILTIN), $(S_SRC_BUILTIN))

S_SRC_ECMD =  exec_cmd.c
D_SRC_ECMD =  exec_cmd/
SRC_ECMD =  $(addprefix $(D_SRC_ECMD), $(S_SRC_ECMD))

S_SRC_ERDIR =  exec_redir.c
D_SRC_ERDIR =  exec_redir/
SRC_ERDIR =  $(addprefix $(D_SRC_ERDIR), $(S_SRC_ERDIR))

S_SRC_EXEC =  $(SRC_ERDIR)  $(SRC_ECMD)  exec.c
D_SRC_EXEC =  exec/
SRC_EXEC =  $(addprefix $(D_SRC_EXEC), $(S_SRC_EXEC))

S_SRC_UTILS =  utils.c
D_SRC_UTILS =  utils/
SRC_UTILS =  $(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

SRC =  $(SRC_UTILS)  $(SRC_EXEC)  $(SRC_BUILTIN)  main.c
D_SRC = src/

D_INC = inc/  

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))


CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g

RM =  rm -rf

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

S_TREE_SRC = make_base.c  test_exec.c  make_utils.c  debug_base.c
TREE_SRC = $(addprefix src/exec/, $(S_TREE_SRC))  src/utils/utils.c

tree:	
	$(CC) $(FLAGS) $(TREE_SRC) -I$(D_INC) -o tree

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
-include $(DEPS)

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM) tree

