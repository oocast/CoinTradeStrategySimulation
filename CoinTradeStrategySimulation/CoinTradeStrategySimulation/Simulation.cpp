#include <string>
#include "Account.h"
#include "MovingAverageStrategy.h"
#include "Simulation.h"

#define PERIOD "1day"
#define SYMBOL "btcusdt"

extern unsigned int dayNum;

Simulation::Simulation() :
  accounts(vector<Account>()),
  strategies(vector<Strategy*>())
{
  std::unordered_map<std::string, std::string> queryParams;
  queryParams["period"] = PERIOD;
  queryParams["size"] = std::to_string(dayNum);
  queryParams["symbol"] = SYMBOL;
  MarketDataClient client("https://api.huobi.pro", "/market/history/kline", queryParams);
  value v = client.GetPriceData();

  marketPtr = new Market(v);

  accounts.push_back(Account());
  strategies.push_back(new MovingAverageStrategy(5, 0.03f, 5000.0f));
}

Simulation::~Simulation()
{
  delete marketPtr;
  marketPtr = nullptr;
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
  cout << "Warning: all fees ignored" << endl;
  for (unsigned int i = 0; i < strategies.size(); i++) {
    Account & const account = accounts[i];
    Strategy * const strategyPtr = strategies[i];
    account.PrintResult(strategyPtr->GetName(), strategyPtr->GetDescription(), marketPtr->ClosePriceFinal());
  }
}

