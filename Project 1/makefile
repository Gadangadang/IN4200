all: compile execute 
FLAGS = -Wall -fopenmp -fsanitize=undefined -fsanitize=address -lm -Wextra -Wfloat-equal -Wconversion -O2 -Wfloat-equal -g
CC := gcc-11
PROGRAMS = $(patsubst %.c,%.x,$(wildcard *.c))
DEP = PageRank_iterations.h read_graph_from_file.h top_n_webpages.h

compile: $(PROGRAMS)

main.x: main.c $(DEP)
	$(CC) $< -o $@ $(FLAGS)

execute:
	./main.x "web-Stanford_p.txt" 0.85 1e-6 10


clean :
	rm -f *.o $(PROGRAMS)