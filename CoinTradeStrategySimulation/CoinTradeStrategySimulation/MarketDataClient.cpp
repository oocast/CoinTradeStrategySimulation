#include "MarketDataClient.h"

#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility::conversions;
using namespace concurrency;
using namespace concurrency::streams;

MarketDataClient::MarketDataClient(std::string origin,
  std::string methodPath,
  std::unordered_map<std::string, std::string> const &queryParams) :
  client(to_string_t(origin))
{
  uri_builder uriBuilder(uri(to_string_t(methodPath)));
  // uriBuilder.append_path(to_string_t(methodPath));
  for (auto iter = queryParams.begin(); iter != queryParams.end(); iter++) {
    uriBuilder.append_query(to_string_t(iter->first), to_string_t(iter->second));
  }
  pathQueryFragment = uriBuilder.to_string();
}

value MarketDataClient::GetPriceData()
{
  pplx::task<value> dataTask = client.request(methods::GET, pathQueryFragment).then([](http_response response) -> pplx::task<utility::string_t> {
    if (response.status_code() == status_codes::OK) {
      return response.extract_string(true);
    }
    return pplx::task_from_result(to_string_t("Nothing"));
  })
    .then([](pplx::task<utility::string_t> prevTask) {
    try {
      utility::string_t& str = prevTask.get();
      value v = value::parse(str);
      return v.at(U("data"));
    }
    catch (std::exception& e) {
      std::wcout << e.what() << std::endl;
    }
    return json::value::array(0);
  });
  return dataTask.get();
}

