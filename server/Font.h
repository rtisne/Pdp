#ifndef FONT_H
#define FONT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "Character.h"


class Font
{
public:
    Font();
    void setName(std::string L);
    std::string getName();
    void ExportToBox();
    void ExportToOd();
    void initBaseline();
    void setBaseline(int y);
    int getBaseline();
    void addCharacter(Character c);
private:
   	std::string Name;
   	std::vector<Character> ListCharacter;
   	int Baseline;
};

#endif // FONT__H