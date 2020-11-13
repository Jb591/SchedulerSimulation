all: FCFS.o HRRN.o RR.o SRTF.o main.o
	g++ FCFS.o HRRN.o RR.o SRTF.o main.o -o outputFile 

FCFS.o: FCFS.h FCFS.cpp
	g++ -c FCFS.cpp

HRRN.o: HRRN.h HRRN.cpp
	g++ -c HRRN.cpp

RR.o: RR.h RR.cpp
	g++ -c RR.cpp

SRTF.o: SRTF.h SRTF.cpp
	g++ -c SRTF.cpp

main.o: main.cpp 
	g++ -c main.cpp

run:
	rm FCFS.txt RR.txt SRTF.txt HRRN.txt
	touch FCFS.txt RR.txt SRTF.txt HRRN.txt
	echo "--------------------------------------------------------FCFS-------------------------------------------------- \n\n lambda		avgTurnAround		totalthroughPut		avgNumProcessInQueue		cpuUtilization \n" >> FCFS.txt
	echo "--------------------------------------------------------RR--------------------------------------------------------------------- \n\n lambda		avgTurnAround		totalthroughPut		avgNumProcessInQueue		cpuUtilization		quantum \n" >> RR.txt
	echo "--------------------------------------------------------SRTF-------------------------------------------------- \n\n lambda		avgTurnAround		totalthroughPut		avgNumProcessInQueue		cpuUtilization \n" >> SRTF.txt
	echo "--------------------------------------------------------HRRN-------------------------------------------------- \n\n lambda		avgTurnAround		totalthroughPut		avgNumProcessInQueue		cpuUtilization \n" >> HRRN.txt
	clear
	./bashScript.sh

.PHONY: clean
clean:
	rm FCFS.txt RR.txt SRTF.txt HRRN.txt
	touch FCFS.txt RR.txt SRTF.txt HRRN.txt
	rm -f FCFS.o HRRN.o RR.o SRTF.o main.o

report:
	clear
	cat FCFS.txt RR.txt SRTF.txt HRRN.txt
