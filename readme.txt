/* How to Run The Code */

Please make sure that you have follow all instruction mentioned 
in part1 of the assignment like compiling prog1.c etc .


Code for part1 is saved as 'first.cpp'

1. To run the code for the first question :
   a). $ make obj-intel64/first.so 

       To make the trace the file you need to provide the program name 
       for example : prog4 and number of threads as 8,as given below :
   b). $ ../../../pin -t obj-intel64/first.so -- ./prog4 8
       
       It will generate a trace named as  'trace.out' .


Code for part2 is saved as 'second.cpp'
2. To run the code for the second part :
   a). compiled it as :
	$ g++ second.cpp -o second
  
   b). Run it for a particular trace file generated in step 1 as:
        $ ./second trace.out

   It will generate a plotData.csv ,which is further used for 
   plotting the CDF .

       

Code for part3 is saved as 'third.cpp'

3.To run the code for the third part :
   a). compiled it as:
	$ g++ third.cpp -o third 

   b). Run it for a particular trace file generated in step1 as :
	$ ./third trace.out

       This will generate an another trace file as 'filter_trace.out'

   c). Pass this 'filter_trace.out' to part2 program as :
	$ ./second filter_trace.out
  
    It will generate some statistics of cache_hit ,cache_miss and 
    a 'plotData.csv' ,which is further used for plotting the CDF.

Code for part4 is saved as fourth.cpp

4. To run the code for the fourth part :
   a). compiled it as :
     $ g++ fourth.cpp -o fourth
 
   b). Run it for a particular trace file generated in step 1 as:
     $ ./fourth trace.out

