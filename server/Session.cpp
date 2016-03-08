#include "Session.hpp"

Session::Session()
{}

std::string Session::setFileName(std::string newFileName){
	fileName = newFileName;
}

std::string Session::getFileName(){
	return fileName;
}

int Session::setToken(int newToken){
	token = newToken;
}

int Session::getToken(){
	return token;
}

