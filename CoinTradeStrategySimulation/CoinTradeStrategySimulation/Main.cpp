#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <windows.data.json.h>
#include "MarketDataClient.h"

using namespace concurrency;
using namespace concurrency::streams;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
  std::unordered_map<std::string, std::string> queryParams;
  queryParams["period"] = "1day";
  queryParams["size"] = "200";
  queryParams["symbol"] = "btcusdt";
  MarketDataClient client("https://api.huobi.pro", "/market/history/kline", queryParams);
  value v = client.GetPriceData();
  std::cout << v.type() << std::endl;
  
  return 0;
}