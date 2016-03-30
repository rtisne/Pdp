#ifndef FONT_H
#define FONT_H

#include <string.h> 
#include <iostream>
#include "Character.hpp"

class Font
{
public:
    Font();

    void setName(const std::string &n);
    const std::string getName() const;
    void addCharacter(const Character &c);
    bool hasCharacter(const Character &c);
    int indexOfCharacter(const std::string &c);

    int indexOfCharacterForCC(int idCC, int idLine);
    Character* characterAtIndex(int id);
    void removeCharacter(int id);
    const int countCharacter() const;
private:
   	std::string m_name;
   	std::vector<Character> m_listCharacter;

};

#endif // FONT_H