#include "Session.hpp"

Session::Session()
{}


void Session::setFileName(std::string f){
	m_fileName = f;
	m_image = new Image(f);
}

const std::string Session::getFileName(){
	return m_fileName;
}

Image* Session::getImage(){
	return m_image;
}


void Session::setToken(int t){
	m_token = t;
}

const int Session::getToken(){
	return m_token;
}

