#include "libnavajo/AuthPAM.hh"
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"

#include <time.h>
#include <signal.h> 
#include <string.h> 

#include "Image.hpp"
#include "Font.hpp"
#include "Session.hpp"


using namespace cv;
using namespace std;


#define UPLOAD_DIR "../client/data/"

WebServer *webServer = NULL;

LocalRepository *myUploadRepo = NULL;

std::vector<Session> activeSessions;

void exitFunction( int dummy )
{
   if (webServer != NULL) webServer->stopService();
}

bool test_format(std::string fileName)
{
  string extension = fileName.substr(fileName.find(".") + 1);
  if(extension.compare("jpg") == 0)
  {
    return true;
  }
  else if (extension.compare("jpeg") == 0)
  {
    return true;
  }
  else if (extension.compare("png") == 0)
  {
    return true;
  }
  else if (extension.compare("tif") == 0)
  {
    return true;
  }
  else {    
    return false;

  }
}

std::string gen_random(std::string extension) {
    static const char letter[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
          srand(time(NULL));    
    string random;
    for (int i = 0; i < 10; ++i) {
        random += letter[rand() % (sizeof(letter) - 1)];
    }

    return random + extension;
}

std::string InitiateSession(std::string fileName,HttpRequest *request)
{
  int cptExample=0;
  Session * mySession = new Session();
  void *sessionTmp = request->getSessionAttribute("mySession");
    if(sessionTmp == NULL)
    {
      srand(time(NULL));
      cptExample= rand();
      NVJ_LOG->append(NVJ_INFO,fileName + to_string(cptExample));
      mySession->setToken(cptExample);
      mySession->setFileName(fileName);
      request->setSessionAttribute ("mySession", mySession );
    }
  activeSessions.push_back(*mySession);
  return "{\"fileName\":\""+mySession->getFileName()+"\",\"token\":"+to_string(mySession->getToken())+"}";
}

int getActiveSessionFromToken(int token)
{
  for (unsigned i=0; i<activeSessions.size(); i++)
  {
    Session s = activeSessions.at(i);
    if(s.getToken() == token)
      return i;
  }
  return -1;
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

        MPFD::Parser *parser = request->getMPFDparser();

        std::map<std::string,MPFD::Field *> fields=parser->GetFieldsMap();
        std::map<std::string,MPFD::Field *>::iterator it;
        for (it=fields.begin();it!=fields.end();it++) 
        {
          if(test_format(fields[it->first]->GetFileName()))
          {
            if (fields[it->first]->GetType()==MPFD::Field::TextType)
              return false;
            else
            {
              std::string newFileName = gen_random(fields[it->first]->GetFileName().substr(fields[it->first]->GetFileName().find(".")));
              std::string json_Session = InitiateSession(newFileName,request);
              NVJ_LOG->append(NVJ_INFO, "Got file field: [" + it->first + "] Filename:[" + newFileName + "] TempFilename:["  + fields[it->first]->GetTempFileName() + "]\n");


              std::ifstream  src( fields[it->first]->GetTempFileName().c_str(), std::ios::binary);
              string dstFilename = string(UPLOAD_DIR)+'/'+newFileName;
              std::ofstream  dst( dstFilename.c_str(), std::ios::binary);
              if (!src || !dst)
                NVJ_LOG->append(NVJ_ERROR, "Copy error: check read/write permissions");
              else
                dst << src.rdbuf();
              src.close();
              dst.close();
              myUploadRepo->reload();
              NVJ_LOG->append(NVJ_ERROR, json_Session);
              return fromString(json_Session, response); 
            }
          } 
          else {
            return fromString("{\"error\":\"This format of image isn't correct\"}",response);
          }

        }
        return true;
      }
    } uploader;

    class getBoundingBox: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string token;
        request->getParameter("token", token);
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        Image * img = new Image(UPLOAD_DIR + activeSessions.at(sessionIndex).getFileName());
        //Line * line = new Line();
        img->BinarizedImage();
         //img->ImgMask();
        img->extractAllConnectedComponents();
        std::vector<ConnectedComponent> ListTmpCC = img->getListConnectedComponent();
        string json = "{";
        for(int i= 0; i < ListTmpCC.size()-1; i++)
        {
          Rect rect = boundingRect(ListTmpCC[i].getListPoint());
          json += ("\" "+ to_string(i) +"\":{");
          json += ("\"x\":" + to_string(rect.x) + ",");
          json += ("\"y\":" + to_string(rect.y) + ",");
          json += ("\"width\":" + to_string(rect.width) + ",");
          json += ("\"height\":" + to_string(rect.height));
          json += ("}");

          if(i != ListTmpCC.size()-2)
          {
            json += (",");
          }
        }
        json += ("}");        
        return fromString(json, response); 
      }
        
    } getBoundingBox;


    class stopSession: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string token;
        request->getParameter("token", token);
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        string filePath = UPLOAD_DIR + activeSessions.at(sessionIndex).getFileName();
        if( remove( filePath.c_str() ) != 0 )
        {
          NVJ_LOG->append(NVJ_ERROR, "Error Deleted");
          return fromString("{\"error\":\"An error append when deleting the image\"}",response);
        }
        else
        {
          activeSessions.erase(activeSessions.begin() + sessionIndex);
          NVJ_LOG->append(NVJ_ERROR, "Deleted");
          return fromString("{\"success\":\"Goodbye\"}",response);
        }
      }
        
    } stopSession;

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
      add("uploader.txt",&uploader);
      add("index.html",&controller);
      add("getBoundingBox.txt",&getBoundingBox);
      add("stopSession.txt",&stopSession);
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

  //webServer->setUseSSL(true, "../mycert.pem");
  LocalRepository *myLocalRepo = new LocalRepository("", "../client/");
  //myLocalRepo.addDirectory("", "../client/"); 
  webServer->addRepository(myLocalRepo);

  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);

  myUploadRepo = new LocalRepository("data", "../client/data/");
  webServer->addRepository(myUploadRepo);


  webServer->startService();
 
  webServer->wait();
  
  AuthPAM::stop();
  LogRecorder::freeInstance();
  return 0;
}


