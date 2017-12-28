#pragma once

static const float initCash = 500000.0f;

class Account {
private:
  float numCoin;
  float cash;
public:
  Account(float numCoin = 0.0f, float cash = initCash);
  void PrintResult(const std::string & const strategyName) const;
};