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
    void setY(cv::Point P);
    cv::Point getY();
private:
   cv::Point X;
   cv::Point Y;
   
};

#endif // BOUNDINGBOX_H
