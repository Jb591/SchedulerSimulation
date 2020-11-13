#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "FCFS.h"
using namespace std;

FCFS::FCFS()
{
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice;
}

void FCFS::fillTheLists() // gets all the events
{
  int index = 0;
  while (index != stopCondition)
  {
    mu = 1 / averageServiceTime;
    newArrival = genExp((float)lambda);
    newService = genExp(mu);
    arrivalT.push_back(newArrival);
    serviceT.push_back(newService);
    arrivalT.sort();
    index++;
  }
}

void FCFS::initialize(int l, float tS, int stop) // initialize values
{
  stopCondition = stop;
  averageServiceTime = tS;
  lambda = l;
  clock = 0;
  turnAroundTime = 0;
  reamainingTime = 0;
  arrivalTime = 0;
  serviceTime = 0;
  finishTime = 0;
  cpuTotal = 0;
  departureCount = 0;
  remainingTime = 0;
  throughPut = 0;
  numProcessInQueue = 0;
  mu = 0;
  tally = 0;
  avgNumProcessInQueue = 0;
  cpuUtilization = 0;
  idleTime = 0;
  averageTurnAround = 0;
  totalThroughPut = 0;
  isIdle = true;
  startTime = 0;
  serviceTime = 0;
}

void FCFS::scheduleEvent()
{
  // cpu is Idle
  if (isIdle)
  {
    startTime = finishTime;
    arrivalTime = arrivalT.front();
    serviceTime = serviceT.front();
    finishTime = arrivalTime + serviceTime;
    throughPut += finishTime;
    turnAroundTime += finishTime - arrivalTime;
    clock += finishTime;
    arrivalT.pop_front();
    serviceT.pop_front();
    departureCount++;
    cpuTotal += serviceTime * finishTime;
    if (numProcessInQueue != 0)
      numProcessInQueue--;
    if (startTime > arrivalT.front())
    {
      isIdle = false;
      numProcessInQueue++;
      tally++;
    }
    else 
      idleTime += arrivalT.front() - startTime ;
  }
  else
  {
    float newArrivalTime; 
    newArrivalTime = startTime;
    finishTime = newArrivalTime + serviceTime;
    clock += arrivalTime + serviceTime;
    cpuTotal += (serviceTime * finishTime) ;
    arrivalT.pop_front();
    serviceT.pop_front();
    numProcessInQueue--;
    isIdle = true;
    departureCount++;
  }

  // cout << " startTime :  " << startTime
  //      << " arrivalT : " << arrivalTime
  //      << " serviceT : " << serviceTime
  //      << " finishTime : " << finishTime
  //      << " time : " << clock
  //      << " idleTime : " << idleTime
  //      << " isIdle : " << isIdle
  //      << "\n\n";
}

void FCFS::printReport()
{
  ofstream oFile;
  oFile.open("FCFS.txt", ios_base::app);
  oFile << setw(7) << lambda
        << setw(22) << averageTurnAround
        << setw(26) << totalThroughPut
        << setw(29) << avgNumProcessInQueue
        << setw(26) << cpuUtilization
        << "\n\n";
  oFile.close();
}

void FCFS::runSim()
{
  fillTheLists();
  while (departureCount != stopCondition)
  {
    newArrival = arrivalT.front();
    newService = serviceT.front();
    scheduleEvent();
  }
  averageTurnAround = turnAroundTime / (float)stopCondition;
  // totalThroughPut = (float)stopCondition / finishTime;
  totalThroughPut = throughPut;
  avgNumProcessInQueue = (float)tally / (float)stopCondition;
  cpuUtilization = (clock - idleTime) / clock;
  arrivalT.clear(), serviceT.clear(), readyQueueArrival.clear(), readyQeueuSerivice.clear();
  ratio.clear();
}

float FCFS::uRand()
{
  return ((float) rand() /RAND_MAX);
}

float FCFS::genExp(float lambda)
{
  float u, x;
  x = 0;
  while (x == 0)
  {
    u = uRand();
    x = (-1 / lambda) * log(u);
  }
  return x ;
}
