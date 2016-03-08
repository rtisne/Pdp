#include "Line.hpp"

Line::Line()
{}

void Line::computeBaseline()
{
  int i;
  int sumBaseline = 0;
  for(i= 0; (unsigned)i < m_listConnectedComponent.size()-1; i++)
    {
      sumBaseline += m_listConnectedComponent[i].getBase();
    }
    Line::setBaseline(sumBaseline / i);
}

void Line::setBaseline(int x)
{
	m_baseline = x;
}

const int Line::getBaseline()
{
	return m_baseline;
}

void Line::addConnectedComponent(ConnectedComponent cc)
{
	 m_listConnectedComponent.push_back(cc);
}

void Line::setListConnectedComponent(std::vector<ConnectedComponent> cc)
{
  m_listConnectedComponent = cc;
}

const std::vector<ConnectedComponent> Line::getListConnectedComponent()
{
  return m_listConnectedComponent;
}
