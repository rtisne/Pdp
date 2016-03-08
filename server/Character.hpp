#ifndef CHARACTERE_H
#define CHARACTERE_H

#include <opencv2/core/core.hpp>


class Character
{
public:
    Character();
    void setLabel(std::string l);
    const std::string getLabel();
    void setBase(int x);
    const int getBase();
    void setImg(cv::Mat i);
    const cv::Mat getImg();
private:
    std::string m_label;
    cv::Mat m_img;
   	int m_base;
};

#endif // CHARACTERE__H