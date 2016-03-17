#ifndef FONT_H
#define FONT_H

#include <string.h> 
#include <iostream>
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
    bool hasCharacter(Character c);
    int indexOfCharacter(std::string c);
    int indexOfCharacterForCC(int idCC, int idLine);
    Character* characterAtIndex(int id);
    void removeCharacter(int id);
    int countCharacter();
private:
   	std::string m_name;
   	std::vector<Character> m_listCharacter;
   	int m_baseline;
};

#endif // FONT_H