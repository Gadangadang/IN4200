# Project 2
### Denoising image using MPI

This folder contains two folders, one for serial implementation, <br> 
and one for parallel implementation. To run the code for a given implementation,<br> 
move into the folder and simply write "make". This will compile the neccesary <br> 
support files for the main function, and if simple jpeg is not compile, will also <br>  
compile those files. To clean up the folder, simply write "make clean". <br>
<br>
Below are the result of the parallel denoising, first the noisy image to the left,<br> 
and then denoising with iterations equal to 10, 100 and 1000.

| Noisy and 100 iterations            |  10 and 1000 iterations |
:-------------------------:|:-------------------------:
<img src="./parallel_code/mona_lisa_noisy.jpg" width="250">  | <img src="./parallel_code/mona_lisa_denoised_10.jpg" width="250">
 <img src="./parallel_code/mona_lisa_denoised_100.jpg" width="250"> |   <img src="./parallel_code/mona_lisa_denoised_1000.jpg" width="250"> 

