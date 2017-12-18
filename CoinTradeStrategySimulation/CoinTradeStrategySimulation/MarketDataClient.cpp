#include "MarketDataClient.h"

using namespace utility::conversions;

MarketDataClient::MarketDataClient(std::string origin,
  std::string methodPath,
  std::unordered_map<std::string, std::string> &queryParams):
  client(uri(to_string_t(origin)))
{
  uri_builder uriBuilder(uri(to_string_t(methodPath)));
}


value MarketDataClient::getPriceData()
{
  return value();
}
