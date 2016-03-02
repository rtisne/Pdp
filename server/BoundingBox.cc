#include "BoundingBox.h"



BoundingBox::BoundingBox()
{

}


void BoundingBox::setX(cv::Point P)
{
  X = P;
}

cv::Point BoundingBox::getX()
{
  return X;
}

void BoundingBox::setHeight(int i)
{
  height = i;
}

const int BoundingBox::getHeight()
{
  return height;
}

void BoundingBox::setWidth(int i)
{
  width = i;
}

const int BoundingBox::getWidth()
{
  return width;
}
