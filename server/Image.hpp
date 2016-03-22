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
    const std::string extractDataFromComponent(int index, int lineId); 
    void ComputeMask();
    int getCharacterHeight(cv::Mat img);
    cv::Mat BinarizedImage();
    cv::vector<ConnectedComponent> extractComposentConnectImage(cv::Mat img);
    void computeBaseline();
    bool CompareBB(cv::Rect bb1, cv::Rect bb2);
    std::string jsonBoundingRect();
    std::string jsonBaseline();
    cv::Rect getBoundingBoxAtIndex(int index, int line);   
    void setBoundingBoxAtIndex(int index,int line, int up, int down, int left, int right);
    ConnectedComponent getConnectedComponnentAt(int index, int line);
    void setBaselineForLine(int id, int value);
     
private:
   cv::Mat m_img;
   std::string m_filename;
   std::vector<Line> m_listLine;
};

#endif // IMAGE_H