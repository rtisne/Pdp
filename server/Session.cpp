#include "Session.hpp"
Session::Session()
{
	
}

void Session::setFileName(std::string newFileName){
	fileName = newFileName;
}

std::string Session::getFileName(){
	return fileName;
}

void Session::setToken(int newToken){
	token = newToken;
}

int Session::getToken(){
	return token;
}

