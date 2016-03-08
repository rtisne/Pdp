#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include "BoundingBox.hpp"
#include "Character.hpp"

class ConnectedComponent
{
public:
    ConnectedComponent();
    void setListP(std::vector<cv::Point> L);
    std::vector<cv::Point> getListP();
    void initBoundingBox();
    BoundingBox getBoundingBox();
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
