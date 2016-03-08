#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include "BoundingBox.hpp"
#include "Character.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ConnectedComponent
{
public:
    ConnectedComponent();
    void setListPoint(std::vector<cv::Point> L);
    const std::vector<cv::Point> getListPoint();
    int sizeListP();
    void initBoundingBox();
    BoundingBox getBoundingBox();
    void initCharacter(std::string name);
    void setCharacter(Character c);
    Character getCharacter();
    void initBase();
    void setBase(int x);
    const int getBase();

private:
   std::vector<cv::Point> m_listPoint;
   BoundingBox m_boundingBox;
   Character m_char;
   int m_base;
};

#endif // CONNECTEDCOMPONENT_H
