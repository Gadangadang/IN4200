all: compile execute 

compile:
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c -g 

execute:
	./main.x "testweb2.txt" 0.85 1e-6 10