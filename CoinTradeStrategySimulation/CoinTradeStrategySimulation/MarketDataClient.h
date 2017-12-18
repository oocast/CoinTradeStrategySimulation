#pragma once
#include <cpprest/http_client.h>
#include <unordered_map>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;

class MarketDataClient {
private:
  http_client client;
  std::string pathQueryFragment;
public:
  MarketDataClient(std::string origin, 
                  std::string methodPath, 
                  std::unordered_map<std::string, std::string> &queryParams);
  value getPriceData();
};

