//********************************************************
/**
 * @file  example2.cc 
 *
 * @brief libnavajo example code.
 *
 * @author T.Descombes (descombes@lpsc.in2p3.fr)
 *
 * @version 1  
 * @date 27/01/15
 */
//********************************************************

#include <signal.h> 
#include <string.h> 
#include "libnavajo/AuthPAM.hh"
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <deque>

#include "Image.h"
#include "Font.h"

using namespace cv;
using namespace std;

//RNG rng(12345);

WebServer *webServer = NULL;
Image * img;
Font * font;

void exitFunction( int dummy )
{
   if (webServer != NULL) webServer->stopService();
}


class MyDynamicRepository : public DynamicRepository
{
    class MyDynamicPage : public DynamicPage
    {
      protected:
        bool isValidSession(HttpRequest* request)
        {
          void *myAttribute = request->getSessionAttribute("username");          
          return myAttribute != NULL;
        }
    };
    class startSession: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string path;
        request->getParameter("path", path);
        if (!isValidSession(request))
        {
          img = new Image(path);
          img->BinarizedImage();
          img->extractAllConnectedComponents();
          std::vector<ConnectedComponent> ListTmpCC = img->getListCC();
          for(int i= 0; (unsigned)i < ListTmpCC.size()-1; i++)
            {
              for(int j= 0; (unsigned)j < ListTmpCC[i].getListP().size()-1;j++)
                {
                  std::vector<cv::Point> ListTmp = ListTmpCC[i].getListP();
                  cout << ListTmp[j] << endl;
                }
            }
        }
        return fromString("SessionOK", response);
      }
    } startSession;


    class createCharacter: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string numCC;
        string nameChar;
        request->getParameter("numCC", numCC);
        request->getParameter("nameChar", nameChar);
        if (!isValidSession(request))
        {
          std::vector<ConnectedComponent> ListTmp;
          ListTmp = img->getListCC();
          //ListTmp[numCC].initCharacter(nameChar);
          //font->addCharacter(ListTmp[numCC].getCharacter());
          img->setListCC(ListTmp);
        }
        return fromString("CharacterOK", response);
      }
    } createCharacter;

    class upload: public MyDynamicPage
    {

      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string path;
        request->getParameter("image", path);
        
        return true;
      }

    } upload;


    class Controller: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {

        if (!isValidSession(request))
          response->forwardTo("index.php");
        return true;
      }

    } controller;
     
  public:
    MyDynamicRepository() : DynamicRepository()
    {
      add("startSession.txt",&startSession);
      add("upload.txt",&upload);
      add("index.html",&controller);
    }
};

/***********************************************************************/

int main(int argc, char** argv )
{
  signal( SIGTERM, exitFunction );
  signal( SIGINT, exitFunction );
  
  NVJ_LOG->addLogOutput(new LogStdOutput);
  AuthPAM::start(); 
  webServer = new WebServer;
  LocalRepository myLocalRepo;
  myLocalRepo.addDirectory("", "../client/"); 
  webServer->addRepository(&myLocalRepo);

  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);
 

  webServer->startService();
 
  webServer->wait();
  
  AuthPAM::stop();
  LogRecorder::freeInstance();
  return 0;
}


