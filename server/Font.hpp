#ifndef FONT_H
#define FONT_H

#include "Character.hpp"

class Font
{
public:
    Font();
    void setName(std::string L);
    std::string getName();
    void ExportToBox();
    void ExportToOd();
    void initBaseline();
    void setBaseline(int y);
    int getBaseline();
    void addCharacter(Character c);
private:
   	std::string Name;
   	std::vector<Character> ListCharacter;
   	int Baseline;
};

#endif // FONT__H