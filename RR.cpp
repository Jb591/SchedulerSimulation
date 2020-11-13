#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "RR.h"
using namespace std;

RR::RR()
{
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice, marked;
}

void RR::initialize(int l, float tS, float q, int stop)
{
  stopCondition = stop;
  averageServiceTime = tS;
  lambda = l;
  quantum = q;
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

void RR::fillTheLists()
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
    totalArrival += newArrival;
    totalService += newService;
  }
}

void RR::scheduleEvent()
{
  // checks if the next event is ready or not if its not it will queue
  if ((startTime > arrivalT.front()) && !arrivalT.empty())
  {
    numProcessInQueue++;
    isIdle = false;
  }
  //cpu is idle
  if (isIdle)
  { //Read from the next Arrival if queue is empty
    if (readyQueueArrival.empty())
    {
      startTime = clock;
      arrivalTime = newArrival;
      serviceTime = newService;
      serviceTime -= quantum; // changing our current servise time thast not in the queue
      if (serviceTime < 0)    // if our serice time is less that zero we will add that back
      {
        serviceTime = ((-1.0) * serviceTime); // getting back what should have been the value
        finishTime = arrivalTime + serviceTime;
        throughPut += finishTime;
        turnAroundTime += finishTime - arrivalTime;
        arrivalT.pop_front(); // getting next value from event
        serviceT.pop_front(); // getting next value from event
        clock += finishTime;
        serviceTime = 0;  // returning it back to zero since it will be the last time processed
        departureCount++; // we are done with the process
      }
      else if (serviceTime > 0)
      {
        finishTime = arrivalTime + serviceTime;
        throughPut += finishTime;
        turnAroundTime += finishTime - arrivalTime;
        arrivalT.pop_front(); // getting next value from event
        serviceT.pop_front(); // getting next value from event
        clock += finishTime;
        readyQeueuSerivice.push_back(serviceTime); // pushing into queue since not done
        readyQueueArrival.push_back(arrivalTime);  // pushing into queue since not done
        marked.push_back(1);                       // Already arrived once
      }
      // else exits the queue
      if (numProcessInQueue != 0)
        numProcessInQueue--;
    }
    //read From the queue if available
    else
    {
      startTime = clock;
      if (marked.front() == 0)
      {
        arrivalTime = readyQueueArrival.front(); // Reading the next value in the queue
      }
      else
      {
        arrivalTime = 0; // Its already Arrived Once so no need to add
      }
      serviceTime = readyQeueuSerivice.front(); // Reading the next value in the queue
      serviceTime -= quantum;                   // changing our current service to accomodate lambda
      readyQueueArrival.pop_front();            // popping the queue that has been used
      readyQeueuSerivice.pop_front();           // popping the queue that has been used
      marked.pop_front(); // popping to stay linear with the others
      if (serviceTime < 0) // if our service time is less that zero we will add that back
      {
        serviceTime = ((-1.0) * serviceTime); // making it positive to get a logical value
        finishTime = arrivalTime + serviceTime;
        throughPut += finishTime;
        turnAroundTime += finishTime - arrivalTime;
        clock += finishTime;
        serviceTime = 0;  // returning it back to zero since it will be the last time processed
        departureCount++; // The event has been executed
      }
      else if (serviceTime > 0)
      {
        finishTime = arrivalTime + serviceTime;
        throughPut += finishTime;
        turnAroundTime += finishTime - arrivalTime;
        clock += finishTime;
        readyQeueuSerivice.push_back(serviceTime); // pushing into queue since not done
        readyQueueArrival.push_back(arrivalTime);  // pushing into queue since not done
        marked.push_back(1);                       // This mean its already arrived once
      }
      // else exits the cpu
    }
  }
  // cpu is not Idle
  else if (!isIdle)
  {
    float newArrivalTime;
    // Adding each event into queue until the cpu is idle again
    while (startTime > arrivalT.front() && !arrivalT.empty())
    {
      readyQueueArrival.push_front(newArrival);  // pushing into the queue
      readyQeueuSerivice.push_front(newService); // pushing into the queue
      marked.push_front(0);                      // This means it has not arrived yet
      arrivalT.pop_front();                      // getting the next event
      serviceT.pop_front();                      // getting the next event
      numProcessInQueue++;
      idleTime += arrivalT.front() - startTime;
      tally++;
    }
    newArrivalTime = startTime;
    finishTime = newArrivalTime + serviceTime;
    isIdle = true;
  }
  // cout << "startTime :  " << startTime
  //      << " inQ : " << readyQeueuSerivice.size()
  //      << " arrivalT : " << arrivalTime
  //      << " serviceT : " << serviceTime
  //      << " finishTime : " << finishTime
  //      << " time : " << clock
  //      << " processed : " << departureCount
  //     //  << " idleTime : " << idleTime
  //      << " isIdle : " << isIdle
  //      << "\n\n";
}

void RR::runSim()
{
  fillTheLists(); // gettig the events
  while (departureCount != stopCondition)
  {
    newArrival = arrivalT.front();
    newService = serviceT.front();
    scheduleEvent();
  }
  //Final calculations
  averageTurnAround = turnAroundTime / (float)stopCondition;
  totalThroughPut = throughPut;
  avgNumProcessInQueue = (float)tally / (float)stopCondition;
  cpuUtilization = (clock - idleTime) / clock;
  arrivalT.clear(), serviceT.clear(), readyQueueArrival.clear(), readyQeueuSerivice.clear();
}

// prints the report
void RR::printReport()
{
  ofstream oFile;
  oFile.open("RR.txt", ios_base::app);
  oFile << setw(7) << lambda
        << setw(22) << averageTurnAround
        << setw(26) << totalThroughPut
        << setw(29) << avgNumProcessInQueue
        << setw(26) << cpuUtilization
        << setw(18) << quantum
        << "\n\n";
  oFile.close();
  //  cout << " Total Arrival : " << totalArrival
  //       << " Total Service : " << startTime
  //       << " My arrival : " << clock
  //       << "\n\n";
}

//Inheritance would have been good now that i think about it
float RR::uRand()
{
  return ((float)rand() / RAND_MAX);
}

float RR::genExp(float lambda)
{
  float u, x;
  x = 0;
  while (x == 0)
  {
    u = uRand();
    x = (-1 / lambda) * log(u);
  }
  return x;
}