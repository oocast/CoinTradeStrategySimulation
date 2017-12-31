#pragma once
#include <unordered_map>
#include <queue>
#include <cpprest/http_client.h>
#include "Account.h"

using namespace std;
using namespace web::json;

class Market {
private:
  const value priceData;
  const float feeRate;
  int date;
  float highValue;
  float lowValue;
  float closePrice;
  void Initialize();
  unsigned int DateToIndex() const;
public:
  Market(const value priceData, const float feeRate);
  void NextDay();
  float ClosePriceToday() const;
  float PeakPrice() const;
  float ValleyPrice() const;
  float ClosePriceFinal() const;
  float MovingAverage(int length) const;
  int GetDate() const;
  bool End() const;
  void BuyWithCash(Account * const buyer, float cashToSpend) const;
  void SellToCash(Account * const seller, float cashToGet) const;
  void SellWithCoin(Account * const seller, float coinToSell) const;
};