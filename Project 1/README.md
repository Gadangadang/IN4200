# Mandatory project 1
To run the code, simply type "make all" in the terminal, and the code will run. <\br
Beneath is what is shown in the make file. 
```
all: compile execute 

compile:
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c -g 

execute:
	./main.x "web-Stanford_p.txt" 0.85 1e-6 10
```

If using an Intel processor, it might not be neccesary to use the -11 after gcc. <\br> 
The flag "-fsanitize=address" is a compiler flag that checks for memory leaks and <\br>
buffer overflows, if nothing is wrong, it will not output anything.
