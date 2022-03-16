# Mandatory project 1
To run the code, simply type "make all" in the terminal, and the code will run. <br>
Beneath is what is shown in the make file. 
```
all: compile execute 

compile:
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c -g 

execute:
	./main.x "web-Stanford_p.txt" 0.85 1e-6 10
```

If using an Intel processor, it might not be neccesary to use the -11 after gcc. <br> 
The flag "-fsanitize=address" is a compiler flag that checks for memory leaks and <br>
buffer overflows, if nothing is wrong, it will not output anything. <br>
<br>
The project contains 4 different c files. 
* read_graph_from_file.c reads the file you choose in command line, and creates <br>
a sparse matrix using the CRS standard for the hyperlinks.
* PageRank_iterations.c will by iteration calculate the score of all the webpages, <br>
also handling dangling webpages.
* top_n_webpages.c sorts the scores of the webpages and outputs the top n that you choose.
* main.c initializes the neccesary pointers, and runs the above mentioned codes.
<br>
<br>
Below are the output of the top 10 webpages, using a damping of 0.85 and a error threshold of 1e-6:

NR of dangling webpages: 172 <br>

Last iteration: 41, Max error: 0.000001, epsilon: 0.000001 <br>
Time page rank is 1.437890E+00 sec <br>
<br>
------------------------------------------ <br>
             Top 10 webpages              <br>
Rank: 1  | Score: 0.011294 | Webpage nr: 89072 <br>
Rank: 2  | Score: 0.009260 | Webpage nr: 226410 <br>
Rank: 3  | Score: 0.008291 | Webpage nr: 241453 <br>
Rank: 4  | Score: 0.003021 | Webpage nr: 262859 <br>
Rank: 5  | Score: 0.002999 | Webpage nr: 134831 <br>
Rank: 6  | Score: 0.002570 | Webpage nr: 234703 <br>
Rank: 7  | Score: 0.002452 | Webpage nr: 136820 <br>
Rank: 8  | Score: 0.002429 | Webpage nr: 68888 <br>
Rank: 9  | Score: 0.002389 | Webpage nr: 105606 <br>
Rank: 10  | Score: 0.002362 | Webpage nr: 69357 <br>
Time total is 8.324689E+00 min <br>

