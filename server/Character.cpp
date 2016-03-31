#include "Character.hpp"


Character::Character():m_baseline(0)
{}
Character::Character(const std::string &l):m_label(l), m_baseline(0)
{}


std::string Character::getLabel() const
{
	return m_label;
}

void Character::setBaseline(int x)
{
	m_baseline = x;
}

int Character::getBaseline() const
{
	return m_baseline;
}

int Character::countComposant() const
{
	return m_idComposantsConnexes.size();
}
void Character::addComposant(int idCC, int idLine)
{
	if(!hasComposant(idCC, idLine))
		m_idComposantsConnexes.push_back(std::make_pair(idLine,idCC));
}
void Character::removeComposant(int idCC, int idLine)
{
	if(hasComposant(idCC, idLine))
		m_idComposantsConnexes.erase(std::remove(m_idComposantsConnexes.begin(), m_idComposantsConnexes.end(), std::make_pair(idLine,idCC)), m_idComposantsConnexes.end()); 
}
bool Character::hasComposant(int idCC, int idLine) const
{
	for (const auto &s : m_idComposantsConnexes) 
		if(s.first == idLine && s.second == idCC)
			return true;
		return false;

}
std::pair<int,int> Character::getIdComposantAtIndex(int index)
{
	return m_idComposantsConnexes.at(index);
}

bool operator== ( const Character &c1, const Character &c2) 
{
        return c1.m_label == c2.m_label;
}