#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <opencv2/core/core.hpp>



class BoundingBox
{
public:
    BoundingBox();
    void setX(cv::Point P);
    const cv::Point getX();
    void setHeight(int x);
    const int getHeight();
    void setWidth(int x);
    const int getWidth();
private:
   cv::Point m_x;
   int m_height;
   int m_width;
   
};

#endif // BOUNDINGBOX_H
