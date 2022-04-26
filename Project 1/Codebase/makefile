
FLAGS = -Wall -fopenmp -fsanitize=undefined -fsanitize=address -lm -Wextra -Wfloat-equal -Wconversion -O2 -Wfloat-equal -g
CC := gcc-11
PROGRAMS = $(patsubst %.c,%.x,$(wildcard *.c))

PROJ = main
OBJS = main.o ../functions/PageRank_iterations.o ../functions/read_graph_from_file.o ../functions/top_n_webpages.o

all:  $(PROJ) $(OBJS) obj-clean run

main: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@.x $(LDFLAGS)

run:
	./main.x "web-Stanford_p.txt" 0.85 1e-6 10

obj-clean:
	$(RM) *.o
	$(RM) functions/*.o
	

exec-clean:
	$(RM) *.x

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean