#include "Session.hpp"

Session::Session()
{}


void Session::setFileName(std::string f){
	m_fileName = f;
	m_image = new Image(f);
	m_font = new Font();
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

