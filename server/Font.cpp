#include "Font.h"



Font::Font()
{

}



void Font::setName(std::string L)
{
	Name = L;
}

std::string Font::getName()
{
	return Name;
}

void Font::ExportToBox()
{
	
}

void Font::ExportToOd()
{

}

void Font::initBaseline()
{
  int i;
  int SommeBaseline = 0;
  for(i= 0; (unsigned)i < ListCharacter.size()-1; i++)
    {
      SommeBaseline += ListCharacter[i].getBase();
    }
    Baseline = (SommeBaseline / i);
}

void Font::setBaseline(int y)
{
	Baseline = y;
}

int Font::getBaseline()
{
	return Baseline;
}
