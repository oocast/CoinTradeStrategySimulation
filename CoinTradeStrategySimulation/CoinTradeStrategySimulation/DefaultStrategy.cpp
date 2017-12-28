#include "DefaultStrategy.h"

void DefaultStrategy::Operate(Account * const account, const Market * market)
{
  // Intentionally blank
}

std::string DefaultStrategy::GetName() const
{
  return "No-Op strategy";
}
