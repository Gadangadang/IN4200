all: compile execute 

compile:
	gcc -Wall -fsanitize=address -fopenmp -o main.x main.c -g 

execute:
	./main.x "testweb.txt" 0.85 0.01 8