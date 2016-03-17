#include "ConnectedComponent.hpp"

ConnectedComponent::ConnectedComponent()
{

}

ConnectedComponent::ConnectedComponent(std::vector<cv::Point> vec){
	m_listPoint = vec;
}

void ConnectedComponent::setListPoint(std::vector<cv::Point> L)
{
	m_listPoint = L;
}

const std::vector<cv::Point> ConnectedComponent::getListPoint()
{
	return m_listPoint;
}

int ConnectedComponent::sizeListP()
{
	return m_listPoint.size();
}

void ConnectedComponent::setOffsetBaseline(int x)
{
	m_offset_baseline = x;
}

const int ConnectedComponent::getOffsetBaseline()
{
	return m_offset_baseline;
}

const bool ConnectedComponent::getInline()
{
	return m_inline;
}

void ConnectedComponent::setInline(bool x)
{
	m_inline = x;
}

void ConnectedComponent::setBoundingBox(int up, int down, int left, int right){
	m_up = up;
	m_down = down;
	m_right = right;
	m_left = left;
}
bool ConnectedComponent::hasPoint(int x, int y)
{
  // cv::Point pt = cv::(x,y);Point
  // return (std::find(m_listPoint.begin(), m_listPoint.end(), pt) != m_listPoint.end());

  for(std::vector<cv::Point>::iterator it = m_listPoint.begin(); it != m_listPoint.end();++it)
  {
    if (it->x == x && it->y == y)
      return true;
  }
  return false;

}
const int ConnectedComponent::getUpLine()
{
	return m_up;
}

const int ConnectedComponent::getDownLine()
{
	return m_down;
}

const int ConnectedComponent::getRightLine()
{
	return m_right;
}

const int ConnectedComponent::getLeftLine()
{
	return m_left;
}
