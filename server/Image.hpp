#ifndef IMAGE_H
#define IMAGE_H

#include "Line.hpp"
#include "Binarization.hpp"
#include <deque>

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