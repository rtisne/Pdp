#include "Session.hpp"

Session::Session():m_token(0),m_font(NULL),m_image(NULL)
{}

Session::~Session()
{
	delete m_image;
	m_image = NULL;
	delete m_font;
	m_font = NULL;
}

void Session::setFileName(std::string f){
	m_fileName = f;
	m_image = new Image(f);
	m_font = new Font();
}

const std::string Session::getFileName() const{
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

const int Session::getToken() const{
	return m_token;
}

