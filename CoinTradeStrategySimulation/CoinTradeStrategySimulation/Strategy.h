#pragma once
#include "Account.h"
#include "Market.h"

class Strategy {
public:
  virtual void Operate(Account * const account, const Market * market) = 0;
  virtual std::string GetName() const = 0;
};