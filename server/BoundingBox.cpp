#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{}

void BoundingBox::setX(cv::Point P)
{
  m_x = P;
}

const cv::Point BoundingBox::getX()
{
  return m_x;
}

void BoundingBox::setHeight(int x)
{
  m_height = x;
}

const int BoundingBox::getHeight()
{
  return m_height;
}

void BoundingBox::setWidth(int x)
{
  m_width = x;
}

const int BoundingBox::getWidth()
{
  return m_width;
}
