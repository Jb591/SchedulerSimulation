I have a makefile with the following instructions :

make -> makes the files
make clean -> removes all of the Files and replaces .txt files
make run -> runs the program 
make report -> shows the data collected 

** first run make clean to clear it up just in case. ** 

HRRN, when passing in a lot of processes, it will take a long time, when i run 1000 its fine but 10000
will take a long time, but will finish eventually

When trying to run it in the school terminal, the report came out buggy, so if this does happen
the only way is to look at each individual txt file. List 
FCFS.txt     HRRN.txt       RR.txt        SRTF.txt

RR will get the processes and run each process one by one, if the service time of the process reaches 
0, depending on the quantum, will process it out, else will reschedule it back into the Queue

FCFS will get the processes and run the first process and then run the next process, but if the cpu
is busy, will store it into a queue that will allow it to be next depending on when it was put inside

HRRN will get the processes and run each process one by one, if the cpu is busy will push it into 
a queue that will change depending on an ratio, the ratio will determine who's been there the longest 
thus giving it a higher priority and pushing it to the front of the queue

SRTF will get the processes and run each process one by one, when the next is schedule, the cpu will 
be interrupted and determine which has the shortest remaining time. whichever has the shortest remaining
time will be switched with the current process