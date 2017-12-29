#include <sstream>
#include <iomanip>
#include "MovingAverageStrategy.h"


MovingAverageStrategy::MovingAverageStrategy(int length, 
  float tradeThreshold, 
  float unitCash, 
  float sellRate) :
  length(length),
  trendThreshold(defaultTrendThreshold),
  tradeThreshold(tradeThreshold),
  unitCash(unitCash),
  sellRate(sellRate),
  prevMA(-1.0f)
{
}

void MovingAverageStrategy::Operate(Account * const account, const Market * market)
{
  if (market->GetDate() >= length - 1) {
    float ma = market->MovingAverage(length);
    if (prevMA > 0.0f) {
      // BULL market
      if (ma > prevMA * (1.0f + trendThreshold)) {
        float close = market->ClosePriceToday();
        // Step on MA, buy
        if (close > ma && close < ma * (1.0f + tradeThreshold)) {
          float budget = account->GetCash();
          float cash = (unitCash < budget) ? unitCash : budget;
          market->BuyWithCash(account, cash);
        }
      }
      // Trend stops
      else if (ma > prevMA * (1.0f - trendThreshold)) {
        float close = market->ClosePriceToday();
        // Below MA, sell
        if (close < ma) {
          float coin = sellRate * account->GetCoin();
          market->SellWithCoin(account, coin);
        }
      }
    }
    prevMA = ma;
  }
}

std::string MovingAverageStrategy::GetName() const
{
  std::ostringstream ss;
  ss << "MA";
  ss << length;
  ss << " Strategy";
  return ss.str();
}

std::string MovingAverageStrategy::GetDescription() const
{
  std::ostringstream ss;
  ss << "\nRefer MA" << length << "\n";
  ss << std::fixed << std::setprecision(2) << "Unit operation cash amout " << unitCash << "\n";
  ss << "Only trade in bull market\n";
  ss << std::fixed << std::setprecision(2) << "Sell " << sellRate * 100.0f << "% coins every time\n";
  ss << std::fixed << std::setprecision(2) << "Operate if off from MA within " << tradeThreshold;
  return ss.str();
}
