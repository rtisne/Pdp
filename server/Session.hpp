#ifndef SESSION_HPP
#define SESSION_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "Font.h"



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