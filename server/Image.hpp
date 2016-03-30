#ifndef IMAGE_H
#define IMAGE_H

#include "Line.hpp"
#include "Binarization.hpp"
#include <deque>

class Image
{
public:
   
    cv::Mat getMat();
    const std::string extractDataFromComponent(int index, int lineId); 
    void ComputeMask();
    cv::Mat binarizeImage();
    const cv::vector<ConnectedComponent> extractComposentConnectImage(cv::Mat img) const;
    const bool inMiddle(cv::Rect bb1, cv::Rect bb2) const;

    std::string jsonBoundingRect();
    std::string jsonBaseline();
    int isValidIdLine(int line);
    int isValidIdCC(int line, int cc);
    
    void setBoundingBoxAtIndex(int index,int line, int up, int down, int left, int right);
    void setBaselineAtIndex(int index,int line, int value);    
    void setBaselineForLine(int id, int value);
    void setListLine(const std::vector<Line> &L);
    explicit Image(const std::string &path);
    void setImg(cv::Mat P);

    std::vector<Line> getListLine();
    const int getCharacterHeight(const cv::Mat &img) const;
    cv::Rect getBoundingBoxAtIndex(int index, int line);   
    int getBaselineAtIndex(int index,int line);
    ConnectedComponent getConnectedComponnentAt(int index, int line);

private:
 cv::Mat m_img;
 std::string m_filename;
 std::vector<Line> m_listLine;
};

#endif // IMAGE_H