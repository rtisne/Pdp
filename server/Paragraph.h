#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "Line.h"


class Paragraph
{
public:
    Paragraph();
private:
   	std::vector<Line> ListLine();
};

#endif // PARAGRAPH__H