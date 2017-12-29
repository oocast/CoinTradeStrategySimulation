#pragma once
#include "Strategy.h"

const float defaultTrendThreshold = 0.01f;
const float defaultSellRate = 0.2f;

class MovingAverageStrategy : public Strategy {
private:
  int length;
  float trendThreshold;
  float tradeThreshold;
  float unitCash;
  float sellRate;
  float prevMA;
public:
  MovingAverageStrategy(int length, float tradeThreshold, float unitCash, float sellRate = defaultSellRate);
  void Operate(Account* const account, const Market * market);
  std::string GetName() const;
  std::string GetDescription() const;
};