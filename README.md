# Scheduler Simulation

This project simulates the different shceduler types such as Round Robin, First Come First Serve, Shortest Remaining Time First and Highest Response Ratio. There is a script file that helps with the simulation by chnaging the value of lambda, defining what kind of schduler is going to be used, the average service time and the quantum value.

## Round Robin

Round Robin will get the processes and run each process one by one, if the service time of the process reaches 0, depending on the quantum, will process it out, else will reschedule it back into the Queue

## First Come First Serve

Frist Come First Serve will get the processes and run the first process and then run the next process, but if the cpu is busy, will store it into a queue that will allow it to be next depending on when it was put inside

## Highest Response Ratio

Highest Response Ratio will get the processes and run each process one by one, if the cpu is busy will push it into a queue that will change depending on an ratio, the ratio will determine who's been there the longest thus giving it a higher priority and pushing it to the front of the queue

## Shortest Remaining Time First

Shortest Remaining Time First will get the processes and run each process one by one, when the next is schedule, the cpu will be interrupted and determine which has the shortest remaining time. whichever has the shortest remaining time will be switched with the current process

## Makefile

I have included a makefile with the following instructions :

`make`

`make clean`

`make run`

`make report`

* make compiles all of the code
* make clean removes all of the files and replaces all .txt files
* make run runs the program
* make report shows all of the data collected

### Installation

Clone this repo for easy access

`git clone https://github.com/Jb591/SchedulerSimulation.git`
