#pragma once
#include <vector>
#include "Account.h"
#include "Strategy.h"
#include "MarketDataClient.h"
#include "Market.h"

using namespace std;

class Simulation {
private:
  Market * marketPtr;
  vector<Account> accounts;
  vector<Strategy*> strategies;
  void CreateGlobalPeakStepStrategies();
public:
  Simulation();
  ~Simulation();
  void Start();
  void PrintResult();
};