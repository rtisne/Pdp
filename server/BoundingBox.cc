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

void BoundingBox::setY(cv::Point P)
{
  Y = P;
}

cv::Point BoundingBox::getY()
{
  return Y;
}

