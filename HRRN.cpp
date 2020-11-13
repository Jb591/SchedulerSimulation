#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "HRRN.h"
using namespace std;

HRRN::HRRN()
{
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice;
  vector <float> ratio;
}

void HRRN::initialize(int l, float tS, int stop)
{
  // initialize our conditions and gather required input
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
void HRRN::fillTheLists()
{
  // This will fill our events and processes
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
void HRRN::updateRatio()
{
  // Initializing our data to be used
  float *data;
  float aNewArrival;
  float aNewService;
  int index = 0;
  float newWaitTime = 0;
  int size = readyQueueArrival.size();
  list<float> aNewArrivalQ, aNewServiceQ;
  if (!readyQueueArrival.empty()) // only if our queue has items
  {
    ratio.clear();
    // Sets temporary Queues to not damange original Queues
    aNewArrivalQ.assign(readyQueueArrival.begin(), readyQueueArrival.end());
    aNewServiceQ.assign(readyQeueuSerivice.begin(), readyQeueuSerivice.end());
    while (!(aNewArrivalQ.empty())) // Gets the new Ratios
    {
      newWaitTime = clock - aNewArrivalQ.front();
      // calculating our ratios and storing them into a vector based off the new queue
      ratio.push_back((newWaitTime + aNewServiceQ.front()) / aNewServiceQ.front()); 
      aNewArrivalQ.pop_front();
      aNewServiceQ.pop_front();
    }
    // our ratios are now linear with our queue
    data = ratio.data();
    // Finding the largest Ratio
    for (int i = 1; i < size; i++)
    {
      if (data[index] < data[i])
      {
        index = i;
      }
    }
    aNewArrivalQ.clear();
    aNewServiceQ.clear();
    for (int i = 0; i < size; i++) // Puts it on Top of a PriorityQueue
    {
      if (i == index) // We've Found and will store it
      {
        aNewArrivalQ.push_front(readyQueueArrival.front()); // Pushed to the Front
        aNewServiceQ.push_front(readyQeueuSerivice.front());
        readyQeueuSerivice.pop_front();
        readyQueueArrival.pop_front();
      }
      else
      {
        //if its not it will continue
        aNewArrivalQ.push_back(readyQueueArrival.front()); // pushed to the back
        aNewServiceQ.push_back(readyQeueuSerivice.front());
        readyQeueuSerivice.pop_front();
        readyQueueArrival.pop_front();
      }
    }
    // // Updating our Queues to the temporary Queue that have priority on Top
    readyQeueuSerivice.assign(aNewServiceQ.begin(), aNewServiceQ.end());
    readyQueueArrival.assign(aNewArrivalQ.begin(), aNewArrivalQ.end());
  }
  // else will not do anything, In order to save time
}

void HRRN::scheduleEvent()
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
      finishTime = arrivalTime + serviceTime; 
      throughPut += finishTime;
      turnAroundTime += finishTime - arrivalTime;
      arrivalT.pop_front(); // chnaged to front from back
      serviceT.pop_front();
      clock += finishTime;
      departureCount++;
      if (numProcessInQueue != 0)
        numProcessInQueue--;
    }
    //read From the queue if 
    else
    {
      startTime = clock;
      arrivalTime = readyQueueArrival.front();
      serviceTime = readyQeueuSerivice.front();
      readyQueueArrival.pop_front();
      readyQeueuSerivice.pop_front();
      finishTime = arrivalTime + serviceTime;
      throughPut += finishTime;
      turnAroundTime += finishTime - arrivalTime;
      clock += finishTime;
      departureCount++;
    }
  }
  // cpu is not idle
  else if (!isIdle)
  {
    float newArrivalTime;
    // push all of the events into queue until the time is 
    while (startTime > arrivalT.front() && !arrivalT.empty())
    {
      readyQueueArrival.push_back(newArrival);
      readyQeueuSerivice.push_back(newService);
      arrivalT.pop_front();
      serviceT.pop_front();
      numProcessInQueue++;
      idleTime += arrivalT.front() - startTime;
      tally++;
    }
    newArrivalTime = startTime;
    finishTime = newArrivalTime + serviceTime;
    isIdle = true;
  }
  updateRatio(); // Will update the ratio everytime a new one is added

  // This is for debugging an shows that its effective
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

void HRRN::runSim()
{
  fillTheLists(); // Fills the events and processes

  // Will continue until all of the processes are done
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

void HRRN::printReport()
{
  //Prints into respected txt file
  ofstream oFile;
  oFile.open("HRRN.txt", ios_base::app);
  oFile << setw(7) << lambda
        << setw(22) << averageTurnAround
        << setw(26) << totalThroughPut
        << setw(29) << avgNumProcessInQueue
        << setw(26) << cpuUtilization
        << "\n\n";
  oFile.close();
}

float HRRN::uRand()
{
  return ((float)rand() / RAND_MAX);
}

float HRRN::genExp(float lambda)
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