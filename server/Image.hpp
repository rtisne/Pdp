#ifndef IMAGE_H
#define IMAGE_H

#include "Line.hpp"
#include "Binarization.hpp"
#include <deque>

static const uchar BACKGROUND = 255;

class Image
{
public:
    void setListLine(std::vector<Line> L);
    const std::vector<Line> getListLine();
    Image(std::string path);
    void setImg(cv::Mat P);
    const cv::Mat getImg();
    void ComputeMask();
    int getCharacterHeight(cv::Mat img);
    cv::Mat BinarizedImage();
    cv::vector<ConnectedComponent> extractComposentConnectImage(cv::Mat img);
    void computeBaseline();
    bool CompareBB(cv::Rect bb1, cv::Rect bb2);
    std::string jsonBoundingRect();
    cv::Rect getBoundingBoxAtIndex(int index, int line);   
    ConnectedComponent getConnectedComponnentAt(int index, int line);
     
private:
   cv::Mat m_img;
   std::vector<Line> m_listLine;
};

#endif // IMAGE_H