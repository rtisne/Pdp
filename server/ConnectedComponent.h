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
    int sizeListP();
    void initCharacter(std::string name);
    void setCharacter(Character c);
    Character getCharacter();
private:
   std::vector<cv::Point> ListP;
   BoundingBox BB;
   Character C;

};

#endif // CONNECTEDCOMPONENT_H
