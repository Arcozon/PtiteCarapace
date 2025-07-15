#! /usr/bin/minishell
# socket --creat -p 4563
ls
norminette
find . -name '*.c' | xargs cat | grep ms -A2 -B2
echo "bonjour $USER" | xargs toilet -f bigmono12 --gay 

