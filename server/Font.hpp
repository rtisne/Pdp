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
    const std::string getName() const;
    void addCharacter(Character c);
    bool hasCharacter(Character c);
    int indexOfCharacter(std::string c);
    int indexOfCharacterForCC(int idCC, int idLine);
    Character* characterAtIndex(int id);
    void removeCharacter(int id);
    const int countCharacter() const;
private:
   	std::string m_name;
   	std::vector<Character> m_listCharacter;
};

#endif // FONT_H