#include <string>
#include "Account.h"
#include "Constants.h"
#include "DefaultStrategy.h"
#include "Simulation.h"

#define PERIOD "1day"
#define SYMBOL "btcusdt"


Simulation::Simulation() :
  accounts(vector<Account>()),
  strategies(vector<Strategy*>())
{
  std::unordered_map<std::string, std::string> queryParams;
  queryParams["period"] = PERIOD;
  queryParams["size"] = std::to_string(DAY_NUM);
  queryParams["symbol"] = SYMBOL;
  MarketDataClient client("https://api.huobi.pro", "/market/history/kline", queryParams);
  value v = client.GetPriceData();
  std::cout << v.at(0).at(U("close")).as_double() << std::endl;

  marketPtr = new Market(v);

  accounts.push_back(Account());
  strategies.push_back(new DefaultStrategy());
}

Simulation::~Simulation()
{
  delete marketPtr;
  for (Strategy * strategy : strategies) {
    delete strategy;
    strategy = nullptr;
  }
}

void Simulation::Start()
{
  while (!marketPtr->End()) {
    for (unsigned int i = 0; i < strategies.size(); i++) {
      Account & const account = accounts[i];
      Strategy * const strategyPtr = strategies[i];
      strategyPtr->Operate(&account, marketPtr);
    }
    marketPtr->NextDay();
  }
}

void Simulation::PrintResult()
{
  for (unsigned int i = 0; i < strategies.size(); i++) {
    Account & const account = accounts[i];
    Strategy * const strategyPtr = strategies[i];
    account.PrintResult(strategyPtr->GetName());
  }
}

