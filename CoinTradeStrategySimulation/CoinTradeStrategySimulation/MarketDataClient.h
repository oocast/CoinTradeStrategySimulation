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
  utility::string_t pathQueryFragment;
public:
  MarketDataClient(std::string origin,
                  std::string methodPath, 
                  std::unordered_map<std::string, std::string> const &queryParams);
  value GetPriceData();
};

