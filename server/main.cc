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

using namespace cv;
using namespace std;

RNG rng(12345);


WebServer *webServer = NULL;

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
        if (!isValidSession(request))
        return fromString("SessionOK", response);
      }
    } startSession;

    class Controller: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string param;

        if (request->getParameter("pageId", param) && param == "LOGIN" && isValidSession(request))
        {
          response->forwardTo("gauge.html"); 
          return true;
        } 

        if (request->hasParameter("disconnect")) // Button disconnect
          request->removeSession();

        if (!isValidSession(request))
          response->forwardTo("login.html");
        else
          response->forwardTo("gauge.html");       
        
        return true;
      }

    } controller;
     
  public:
    MyDynamicRepository() : DynamicRepository()
    {
      add("startSession.txt",&startSession);
      add("index.html",&controller);
    }
};

/***********************************************************************/

int main(int argc, char** argv )
{
  // connect signals
  signal( SIGTERM, exitFunction );
  signal( SIGINT, exitFunction );
  
  NVJ_LOG->addLogOutput(new LogStdOutput);
  AuthPAM::start(); 
  webServer = new WebServer;
  //webServer->setUseSSL(true, "../mycert.pem");
  LocalRepository myLocalRepo;
  myLocalRepo.addDirectory("", "./html"); 
  webServer->addRepository(&myLocalRepo);

  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
    Image * img = new Image(argv[1]);
  // Read the file
    
    if(! img->getImg().data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }
    img->BinarizedImage();

    img->extractAllConnectedComponents();
     
     //Verification des données
    std::vector<ConnectedComponent> ListTmpCC = img->getListCC();
    for(int i= 0; i < ListTmpCC.size()-1; i++)
    {
        for(int j= 0; j < ListTmpCC[i].getListP().size()-1;j++)
        {
        std::vector<cv::Point> ListTmp = ListTmpCC[i].getListP();
         cout << ListTmp[j] << endl;
        }
    }


    //affichage CC avec openCV + bounding Box
    vector<vector<Point> > contours_poly(ListTmpCC.size());
    vector<Rect> boundRect( ListTmpCC.size() );

    for( int i = 0; i < ListTmpCC.size(); i++ )
     { approxPolyDP( Mat(ListTmpCC[i].getListP()), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
     }

      Mat drawing = Mat::zeros( img->getImg().size(), CV_8UC3 );
    for( int i = 0; i< ListTmpCC.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
     }


     namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
        
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", img->getImg()); 

  webServer->startService();
 
  webServer->wait();
  
  AuthPAM::stop();
  LogRecorder::freeInstance();
  return 0;
}


