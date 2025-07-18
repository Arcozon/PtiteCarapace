#! /usr/bin/minishell
# exec -c "/usr/bin/bash" {"minishell",NULL}
ls
norminette
find . -name '*.c' | xargs cat | grep ms -A2 -B2
echo "bonjour $USER" | xargs toilet -f bigmono12 --gay 

