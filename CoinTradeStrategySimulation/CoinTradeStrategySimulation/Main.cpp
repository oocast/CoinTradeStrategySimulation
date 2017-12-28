#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <windows.data.json.h>
#include "Simulation.h"

using namespace concurrency;
using namespace concurrency::streams;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
  Simulation simulation; 
  simulation.Start();
  simulation.PrintResult();
  return 0;
}