#include <iostream>
#include "Market.h"

extern unsigned int dayNum;

void Market::Initialize()
{
  dayNum = priceData.size();
  closePrice = priceData.at(DateToIndex()).at(U("close")).as_double();
}

unsigned int Market::DateToIndex() const
{
  return dayNum - 1 - date;
}

Market::Market(const value priceData) :
  date(0),
  highValue(-1),
  lowValue(INFINITY),
  priceData(priceData)
{
  // prepare data of first day
  Initialize();
}

void Market::NextDay()
{
  date++;
  if (date < dayNum)
    closePrice = priceData.at(DateToIndex()).at(U("close")).as_double();
}

float Market::ClosePriceToday() const
{
  return closePrice;
}

float Market::ClosePriceFinal() const
{
  return priceData.at(0).at(U("close")).as_double();
}

float Market::MovingAverage(int length) const
{
  length = (date + 1 < length) ? date + 1 : length;
  float sum = closePrice;
  unsigned int baseIndex = DateToIndex();
  for (unsigned int i = 1; i < length; i++) {
    sum += priceData.at(baseIndex + i).at(U("close")).as_double();
  }
  return sum / (float) length;
}

int Market::GetDate() const
{
  return date;
}

bool Market::End() const
{
  return date >= dayNum;
}

void Market::BuyWithCash(Account * const buyer, float cashToSpend) const
{
  float buyerBudget = buyer->GetCash();
  if (buyerBudget >= cashToSpend) {
    float coin = cashToSpend / closePrice;
    buyer->AddCash(-cashToSpend);
    buyer->AddCoin(coin);
  }
}

void Market::SellToCash(Account * const seller, float cashToGet) const
{
  float sellerCoin = seller->GetCoin();
  float sellerCoinValue = sellerCoin * closePrice;
  if (sellerCoinValue > cashToGet) {
    float coin = cashToGet / closePrice;
    seller->AddCash(cashToGet);
    seller->AddCoin(-coin);
  }
}

void Market::SellWithCoin(Account * const seller, float coinToSell) const
{
  float sellerCoin = seller->GetCoin();
  if (sellerCoin > coinToSell) {
    float cash = coinToSell * closePrice;
    seller->AddCash(cash);
    seller->AddCoin(-coinToSell);
  }
}
