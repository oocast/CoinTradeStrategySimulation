#pragma once
#include <vector>
#include "Account.h"
#include "Strategy.h"

using namespace std;

class Simulation {
  vector<Account> accounts;
  vector<Strategy*> strategies;
public:
  Simulation();
  void start();
  void reset();
  void printResult();
};