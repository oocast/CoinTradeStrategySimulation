#include <iostream>
#include <iomanip>
#include <sstream>
#include "Account.h"

Account::Account(float numCoin, float cash) :
  numCoin(numCoin),
  cash(cash)
{
}

void Account::PrintResult(const std::string & const strategyName, 
  const std::string & const strategyDescription, 
  const float finalClosePrice) const
{
  // TODO: fix calculation
  const float balance = cash + numCoin * finalClosePrice;
  const float profit = balance - initCash;
  const float profitRate = 100.0f * profit / initCash;

  std::ostringstream ss;
  ss << "--------------------" << '\n';
  ss << "Strategy: " << strategyName << '\n';
  ss << "Description: " << strategyDescription << '\n';
  ss << std::fixed << "Coins: "  << numCoin << '\n';
  ss << std::fixed << std::setprecision(2) << "Cash: " << cash << '\n';
  ss << std::fixed << std::setprecision(2) << "Balance: " << balance << '\n';
  ss << std::fixed << std::setprecision(2) << "Profit: " << profit << '\n';
  ss << std::fixed << std::setprecision(2) << "Profit Rate: " << profitRate << "%" << '\n';
  std::cout << ss.str() << std::flush;
}

float Account::GetCash() const
{
  return cash;
}

void Account::AddCash(float cashValue)
{
  cash += cashValue;
}

float Account::GetCoin() const
{
  return numCoin;
}

void Account::AddCoin(float coinValue)
{
  numCoin += coinValue;
}
