#pragma once
#include "Strategy.h"

const int defaultPeriod = 30;
const bool defaultClearRemaining = true;

class GlobalPeakStepStrategy : public Strategy {
  std::map<float, float> buyCashSteps;
  const int period;
  const float periodCash;
  const bool clearRemaining;
  float periodRemainingCash;
  float prevPeak;
  std::map<float, float>::const_iterator it;
public:
  GlobalPeakStepStrategy(const std::vector<float> & const steps, 
                        const std::vector<float> & const cashes, 
                        const int period = defaultPeriod, 
                        const bool clearRemaining = defaultClearRemaining);
  void Operate(Account* const account, const Market * market);
  std::string GetName() const;
  std::string GetDescription() const;
};