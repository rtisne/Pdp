#include "Session.hpp"

Session::Session()
{}


void Session::setFileName(std::string f){
	m_fileName = f;
}

const std::string Session::getFileName(){
	return m_fileName;
}


void Session::setToken(int t){
	m_token = t;
}

const int Session::getToken(){
	return m_token;
}

