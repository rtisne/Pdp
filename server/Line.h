#ifndef LINE_H
#define LINE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "Character.h"
#include "ConnectedComponent.h"


class Line
{
public:
    Line();
    void initBaseline();
    void setBaseline(int y);
    int getBaseline();
    void addConnectedComponent(ConnectedComponent cc);
private:
   	int Baseline;
   	std::vector<ConnectedComponent> ListCC;
};

#endif // LINE__H