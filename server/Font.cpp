#include "Font.hpp"


Font::Font()
{}

void Font::setName(std::string n)
{
	m_name = n;
}

const std::string Font::getName()
{
	return m_name;
}

void Font::ExportToBox()
{
	
}

void Font::ExportToOd()
{

}

void Font::computeBaseline()
{
  int i;
  int sumBaseline = 0;
  for(i= 0; (unsigned)i < m_listCharacter.size()-1; i++)
    {
      sumBaseline += m_listCharacter[i].getBase();
    }
    m_baseline = (sumBaseline / i);
}

void Font::setBaseline(int x)
{
	m_baseline = x;
}

const int Font::getBaseline()
{
	return m_baseline;
}

void Font::addCharacter(Character c)
{
  m_listCharacter.push_back(c);
}