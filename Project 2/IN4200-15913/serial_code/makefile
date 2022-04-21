CC = gcc
CFLAGS = -O2 -Wall -g -fsanitize=undefined -fsanitize=address
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
OBJS = serial_main.o ../utilities/functions.o 


all: simple-jpeg $(PROJ) $(OBJS) obj-clean run


serial_main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@.x $(LDFLAGS)



simple-jpeg:
	$(MAKE) -C ../simple-jpeg


run:
	./serial_main.x 0.2 100 "mona_lisa_noisy.jpg" "mona_lisa_denoised.jpg"

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