#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include "Character.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ConnectedComponent
{
public:
    ConnectedComponent();
    ConnectedComponent(std::vector<cv::Point> vec);
    void setListPoint(std::vector<cv::Point> L);
    const std::vector<cv::Point> getListPoint();
    int sizeListP();
    void setOffsetBaseline(int x);
    const int getOffsetBaseline();
    const bool getInline();
    void setInline(bool x);
    void setBoundingBox(int up, int down, int left, int right);
    const int getUpLine();
    const int getDownLine();
    const int getRightLine();
    const int getLeftLine();
private:
   std::vector<cv::Point> m_listPoint;
   float m_offset_baseline;
   int m_up;
   int m_down;
   int m_right;
   int m_left;
   bool m_inline = false;
};

#endif // CONNECTEDCOMPONENT_H
