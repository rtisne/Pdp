#ifndef SESSION_HPP
#define SESSION_HPP

#include "Font.hpp"

class Session
{
public:
    Session();
    std::string setFileName(std::string f);
    const std::string getFileName();
    int setToken(int t);
    const int getToken();
private:
    std::string m_fileName;
    int m_token;
    Font m_font;
};

#endif // SESSION__HPP