#include "Character.hpp"

Character::Character()
{}


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
