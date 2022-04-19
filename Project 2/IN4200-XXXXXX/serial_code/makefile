CC = mpicc #gcc
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
OBJS = serial_main.o ../utilities/functions.o 


all: simple-jpeg $(PROJ) $(OBJS) obj-clean run


serial_main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@.x $(LDFLAGS)



simple-jpeg:
	$(MAKE) -C ../simple-jpeg


run:
	mpirun -np 4 ./serial_main.x

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