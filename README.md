# Scheduler Simulation

In this project, we are going to build a discrete-time event simulator for a number of CPU schedulers on a single CPU system. The goal of this project is to compare and assess the impact of different schedulers on different performance metrics, and across multiple workloads.

## Process

The simulator needs to generate a list of processes. For each process, we need to generate its arrival time and its requested service time. We can assume that processes arrive with an average rate λ that follows a Poisson process (hence exponential inter-arrival times). The service times are generated according to an exponential distribution. We will vary λ to simulate different loads while keeping the average service time fixed. The simulator should stop after processing 10,000 processes to completion (without stopping the arrival process), then it should output the statistics (i.e., the metrics above). Events (e.g., process arrival, process completion, time-slice) that occur causes the simulator to update its current state (e.g., cpu busy/idle, number of processes in the ready queue, etc.) To keep track and process events in the right order, we keep events in a priority queue (called “Event Queue”) that describes the future events and is kept sorted by the time of each event. The simulator keeps a clock the represents the current time which takes the time of the first event in the Event Queue. Notice that when an event is processed at its assigned time, one or more future events may be added to the Event Queue. For example, when a process gets serviced by the CPU, another process can start executing (if one is waiting in the ready queue) and under FCFS, we know exactly when this process would finish (since FCFS is non-preeptive), so we can schedule a departure event in the future and place it in the event queue. Notice that time hops between events, so you would need to update your simulator clock accordingly. The simulator should take few command-line arguments. The first is to indicate the scheduler, a 1 through 4 value based on the list above. Also, it should take other arguments such as the average arrival rate, the average service time and the quantum interval (for RR). Running the simulator with no arguments, should display the parameters usage. Each scheduler would need to maintain a queue (the “Process Ready Queue”) for the ready processes that are waiting for the CPU. A scheduler will select a process to run next based on the scheduling policy. Clearly, this queue should not be confused with the Event Queue that is used to hold events to be processed in the future.

## Running

We will vary the average arrival rate, λ, of processes from 10 process per second to 30 processes per second (based on a Poisson process). The service time is chosen according to an exponential distribution with an average service time of 0.04 sec. For each value of λ, we need to compare the performance of each scheduler, based on the metrics above. It is recommended (but not required) that you write a simple batch file that would run those experiments and put the results in a file (that you can later import into a spread sheet and plot the values).This will run the simulator using FCFS (indicated by the value 1 in the first argument) for 20 different values of λ using 0.04 as the average service time and a quantum value of 0.01 (which is ignored in all algorithms, except round robin). Then, the script will move the sim.data file to a safe place. With the Round Robin algorithm, an argument is supplied to indicate the quantum used. Use 2 different values of quantum; 0.01 and 0.2. If a process finishes before its quantum expires, the CPU will schedule the next process right away.

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
