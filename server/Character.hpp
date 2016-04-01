#ifndef CHARACTER_H
#define CHARACTER_H

/**
 * \file Character.hpp
 * \brief Character of the font
 * \author  T.Autret, A.Boschet, T.Labrousse, R.Tisné
 * \version 1.0
 * \date Mars 2016
 *
 * Character of the font
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
    int countComponent() const;
    void addComponent(int idCC, int idLine);
    void removeComponent(int idCC, int idLine);
    bool hasComponent(int idCC, int idLine) const;
    std::pair<int,int> getIdComponentAtIndex(int index);

    friend bool operator== ( const Character &c1, const Character &c2);
private:
    std::string m_label;
   	int m_baseline;
    std::vector<std::pair<int,int>> m_idComponentsConnexes;
};

#endif // CHARACTER__H