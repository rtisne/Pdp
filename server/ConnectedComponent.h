#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>


#include "BoundingBox.h"
#include "Character.h"



class ConnectedComponent
{
public:
    ConnectedComponent();
    void setListP(std::vector<cv::Point> L);
    std::vector<cv::Point> getListP();
    void initBoundingBox();
    void getBoundingBox();
    int sizeListP();
    void initCharacter(std::string name);
    void setCharacter(Character c);
    Character getCharacter();
    void initBase();
    void setBase(int y);
    int getBase();

private:
   std::vector<cv::Point> ListP;
   BoundingBox BB;
   Character C;
   int Base;
};

#endif // CONNECTEDCOMPONENT_H
