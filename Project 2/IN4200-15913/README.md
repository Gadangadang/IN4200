# Project 2
### Denoising image using MPI

This folder contains two folders, one for serial implementation, and one for parallel implementation. To run the code for a given implementation, move into the folder and simply write "make". This will compile the neccesary support files for the main function, and if simple jpeg is not compile, will also compile those files. To clean up the folder, simply write "make clean". <br>
<br>
Below are the result of the parallel denoising, first the noisy image to the left, and then denoising with iterations equal to 10, 100 and 1000.
<img src="./parallel_code/mona_lisa_noisy.jpg" width="230"/>
<img src="./parallel_code/mona_lisa_denoised_10.jpg" width="230"/>
<img src="./parallel_code/mona_lisa_denoised_100.jpg" width="230"/>
<img src="./parallel_code/mona_lisa_denoised_1000.jpg" width="230"/>


