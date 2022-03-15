all: compile execute 

compile:
	gcc -Wall -fsanitize=address -fopenmp -o main.x main.c -g 

execute:
	./main.x "web-Stanford_p.txt" 1 1e-6 10