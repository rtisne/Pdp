#ifndef CHARACTERE_H
#define CHARACTERE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "ConnectedComponent.h"


class Character
{
public:
    Character();
    void setLabel(std::string L);
    std::string getLabel();
    void setBase(int X);
    int getBase();
    void setImg(cv::Mat P);
    cv::Mat getImg();
private:
    std::string Label;
    cv::Mat Img;
   	ConnectedComponent CC;
   	int Base;
};

#endif // CHARACTERE__H