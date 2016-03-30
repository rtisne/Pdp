#include "Session.hpp"

Session::Session(const std::string &f)
{
	m_image = new Image(f);
	m_font = new Font();
}


void Session::setFileName(const std::string &f){
	m_fileName = f;
}

const std::string Session::getFileName(){
	return m_fileName;
}

Image* Session::getImage(){
	return m_image;
}
Font* Session::getFont(){
	return m_font;
}


void Session::setToken(int t){
	m_token = t;
}

const int Session::getToken(){
	return m_token;
}

