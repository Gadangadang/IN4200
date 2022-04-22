CC = mpicc #gcc
CFLAGS = -O2 -Wall -g -fsanitize=undefined -fsanitize=address -lm -Wextra -Wfloat-equal -Wconversion
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = parallel_main
OBJS = parallel_main.o ../utilities/functions.o ../utilities/functions_parallel.o


all: simple-jpeg $(PROJ) $(OBJS) obj-clean run


parallel_main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@.x $(LDFLAGS)



simple-jpeg:
	$(MAKE) -C ../simple-jpeg


run:
	mpirun -n 4 ./parallel_main.x 0.2 100 "mona_lisa_noisy.jpg" "mona_lisa_denoised_100.jpg"

obj-clean:
	$(RM) *.o
	$(RM) ../utilities/*.o

exec-clean:
	$(RM) *.x

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean
	

