#ifndef SESSION_HPP
#define SESSION_HPP

#include "Font.hpp"

class Session
{
public:
    Session();
    std::string setFileName(std::string newFileName);
    std::string getFileName();
    int setToken(int newToken);
    int getToken();
private:
    std::string fileName;
    int token;
    Font myFont;
};

#endif // SESSION__HPP