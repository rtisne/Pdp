#ifndef CHARACTERE_H
#define CHARACTERE_H

/**
 * \file Charactere.hpp
 * \brief Charactere of the font
 * \author  T.Autret, A.Boschet, T.Labrousse, R.Tisné
 * \version 1.0
 * \date Mars 2016
 *
 * Caractere of the font
 *
 */

#include <opencv2/core/core.hpp>
#include <algorithm>
#include <iostream>

class Character
{
public:
    Character();

    explicit Character(const std::string &l);
    std::string getLabel() const;
    void setBaseline(int x);
    int getBaseline() const;
    int countComposant() const;
    void addComposant(int idCC, int idLine);
    void removeComposant(int idCC, int idLine);
    bool hasComposant(int idCC, int idLine) const;
    std::pair<int,int> getIdComposantAtIndex(int index);

    friend bool operator== ( const Character &c1, const Character &c2);
private:
    std::string m_label;
    cv::Mat m_img;
   	int m_baseline;
    std::vector<std::pair<int,int>> m_idComposantsConnexes;
};

#endif // CHARACTERE__H