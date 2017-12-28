#pragma once
#include <vector>
#include "Account.h"
#include "Strategy.h"
#include "MarketDataClient.h"
#include "Market.h"

using namespace std;

class Simulation {
  Market * marketPtr;
  vector<Account> accounts;
  vector<Strategy*> strategies;
public:
  Simulation();
  ~Simulation();
  void Start();
  void Reset();
  void PrintResult();
};