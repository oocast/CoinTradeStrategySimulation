#include <iostream>
#include <iomanip>
#include <sstream>
#include "Account.h"

Account::Account(float numCoin, float cash) :
  numCoin(numCoin),
  cash(cash)
{
}

void Account::PrintResult(const std::string & const strategyName) const
{
  // TODO: fix calculation
  const float profit = cash - initCash;
  const float profitRate = 100.0f * profit / initCash;

  std::ostringstream ss;
  ss << "--------------------" << '\n';
  ss << "Strategy: " << strategyName << '\n';
  ss << "Coins: "  << numCoin << '\n';
  ss << std::setprecision(2) << "Profit: " << profit << '\n';
  ss << std::setprecision(2) << "Profit Rate: " << profitRate << "%" << '\n';
  std::cout << ss.str() << std::flush;
}
