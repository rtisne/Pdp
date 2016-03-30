#ifndef IMAGE_H
#define IMAGE_H

#include "Line.hpp"
#include "Binarization.hpp"
#include <deque>

class Image
{
public:
   
    const cv::Mat getMat() const;
    const std::string extractDataFromComponent(int index, int lineId) const; 
    void ComputeMask();
    const cv::Mat binarizeImage() const;
    static cv::vector<ConnectedComponent> extractComposentConnectImage(cv::Mat img);
    const bool inMiddle(cv::Rect bb1, cv::Rect bb2) const;

    std::string jsonBoundingRect();
    std::string jsonBaseline();
    const int isValidIdLine(int line) const;
    const int isValidIdCC(int line, int cc) const;
    
    void setBoundingBoxAtIndex(int index,int line, int up, int down, int left, int right);
    void setBaselineAtIndex(int index,int line, int value);    
    void setBaselineForLine(int id, int value);
    explicit Image(const std::string &path);

    static int getCharacterHeight(const cv::Mat &img);
    const cv::Rect getBoundingBoxAtIndex(int index, int line) const;   
    int getBaselineAtIndex(int index,int line);
    ConnectedComponent getConnectedComponnentAt(int index, int line);

private:
 cv::Mat m_img;
 std::string m_filename;
 std::vector<Line> m_listLine;
};

#endif // IMAGE_H