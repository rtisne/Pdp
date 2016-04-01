#ifndef IMAGE_H
#define IMAGE_H

/**
 * \file Image.hpp
 * \brief Image to be processed
 * \author  T.Autret, A.Boschet, T.Labrousse, R.Tisné
 * \version 1.0
 * \date Mars 2016
 *
 * Image to be processed
 *
 */


#include "Line.hpp"
#include <deque>

class Image
{
public:
   
    cv::Mat getMat() const;
    std::string extractDataFromComponent(int index, int lineId) const; 
    void ComputeMask();
    cv::Mat binarizeImage() const;
    static cv::vector<ConnectedComponent> extractComposentConnectImage(cv::Mat img);
    bool inMiddle(cv::Rect bb1, cv::Rect bb2) const;

    std::string jsonBoundingRect();
    std::string jsonBaseline();
    int isValidIdLine(int line) const;
    int isValidIdCC(int line, int cc) const;
    
    void setBoundingBoxAtIndex(int index,int line, int up, int down, int left, int right);
    void setBaselineAtIndex(int index,int line, int value);    
    void setBaselineForLine(int id, int value);
    explicit Image(const std::string &path);

    static int getCharacterHeight(const cv::Mat &img);
    cv::Rect getBoundingBoxAtIndex(int index, int line) const;   
    int getBaselineAtIndex(int index,int line);
    ConnectedComponent getConnectedComponnentAt(int index, int line);

private:
 cv::Mat m_img;
 std::vector<Line> m_listLine;
};

#endif // IMAGE_H