#ifndef RR_H
#define RR_H
#include <list>
#include <queue>
#include <vector>
using namespace std;

class RR
{
private:
public:
  RR();
  void printReport();
  void initialize(int l, float tS, float q, int stop);
  void runSim();
  void scheduleEvent();
  float uRand();
  float genExp(float lambda);
  void fillTheLists();
  void updateRR();
  float totalArrival;// For checking if correct 
  float totalService;// For checking if correct 
  list<float> arrivalT, serviceT, readyQueueArrival, readyQeueuSerivice, marked;
  float quantum;
  bool isIdle;
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