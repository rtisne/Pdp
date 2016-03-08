#ifndef FONT_H
#define FONT_H

#include "Character.hpp"

class Font
{
public:
    Font();
    void setName(std::string n);
    const std::string getName();
    void ExportToBox();
    void ExportToOd();
    void computeBaseline();
    void setBaseline(int x);
    const int getBaseline();
    void addCharacter(Character c);
private:
   	std::string m_name;
   	std::vector<Character> m_listCharacter;
   	int m_baseline;
};

#endif // FONT__H