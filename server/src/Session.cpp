#include "../headers/Session.hpp"


Session::Session(const std::string &f):m_fileName(""),m_token(0),m_font(new Font()),m_image(new Image(f))
{}
Session::Session(const Session& session):m_fileName(""),m_token(session.getToken()),m_font(nullptr), m_image(nullptr)
{
}
Session::~Session()
{
	delete m_image;
	m_image = nullptr;
	delete m_font;
	m_font = nullptr;
}

void Session::setFileName(const std::string &f){
	m_fileName = f;
}

std::string Session::getFileName() const{
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

int Session::getToken() const{
	return m_token;
}

