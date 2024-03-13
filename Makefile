all:
	gcc -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -c src/hashtable.c -o src/hashtable.o

clean:
	rm -rf src/hashtable.o

exec:
	gcc -std=c99 -fsanitize=address -g -pedantic -Werror -Wall -Wextra -Wvla src/hashtable.c test/main.c -o src/hashtable.o
	./src/hashtable.o

exec1:
	gcc -std=c99 -pedantic -Werror -Wall -Wextra -Wvla src/hashtable.c test/main.c -o src/hashtable.o
	./src/hashtable.o

clang:
	touch test.c
	clang-format src/hashtable.c > test.c
	cat test.c > src/hashtable.c
	rm -rf test.c
	touch test.c
	clang-format src/hashtable.h > test.c
	cat test.c > src/hashtable.h
	rm -rf test.c
