#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "ConnectedComponent.h"
#include "Line.h"

static const uchar BACKGROUND = 255;

class Image
{
public:
    Image(std::string path);
    void setImg(cv::Mat P);
    cv::Mat getImg();
    void setListCC(std::vector<ConnectedComponent> L);
    std::vector<ConnectedComponent> getListCC();
    void ImgMask();
    void setListLine(std::vector<Line> L);
    std::vector<Line> getListLine();
    void BinarizedImage();
    void extractConnectedComponent(cv::Mat &input,const cv::Point &seed,ConnectedComponent &cc);
    void extractAllConnectedComponents();
    void putInLine();

private:
   cv::Mat img;
   cv::Mat mask;
   std::vector<ConnectedComponent> ListCC;
   std::vector<Line> ListLine;
};

#endif // IMAGE_H