#pragma once
#include "Market.h"
#include "Strategy.h"

class DefaultStrategy : public Strategy {
public:
  void Operate(Account* const account, const Market * market);
  std::string GetName() const;
};