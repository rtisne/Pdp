#ifndef CHARACTERE_H
#define CHARACTERE_H

#include <opencv2/core/core.hpp>
#include <algorithm>
#include <iostream>

class Character
{
public:
    Character();
    Character(std::string l);
    void setLabel(std::string l);
    const std::string getLabel();
    void setBase(int x);
    const int getBase();
    void setImg(cv::Mat i);
    const cv::Mat getImg();
    const int countComposant();
    void addComposant(int idCC);
    void removeComposant(int idCC);
    bool hasComposant(int idCC);

    friend bool operator== ( const Character &c1, const Character &c2);
private:
    std::string m_label;
    cv::Mat m_img;
   	int m_base;
    std::vector<int> m_idComposantsConnexes;
};

#endif // CHARACTERE__H