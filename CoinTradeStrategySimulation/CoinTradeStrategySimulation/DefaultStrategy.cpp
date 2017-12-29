#include "DefaultStrategy.h"

void DefaultStrategy::Operate(Account * const account, const Market * market)
{
  // Intentionally blank
  float price = market->ClosePriceToday();
}

std::string DefaultStrategy::GetName() const
{
  return "No-Op strategy";
}

std::string DefaultStrategy::GetDescription() const
{
  return "Do nothing";
}
