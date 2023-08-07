all:
	gcc -o programaTrab *.c -lm
run:
	./programaTrab
valgrind:
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./programaTrab
clean:
	rm programaTrab