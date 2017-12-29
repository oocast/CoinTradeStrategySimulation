#pragma once
#include <unordered_map>
#include <queue>
#include <cpprest/http_client.h>

using namespace std;
using namespace web::json;

class Market {
private:
  const value priceData;
  int date;
  float highValue;
  float lowValue;
  void Initialize();
  unsigned int DateToIndex() const;
public:
  Market(const value priceData);
  void NextDay();
  float ClosePriceToday() const;
  float ClosePriceFinal() const;
  float MovingAverage(int length) const;
  int GetDate() const;
  bool End() const;
};