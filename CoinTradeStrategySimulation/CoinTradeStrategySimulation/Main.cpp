#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <windows.data.json.h>

using namespace concurrency;
using namespace concurrency::streams;
using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<void> RequestJSONValueAsync() {
  http_client client(L"https://api.huobi.pro/market/history/kline?period=1day&size=200&symbol=btcusdt");
  
  return client.request(methods::GET).then([](http_response response) {
    if (response.status_code() == status_codes::OK) {
      istream is = response.body();
      container_buffer<std::string> inStringBuffer;
      return is.read_to_end(inStringBuffer).then([inStringBuffer](size_t bytesRead) {
        const std::string &text = inStringBuffer.collection();
        std::wcout << text.c_str();
      });
    }
  });
}

int main() {
  //RequestJSONValueAsync().wait();
  return 0;
}