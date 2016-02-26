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

//RNG rng(12345);


#define UPLOAD_DIR "../client/data"

WebServer *webServer = NULL;

LocalRepository *myUploadRepo = NULL;

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

    class Uploader: public DynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        if (!request->isMultipartContent())
          return false;

        MPFD::Parser *parser=request->getMPFDparser();

        std::map<std::string,MPFD::Field *> fields=parser->GetFieldsMap();
        std::map<std::string,MPFD::Field *>::iterator it;
        for (it=fields.begin();it!=fields.end();it++) 
        {
          if (fields[it->first]->GetType()==MPFD::Field::TextType)
           return false;
          else
          {
            NVJ_LOG->append(NVJ_INFO, "Got file field: [" + it->first + "] Filename:[" + fields[it->first]->GetFileName() + "] TempFilename:["  + fields[it->first]->GetTempFileName() + "]\n");

            // Copy files to upload directory
            std::ifstream  src( fields[it->first]->GetTempFileName().c_str(), std::ios::binary);
            string dstFilename= string(UPLOAD_DIR)+'/'+fields[it->first]->GetFileName();
            std::ofstream  dst( dstFilename.c_str(), std::ios::binary);
            if (!src || !dst)
              NVJ_LOG->append(NVJ_ERROR, "Copy error: check read/write permissions");
            else
              dst << src.rdbuf();
            src.close();
            dst.close();
            myUploadRepo->reload();
            return fromString(fields[it->first]->GetFileName(), response); 
          }
        }
        return true;
      }

    } uploader;







    class getBoundingBox: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        // string path;
        // request->getParameter("path", path);
        // if (!isValidSession(request))
        // {
        //   Image * img = new Image(path);
        //   img->BinarizedImage();
        //   img->extractAllConnectedComponents();
        //   std::vector<ConnectedComponent> ListTmpCC = img->getListCC();
        //   for(int i= 0; i < ListTmpCC.size()-1; i++)
        //     {
        //       for(int j= 0; j < ListTmpCC[i].getListP().size()-1;j++)
        //         {
        //           std::vector<cv::Point> ListTmp = ListTmpCC[i].getListP();
        //           cout << ListTmp[j] << endl;
        //         }
        //     }
        // }
        
      }
    } getBoundingBox;

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
      add("getBoundingBox.txt",&getBoundingBox);
      add("uploader.txt",&uploader);
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
  LocalRepository *myLocalRepo = new LocalRepository("", "../client/");
  //myLocalRepo.addDirectory("", "../client/"); 
  webServer->addRepository(myLocalRepo);

  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);

  myUploadRepo = new LocalRepository("upload", "./upload");
  webServer->addRepository(myUploadRepo);
   /* 
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
    imshow( "Display window", img->getImg()); */

  webServer->startService();
 
  webServer->wait();
  
  AuthPAM::stop();
  LogRecorder::freeInstance();
  return 0;
}


