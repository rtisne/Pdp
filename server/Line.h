#ifndef LINE_H
#define LINE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "Character.h"


class Line
{
public:
    Line();
    void setBaseline(int X);
    int getBaseline();
private:
   	int Baseline;
   	std::vector<Character> ListCharacter();
};

#endif // LINE__H