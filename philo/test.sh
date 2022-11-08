# gcc -Wall -Wextra -Werror -fsanitize=thread *.c -o philo
# gcc -Wall -Wextra -Werror -pthread *.c -o philo
# gcc -Wall -Wextra -Werror -fsanitize=thread -pthread *.c -o philo
# gcc -Wall -Wextra -Werror *.c -o philo

# no one died
# ./philo 5 800 200 200
# ./philo 4 410 200 200
# all full
./philo 5 800 200 200 7
# one died
# ./philo 1 800 200 200
# ./philo 4 310 200 100
# ./philo 21 290 100 100
# with zero
# ./philo 05 0800 0200 0200 007
# leaks
# leaks --atExit -- ./philo 5 800 200 200
# leaks --atExit -- ./philo 4 410 200 200
# leaks --atExit -- ./philo 5 800 200 200 7
# leaks --atExit -- ./philo 1 800 200 200
# leaks --atExit -- ./philo 4 310 200 100

# errors
# ./philo 5 800 200 200 7 3
# ./philo 5 8a00 200 200 7
# ./philo 5 800 200 2001231231231123
# ./philo 205 800 200 200
# ./philo 5 8 200 200
# ./philo 5 800 20 200
# ./philo 5 800 200 20
# ./philo 5 800 200 200 0
# ./philo 0 800 200 200

# rm philo
