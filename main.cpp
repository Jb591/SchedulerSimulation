#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "FCFS.h"
#include "HRRN.h"
#include "SRTF.h"
#include "RR.h"
using namespace std;

int stopCondition = 1000;
int lambda = 0;
int scheduler = 0;
float avgServiceTime = 0;
float quantum = 0;
float mu = 0;

void getData(int &l, int &sT, float &tS, float &q, char *argv[]);
void initialize(int l, int sT, float tS, float q, int stop);
void printReport(int sT);
void runSim(int sT);

FCFS fcfs;
HRRN hrrn;
SRTF srtf;
RR rr;

int main(int argc, char *argv[])
{
  srand(time(NULL));
  getData(lambda, scheduler, avgServiceTime, quantum, argv);
  initialize(lambda, scheduler, avgServiceTime, quantum, stopCondition);
  runSim(scheduler);
  printReport(scheduler);
  return EXIT_SUCCESS;
}

void getData(int &l, int &sT, float &tS, float &q, char *argv[])
{
  sT = atoi(argv[1]);
  l = atoi(argv[2]);
  tS = (float)atof(argv[3]);
  q = (float)atof(argv[4]);
}

void initialize(int l, int sT, float tS, float q, int stop)
{
  switch (sT)
  {
    case 1:
      // cout << "Now Initializing FCFS : \n";
      fcfs.initialize(l, tS, stop);
      break;
    case 2:
      // cout << "Now Initializing SRTF : \n";
      srtf.initialize(l, tS, stop);
      break;
    case 3:
      // cout << "Now Initializing HRRN : \n";
      hrrn.initialize(l, tS, stop);
      break;
    case 4:
      // cout << "Now Initializing RR : \n";
      rr.initialize(l, tS, q, stop);
      break;
    default:
      cout << "Error " << sT << " is Not Available!!";
      break;
  }
}

void printReport(int sT)
{
  switch (sT)
  {
  case 1:
    // cout << "Now Reporting FCFS : \n";
    fcfs.printReport();
    break;
  case 2:
    // cout << "Now Reporting SRTF : \n";
    srtf.printReport();
    break;
  case 3:
    // cout << "Now Reporting HRRN : \n";
    hrrn.printReport();
    break;
  case 4:
    // cout << "Now Reporting RR : \n";
    rr.printReport();
    break;
  default:
    cout << "Error " << sT << " is Not Available!!";
    break;
  }
}

void runSim(int sT)
{
  switch (sT)
  {
  case 1:
    cout << "Now Running FCFS : \n";
    fcfs.runSim();
    break;
  case 2:
    cout << "Now Running SRTF : \n";
    srtf.runSim();
    break;
  case 3:
    cout << "Now Running HRRN : \n";
    hrrn.runSim();
    break;
  case 4:
    cout << "Now Reporting RR : \n";
    rr.runSim();
    break;
  default:
    cout << "Error " << sT << " is Not Available!!";
    break;
  }
}
