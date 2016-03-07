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
<<<<<<< HEAD
    Line::setBaseline(SommeBaseline / i);
=======
    Baseline = (sommeBaseline / i);
>>>>>>> ab386f899c34901c24e9dbfc479b9f1c9c97a42c
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

void Line::setListCC(std::vector<ConnectedComponent> L)
{
  ListCC = L;
}

std::vector<ConnectedComponent> Line::getListCC()
{
  return ListCC;
}
