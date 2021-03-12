#!/bin/bash
# flag="-Werror -Wall -Wextra"
# leaks="-fsanitize=address -g3"
# libft="-L../../../libft_extended/ -lftx -I-L../../../libft_extended/libft"
lib="-lpthread"
gcc $1 -L../../../libft_extended/ $lib $flag $leaks
if [ $? = 0 ]
then
    echo "$1 compilé sous a.out :fire: nous lançons l'éxécutable : "
    ./a.out
else
    echo le compilation de $1 a échouée :monkey_face:
fi