#! /usr/bin/minishell
# socket --creat -p 4563
ls
norminette
find . -name '*.c' | xargs cat | grep malloc -A2 -B2

