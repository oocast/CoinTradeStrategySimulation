#include <numeric>
#include <iomanip>
#include "GlobalPeakStepStrategy.h"

GlobalPeakStepStrategy::GlobalPeakStepStrategy(const std::vector<float>& const steps, 
  const std::vector<float>& const cashes, 
  const int period, const bool clearRemaining) :
  buyCashSteps(std::map<float, float>()),
  period(period),
  periodCash(std::accumulate(cashes.begin(), cashes.end(), 0.0f)),
  periodRemainingCash(periodCash),
  clearRemaining(clearRemaining)
{
  for (unsigned int i = 0; i < steps.size(); i++) {
    buyCashSteps[steps[i]] = cashes[i];
  }
  it = buyCashSteps.cbegin();
}

// TODO: base on high/low price, not close
void GlobalPeakStepStrategy::Operate(Account * const account, const Market * market)
{
  int date = market->GetDate();
  if (date > 0) {
    float close = market->ClosePriceToday();
    float dropRate = 1.0f - close / prevPeak;
    if (dropRate > 0.0001f) {
      while (it != buyCashSteps.cend() && dropRate > it->first) {
        market->BuyWithCash(account, it->second);
        it++;
      }
    }
    else if (close >= prevPeak) {
      market->SellToCash(account, periodCash - periodRemainingCash);
    }

    // Reset period contexts
    if (date % period == period - 1) {
      if (clearRemaining) {
        market->BuyWithCash(account, periodRemainingCash);
      }

      it = buyCashSteps.cbegin();
      periodRemainingCash = periodCash;
    }
  }
  prevPeak = market->PeakPrice();
}

std::string GlobalPeakStepStrategy::GetName() const
{
  return "Global Peak Step Strategy";
}

std::string GlobalPeakStepStrategy::GetDescription() const
{
  std::ostringstream ss;
  ss << '\n';
  for (auto it = buyCashSteps.cbegin(); it != buyCashSteps.cend(); it++) {
    ss << "When price drops " << (it->first) * 100.0f << "%, ";
    ss << std::fixed << std::setprecision(2) << "spend " << it->second << " cash\n";
  }
  ss << "Total period budget " << std::fixed << std::setprecision(2) << periodCash << " cash\n";
  ss << "Period " << period << " days\n";
  ss << "Sell coins to recover period cashes when price back to peak\n";
  if (clearRemaining) {
    ss << "Spend all remaining cash each period\n";
  }
  return ss.str();
}
