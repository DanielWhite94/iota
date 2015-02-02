all:
	gcc iota.c -o iota -Wall -O3
$(OBJS):

size:
	@gcc -fpreprocessed -dD -E iota.c | tr '\n' ' ' | sed 's/[ \t]//g' | wc -c
