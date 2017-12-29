#include <iostream>
#include "Market.h"

extern unsigned int dayNum;

void Market::Initialize()
{
  dayNum = priceData.size();
  // cout << ClosePriceToday() << endl;
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
}

float Market::ClosePriceToday() const
{
  return priceData.at(DateToIndex()).at(U("close")).as_double();
}

float Market::ClosePriceFinal() const
{
  return priceData.at(0).at(U("close")).as_double();
}

float Market::MovingAverage(int length) const
{
  length = (date + 1 < length) ? date + 1 : length;
  float sum = 0.0f;
  unsigned int baseIndex = DateToIndex();
  for (unsigned int i = 0; i < length; i++) {
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
