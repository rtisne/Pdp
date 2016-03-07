#include "Line.h"



Line::Line()
{

}

void Line::initBaseline()
{
  int i;
  int SommeBaseline = 0;
  for(i= 0; (unsigned)i < ListCharacter.size()-1; i++)
    {
      SommeBaseline += ListCharacter[i].getBase();
    }
    Line::setBaseline(SommeBaseline / i);
}

void Line::setBaseline(int y)
{
	Baseline = y;
}

int Line::getBaseline()
{
	return Baseline;
}

