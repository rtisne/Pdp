#ifndef IMAGE_H
#define IMAGE_H

#include "Line.hpp"
#include "Binarization.hpp"
#include <deque>

static const uchar BACKGROUND = 255;

class Image
{
public:
    // const std::vector<Line> getListLine() const;
    explicit Image(std::string path);
    const std::string extractDataFromComponent(int index, int lineId); 
    void ComputeMask();
    const int getCharacterHeight(cv::Mat img) const;
    cv::Mat BinarizedImage();
    const cv::vector<ConnectedComponent> extractComposentConnectImage(const cv::Mat img) const;
    void computeBaseline();
    static const bool inMiddle(const cv::Rect bb1,const cv::Rect bb2) const;
    std::string jsonBoundingRect();
    std::string jsonBaseline();
    cv::Rect getBoundingBoxAtIndex(int index, int line);   
    int getBaselineAtIndex(int index,int line);
    void setBoundingBoxAtIndex(int index,int line, int up, int down, int left, int right);
    void setBaselineAtIndex(int index,int line, int value);
    ConnectedComponent getConnectedComponnentAt(int index, int line);
    void setBaselineForLine(int id, int value);
     
private:
   cv::Mat m_img;
   std::string m_filename;
   std::vector<Line> m_listLine;
};

#endif // IMAGE_H