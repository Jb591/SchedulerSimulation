#ifndef FCFS_H
#define FCFS_H
#include <list>
#include <queue>
using namespace std;

class FCFS
{
private:

public:
  FCFS();
  void printReport();
  void initialize(int l, float tS, int stop);
  void runSim();
  void scheduleEvent();
  float uRand();
  float genExp(float lambda);
  void fillTheLists();
  void updateRatio();
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice;
  vector<float> ratio;
  int lambda;
  float totalArrival;
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
  bool isIdle;
  int tally;
  float avgNumProcessInQueue;
  float cpuUtilization;
  float idleTime;
  float averageTurnAround;
  float totalThroughPut;
};
#endif