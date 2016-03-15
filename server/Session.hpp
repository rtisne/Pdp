#ifndef SESSION_HPP
#define SESSION_HPP

#include "Font.hpp"
#include "Image.hpp"

class Session
{
public:
    Session();

    void setFileName(std::string f);
    const std::string getFileName();
    void setToken(int t);
    const int getToken();
    Image* getImage();
    Font* getFont();
private:
    std::string m_fileName;
    int m_token;
    Font* m_font;
    Image* m_image;
};

#endif // SESSION__HPP