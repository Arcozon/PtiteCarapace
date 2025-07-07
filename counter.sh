#! /bin/bash
\

\
file=$1
\
total=$2
\

\
counter_file="/tmp/ms_counter"
\

\
count=$(cat "$counter_file")
\
count=$((count + 1))
\
echo "[$count/$total]: 🔧 Compiling $file"
\
echo $count > "$counter_file"
