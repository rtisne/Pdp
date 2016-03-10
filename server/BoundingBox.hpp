#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <opencv2/core/core.hpp>



class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(cv::Point2f P, float w, float h);
    void setX(cv::Point2f P);
    const cv::Point2f getX();
    void setHeight(float x);
    const float getHeight();
    void setWidth(float x);
    const float getWidth();
private:
   cv::Point2f m_x;
   float m_height;
   float m_width;
   
};

#endif // BOUNDINGBOX_H
