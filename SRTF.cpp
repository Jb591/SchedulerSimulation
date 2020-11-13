#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "SRTF.h"
using namespace std;

SRTF::SRTF()
{
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice, marked;
  vector <float> shortestTime;
}

void SRTF::fillTheLists()
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

void SRTF::initialize(int l, float tS, int stop)
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
  done = true;
  startTime = 0;
  serviceTime = 0;
}

void SRTF::updateQueue()
{
  float *data;
  float aNewArrival;
  float aNewService;
  int index = 0;
  float newWaitTime = 0;
  int size = readyQueueArrival.size();
  list<float> aNewArrivalQ, aNewServiceQ;
  if (!readyQueueArrival.empty()) // only if our queue has items
  {
    shortestTime.clear();
    // Sets temporary Queues to not damange original Queues
    aNewArrivalQ.assign(readyQueueArrival.begin(), readyQueueArrival.end());
    aNewServiceQ.assign(readyQeueuSerivice.begin(), readyQeueuSerivice.end());
    while (!(aNewArrivalQ.empty())) // Gets the new shortestTimes
    {
      newWaitTime = aNewServiceQ.front();
      // calculating our shortestTimes and storing them into a vector based off the new queue
      shortestTime.push_back(newWaitTime);
      aNewArrivalQ.pop_front();
      aNewServiceQ.pop_front();
    }
    // our shortestTimes are now linear with our queue
    data = shortestTime.data();
    // Finding the shortest shortestTime
    for (int i = 1; i < size; i++)
    {
      if (data[index] > data[i])
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
        //if its not what we're looking for will continue and store in the back of Queue
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

void SRTF::scheduleEvent()
{
  // checks if the next event is ready or not if its not it will queue
  if ((newService > serviceT.front()) && !arrivalT.empty())
  {
    numProcessInQueue++;
    done = false;
  }
  else if ((newService < serviceT.front()) && !arrivalT.empty())
  {
    done = true;
  }
  //cpu is done
  if (done) 
  { //Read from the next Arrival if queue is empty
    if (readyQueueArrival.empty())
    {
      startTime = clock;
      arrivalTime = newArrival;
      serviceTime = newService;
      finishTime = arrivalTime + serviceTime;
      throughPut += finishTime;
      turnAroundTime += finishTime - arrivalTime;
      arrivalT.pop_front();
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
      //cout << "from the Queue\n";
    }
  }
  else if (!done)
  {
    // checking if the next service time is shorter than before
    if (serviceTime > serviceT.front() && !arrivalT.empty())
    {
      readyQueueArrival.push_back(newArrival);
      readyQeueuSerivice.push_back(newService);
      arrivalT.pop_front();
      serviceT.pop_front();
      numProcessInQueue++;
      idleTime += arrivalT.front() + arrivalT.front() - startTime;
      tally++;
      updateQueue();
    }
    // if its not it will continue
    else if (serviceTime < serviceT.front() && !arrivalT.empty())
    {
      // Will change the value of the current servise and subtract the next one
      float newServiceT = newService - serviceT.front();
      serviceT.pop_front(); // remove Fronm the top
      serviceT.push_front(newServiceT); // will push to the top the new service time
      updateQueue();
      if (serviceTime <= 0)
        done = true;
    }
    finishTime = startTime + serviceTime;
  } 
  // This shows that ist functioning correctly, such as continuing to process after no more are there
  // cout << "startTime :  " << startTime
  //      << " inQ : " << readyQeueuSerivice.size()
  //      << " arrivalT : " << arrivalTime
  //      << " serviceT : " << serviceTime
  //      << " finishTime : " << finishTime
  //      << " time : " << clock
  //      << " processed : " << departureCount
  //      << " idleTime : " << idleTime
  //      << " isIdle : " << isIdle
  //      << "\n\n";
}

void SRTF::runSim()
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
}

void SRTF::printReport()
{
  ofstream oFile;
  oFile.open("SRTF.txt", ios_base::app);
  oFile << setw(7) << lambda
        << setw(22) << averageTurnAround
        << setw(26) << totalThroughPut
        << setw(29) << avgNumProcessInQueue
        << setw(26) << cpuUtilization
        << "\n\n";
  oFile.close();
}

float SRTF::uRand()
{
  return ((float)rand() / RAND_MAX);
}

float SRTF::genExp(float lambda)
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