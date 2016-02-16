#include "Character.h"



Character::Character()
{

}



void Character::setLabel(std::string L)
{
	Label = L;
}

std::string Character::getLabel()
{
	return Label;
}

void Character::setBase(int y)
{
	Base = y;
}

int Character::getBase()
{
	return Base;
}

void Character::setImg(cv::Mat P)
{
   Img = P;
}

cv::Mat Character::getImg()
{
	return Img;
}
