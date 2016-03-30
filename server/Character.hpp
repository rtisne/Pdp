#ifndef CHARACTERE_H
#define CHARACTERE_H

#include <opencv2/core/core.hpp>
#include <algorithm>
#include <iostream>

class Character
{
public:
    Character();
    explicit Character(std::string l);
    const std::string getLabel() const;
    void setBaseline(int x);
    const int getBaseline() const;
    const int countComposant() const;
    void addComposant(int idCC, int idLine);
    void removeComposant(int idCC, int idLine);
    bool hasComposant(int idCC, int idLine);
    std::pair<int,int> getIdComposantAtIndex(int index);

    friend bool operator== ( const Character &c1, const Character &c2);
private:
    std::string m_label;
    cv::Mat m_img;
   	int m_baseline;
    std::vector<std::pair<int,int>> m_idComposantsConnexes;
};

#endif // CHARACTERE__H