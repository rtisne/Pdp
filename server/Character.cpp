#include "Character.hpp"


Character::Character()
{}
Character::Character(std::string l)
{
	m_label = l;
}


void Character::setLabel(std::string l)
{
	m_label = l;
}

const std::string Character::getLabel()
{
	return m_label;
}

void Character::setBase(int x)
{
	m_base = x;
}

const int Character::getBase()
{
	return m_base;
}

void Character::setImg(cv::Mat i)
{
   m_img = i;
}

const cv::Mat Character::getImg()
{
	return m_img;
}

const int Character::countComposant()
{
	return m_idComposantsConnexes.size();
}
void Character::addComposant(int idCC)
{
	if(!hasComposant(idCC))
		m_idComposantsConnexes.push_back(idCC);
}
void Character::removeComposant(int idCC)
{
	if(hasComposant(idCC))
		m_idComposantsConnexes.erase(std::remove(m_idComposantsConnexes.begin(), m_idComposantsConnexes.end(), idCC), m_idComposantsConnexes.end()); 
}
bool Character::hasComposant(int idCC)
{
	return (std::find(m_idComposantsConnexes.begin(), m_idComposantsConnexes.end(), idCC) != m_idComposantsConnexes.end());
}

bool operator== ( const Character &c1, const Character &c2) 
{
        return c1.m_label == c2.m_label;
}