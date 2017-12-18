#pragma once
#include <unordered_map>
#include <queue>
#include <cpprest/http_client.h>

using namespace std;
using namespace web::json;

class Market {
  value priceData;
  int date;
  float highValue;
  float lowValue;
  unordered_map<int, float> movingAverages;
  deque<float> closePriceHistory;
};