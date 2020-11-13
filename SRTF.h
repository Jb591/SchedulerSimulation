#ifndef SRTF_H
#define SRTF_H
#include <list>
#include <queue>
#include <vector>
using namespace std;

class SRTF
{
private:
public:
  SRTF();
  void printReport();
  void initialize(int l, float tS, int stop);
  void runSim();
  void scheduleEvent();
  float uRand();
  float genExp(float lambda);
  void fillTheLists();
  void updateQueue();
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice, marked;
  vector<float> shortestTime;
  bool done;
  int lambda;
  float cpuTotal;
  float startTime;
  float newArrival;
  float newService;
  float averageServiceTime;
  int stopCondition;
  float clock;
  float turnAroundTime;
  float reamainingTime;
  float arrivalTime;
  float serviceTime;
  float finishTime;
  int departureCount;
  float remainingTime;
  float throughPut;
  int numProcessInQueue;
  float mu;
  int tally;
  float avgNumProcessInQueue;
  float cpuUtilization;
  float idleTime;
  float averageTurnAround;
  float totalThroughPut;
};
#endif