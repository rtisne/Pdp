#include "Line.hpp"

Line::Line(){

}

void Line::setBaseline(float x)
{
  m_baseline = x;
}

const float Line::getBaseline()
{
  return m_baseline;
}

void Line::addCC(ConnectedComponent cc)
{
  m_ListCC.push_back(cc);
}

void Line::setListCC(std::vector<ConnectedComponent> cc)
{
  m_ListCC = cc;
}

const std::vector<ConnectedComponent> Line::getListCC()
{
  return m_ListCC;
}

ConnectedComponent Line::getConnectedComponentAtIndex(int index){
	return m_ListCC.at(index);
}

void Line::setBoundingBoxAtIndex(int index, int up, int down, int left, int right){
	m_ListCC[index].setBoundingBox(up, down, left, right);
}
