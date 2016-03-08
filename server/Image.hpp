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
    const cv::Mat getImg();
    void setListConnectedComponent(std::vector<ConnectedComponent> L);
    const std::vector<ConnectedComponent> getListConnectedComponent();
    void ImgMask();
    void setListLine(std::vector<Line> L);
    const std::vector<Line> getListLine();
    void BinarizedImage();
    void extractConnectedComponent(cv::Mat &input,const cv::Point &seed,ConnectedComponent &cc);
    void extractAllConnectedComponents();
    void putInLine();

private:
   cv::Mat m_img;
   cv::Mat m_mask;
   std::vector<ConnectedComponent> m_listConnectedComponent;
   std::vector<Line> m_listLine;
};

#endif // IMAGE_H