#include <iostream>
#include "Market.h"
#include "Constants.h"

Market::Market(const value const & priceData) :
  date(0),
  highValue(-1),
  lowValue(INFINITY),
  currentCloseValue(0),
  priceData(priceData)
{

}

void Market::NextDay()
{
  date++;
}

float Market::ClosePriceToday() const
{
  return 0.0f;
}

int Market::GetDate() const
{
  return date;
}

bool Market::End() const
{
  return date >= DAY_NUM;
}
