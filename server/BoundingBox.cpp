#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{}
BoundingBox::BoundingBox(cv::Point2f P, float w, float h)
{
	m_x = P;
	m_width = w;
	m_height = h;
}
void BoundingBox::setX(cv::Point2f P)
{
  m_x = P;
}

const cv::Point2f BoundingBox::getX()
{
  return m_x;
}

void BoundingBox::setHeight(float x)
{
  m_height = x;
}

const float BoundingBox::getHeight()
{
  return m_height;
}

void BoundingBox::setWidth(float x)
{
  m_width = x;
}

const float BoundingBox::getWidth()
{
  return m_width;
}
