all: compile execute 

compile:
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c -g 

execute:
	./main.x "web-Stanford_p.txt" 0.85 1e-6 10