#include "Font.hpp"


Font::Font()
{
}

void Font::setName(const std::string &n)
{
	m_name = n;
}

const std::string Font::getName() const
{
	return m_name;
}

void Font::addCharacter(const Character &c)
{
  m_listCharacter.push_back(c);
}

int Font::indexOfCharacter(const std::string &c)
{
  for (unsigned i=0; i<m_listCharacter.size(); i++)
  {
    Character s = m_listCharacter.at(i);
    if(s.getLabel() == c)
      return i;
  }
  return -1;
}

int Font::indexOfCharacterForCC(int idCC, int idLine)
{
  for (unsigned i=0; i < m_listCharacter.size(); i++)
  {
    Character s = m_listCharacter.at(i);
    if(s.hasComposant(idCC, idLine))
      return i;
  }
  return -1;
}


bool Font::hasCharacter(const Character &c)
{
  return (std::find(m_listCharacter.begin(), m_listCharacter.end(), c) != m_listCharacter.end());
}

Character* Font::characterAtIndex(int id)
{
  return &m_listCharacter.at(id);
}

void Font::removeCharacter(int id)
{
  m_listCharacter.erase(m_listCharacter.begin() + id);
}

const int Font::countCharacter() const
{
  return m_listCharacter.size();
}
