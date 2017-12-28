#pragma once
#include <unordered_map>
#include <queue>
#include <cpprest/http_client.h>

using namespace std;
using namespace web::json;

class Market {
private:
  const value & const priceData;
  int date;
  float highValue;
  float lowValue;
  float currentCloseValue;
  unordered_map<int, float> movingAverages;
  deque<float> closePriceHistory;
public:
  Market(const value & const priceData);
  void NextDay();
  float ClosePriceToday() const;
  int GetDate() const;
  bool End() const;
};