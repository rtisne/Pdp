#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>


#include "BoundingBox.h"



class ConnectedComponent
{
public:
    ConnectedComponent();
    void setListP(std::vector<cv::Point> L);
    std::vector<cv::Point> getListP();
    void initBB();
    int sizeListP();
private:
   std::vector<cv::Point> ListP;
   BoundingBox BB;

};

#endif // CONNECTEDCOMPONENT_H
