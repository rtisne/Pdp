#include "ConnectedComponent.hpp"

ConnectedComponent::ConnectedComponent()
{}

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

void ConnectedComponent::initBoundingBox()
{
  cv::Rect rect = boundingRect(m_listPoint);
  cv::Point P;
  P.x = rect.x;
  P.y = rect.y;
  
  m_boundingBox.setX(P);
  m_boundingBox.setHeight(rect.height);
  m_boundingBox.setWidth(rect.width);
}
void ConnectedComponent::setBoundingBox(const BoundingBox b){
  m_boundingBox = b;
}
BoundingBox ConnectedComponent::getBoundingBox()
{
  return m_boundingBox;
}

void ConnectedComponent::initCharacter(std::string name)
{
  m_char.setLabel(name);
  m_char.setBase(m_base);

}

void ConnectedComponent::initBase()
{
  m_base = m_boundingBox.getX().y + m_boundingBox.getHeight();
}

void ConnectedComponent::setCharacter(Character c)
{
   m_char = c;
}

Character ConnectedComponent::getCharacter()
{
  return m_char;
}

void ConnectedComponent::setBase(int x)
{
  m_base = x;
}

const int ConnectedComponent::getBase()
{
  return m_base;
}