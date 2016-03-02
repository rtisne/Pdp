#include "Line.h"



Line::Line()
{

}

void Line::initBaseline()
{
  int i;
  int sommeBaseline = 0;
  for(i= 0; (unsigned)i < ListCC.size()-1; i++)
    {
      sommeBaseline += ListCC[i].getBase();
    }
    Baseline = (sommeBaseline / i);
}

void Line::setBaseline(int y)
{
	Baseline = y;
}

int Line::getBaseline()
{
	return Baseline;
}

void Line::addConnectedComponent(ConnectedComponent cc)
{
	 ListCC.push_back(cc);
}
