#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>


class BoundingBox
{
public:
    BoundingBox();
    void setX(cv::Point P);
    cv::Point getX();
    void setHeight(int i);
    const int getHeight();
    void setWidth(int i);
    const int getWidth();
private:
   cv::Point X;
   int height;
   int width;
   
};

#endif // BOUNDINGBOX_H
