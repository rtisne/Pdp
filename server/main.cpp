#include "libnavajo/AuthPAM.hh"
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"

#include <time.h>
#include <signal.h> 
#include <string.h> 

#include "Image.hpp"
#include "Font.hpp"
#include "Session.hpp"
#include "json.hpp"


using namespace cv;
using namespace std;
using json = nlohmann::json;


#define UPLOAD_DIR "../client/data/"

WebServer *webServer = NULL;

LocalRepository *myUploadRepo = NULL;

std::vector<Session*> activeSessions;

void exitFunction( int dummy )
{
  for (unsigned i=0; i<activeSessions.size(); i++)
  {
    delete activeSessions.at(i);
  }
  if (webServer != NULL) webServer->stopService();
}

bool isFormatSupported( const std::string &fileName)
{
  string extension = fileName.substr(fileName.find(".") + 1);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper);
  std::map<int,string> format;

  format[1] = "JPG";
  format[2] = "JPEG";
  format[3] = "PNG";
  format[4] = "TIFF";
  format[4] = "TIF";
  
  std::map<int,string>::iterator it = format.begin();
  
  while(it != format.end())
  {
  
    if(extension.compare(it->second) == 0)
    {
      NVJ_LOG->append(NVJ_ERROR, "4");
      return true;
    }
    ++it;
  }
  NVJ_LOG->append(NVJ_ERROR, "5");
  return false;
}



string extractFontInOl(int sessionIndex, string fontName)
{
  ostringstream xmlDocument;
  xmlDocument << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl << "<font name=\"" + fontName + "\">" << endl; 
  for(int i = 0; i < activeSessions.at(sessionIndex)->getFont()->countCharacter(); i ++)
  {
    Character* character = activeSessions.at(sessionIndex)->getFont()->characterAtIndex(i);
    xmlDocument << "<letter char=\"" +  character->getLabel() + "\">"<< endl; 
    xmlDocument << "<anchor>"<< endl; 
    xmlDocument << "<upLine>0</upLine>"<< endl; 
    xmlDocument << "<baseLine>" << character->getBaseline() << "</baseLine>"<< endl; 
    xmlDocument << "<leftLine>0</leftLine>"<< endl; 
    xmlDocument << "<rightLine>100</rightLine>"<< endl; 
    xmlDocument << "</anchor>" << endl;

    for(int j = 0; j < character->countComposant(); j++)
    {
      pair<int,int> ids = character->getIdComposantAtIndex(j);
      int indexLine = ids.first;
      int indexCC = ids.second;

      ConnectedComponent component = activeSessions.at(sessionIndex)->getImage()->getConnectedComponnentAt(indexCC, indexLine); 
      xmlDocument << "<picture id=\"" + to_string(j) + "\">"<< endl; 
      xmlDocument << "<imageData>"<< endl; 
      xmlDocument << "<width>"+to_string((int) activeSessions.at(sessionIndex)->getImage()->getBoundingBoxAtIndex(indexCC, indexLine).width)+"</width>"<< endl; 
      xmlDocument << "<height>"+to_string((int) activeSessions.at(sessionIndex)->getImage()->getBoundingBoxAtIndex(indexCC, indexLine).height)+"</height>"<< endl; 
      xmlDocument << "<format>5</format>"<< endl; 
      xmlDocument << "<degradationlevel>0</degradationlevel>"<< endl; 
      xmlDocument << "<data>" + activeSessions.at(sessionIndex)->getImage()->extractDataFromComponent(indexCC, indexLine) + "</data>"<< endl; 
      xmlDocument << "</imageData>"<< endl; 
      xmlDocument << "</picture>"<< endl; 
    }
    xmlDocument << "</letter>" << endl;

  }
  xmlDocument << "</font>" << endl;
  return xmlDocument.str();
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
  Session * mySession = new Session((UPLOAD_DIR)+fileName);
  
  srand(time(NULL));
  cptExample = rand();
  mySession->setToken(cptExample);
  mySession->setFileName((UPLOAD_DIR)+fileName);  
  activeSessions.push_back(mySession);
  mySession->getImage()->ComputeMask();
  return "{\"fileName\":\""+fileName+"\",\"token\":"+to_string(mySession->getToken())+"}";
}

int getActiveSessionFromToken(int token)
{
  for (unsigned i=0; i<activeSessions.size(); i++)
  {
    Session* s = activeSessions.at(i);
    if(s->getToken() == token)
      return i;
  }
  return -1;
}



class MyDynamicRepository : public DynamicRepository
{
  class MyDynamicPage : public DynamicPage
  {    
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
      for (it=fields.begin();it!=fields.end();++it) 
      {
        if(isFormatSupported(fields[it->first]->GetFileName()))
        {
           
          if (fields[it->first]->GetType()==MPFD::Field::TextType)
            return false;
          else
          {
           
            std::string newFileName = gen_random(fields[it->first]->GetFileName().substr(fields[it->first]->GetFileName().find(".")));

            NVJ_LOG->append(NVJ_INFO, "Got file field: [" + it->first + "] Filename:[" + newFileName + "] TempFilename:["  + fields[it->first]->GetTempFileName() + "]\n");


            std::ifstream  src( fields[it->first]->GetTempFileName().c_str(), std::ios::binary);
            string dstFilename = string(UPLOAD_DIR)+newFileName;
            std::ofstream  dst( dstFilename.c_str(), std::ios::binary);
            if (!src || !dst)
              NVJ_LOG->append(NVJ_ERROR, "Copy error: check read/write permissions");
            else
              dst << src.rdbuf();
            src.close();
            dst.close();
            myUploadRepo->reload();
            std::string json_Session = InitiateSession(newFileName,request);
            NVJ_LOG->append(NVJ_ERROR, json_Session);
            return fromString(json_Session, response); 
          }
        } else {
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
      if(sessionIndex != -1)
      {
        Image* img = activeSessions.at(sessionIndex)->getImage();
        string json = "{\"boundingbox\":{" + img->jsonBoundingRect() + "},\"baseline\":{" + img->jsonBaseline() + "}}";
        return fromString(json, response);
      } else {
        return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
      }
      
    }

  } getBoundingBox;

  class getInfoOnCC: public MyDynamicPage
  {
    bool getPage(HttpRequest* request, HttpResponse *response)
    {
      string token;
      string ccId;
      string lineId;
      request->getParameter("token", token);
      request->getParameter("idCC", ccId);
      request->getParameter("idLine", lineId);
      int sessionIndex = getActiveSessionFromToken(stoi(token));
      if(sessionIndex != -1)
      {
        if(activeSessions.at(sessionIndex)->getImage()->isValidIdCC(stoi(lineId),stoi(ccId)) != -1)
        {
          int sessionIndex = getActiveSessionFromToken(stoi(token));
          cv::Rect bb = activeSessions.at(sessionIndex)->getImage()->getBoundingBoxAtIndex(stoi(ccId),stoi(lineId));
          int charactereId = activeSessions.at(sessionIndex)->getFont()->indexOfCharacterForCC(stoi(ccId),stoi(lineId));

          string letter = "";
          int baseline;
          if(charactereId != -1)
          {
            letter = activeSessions.at(sessionIndex)->getFont()->characterAtIndex(charactereId)->getLabel();
            int percent = activeSessions.at(sessionIndex)->getFont()->characterAtIndex(charactereId)->getBaseline();
            baseline = round((float)bb.y + ((float)bb.height * (float)percent / 100));
          } else {
            baseline = activeSessions.at(sessionIndex)->getImage()->getBaselineAtIndex(stoi(ccId),stoi(lineId));
          }
          string json = "{";
          json += ("\"id\":" + ccId + ",");
          json += ("\"idLine\":" + lineId + ",");
          json += ("\"baseline\":" + to_string(baseline) + ",");
          json += ("\"left\":" + to_string(bb.x) + ",");
          json += ("\"right\":" + to_string(bb.x + bb.width) + ",");
          json += ("\"up\":" + to_string(bb.y) + ",");
          json += ("\"down\":" + to_string(bb.y + bb.height) + ",");
          json += ("\"letter\":\"" + letter + "\"");
          json += "}";
          return fromString(json, response);
        } else {
          return fromString("{\"error\" : Your Line and/or id isn't valid, retry please\"}", response);
        }
      } else {
        return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
      }
      
    }

  } getInfoOnCC;    

  class updateInfoOnCC: public MyDynamicPage
  {
    bool getPage(HttpRequest* request, HttpResponse *response)
    {

      string listCCId;
      string token;
      string left;
      string right;
      string up;
      string down;
      string letter;
      string activeId;
      string activeLine;
      string baseline;
      request->getParameter("token", token);
      request->getParameter("left", left);
      request->getParameter("right", right);
      request->getParameter("up", up);
      request->getParameter("down", down);
      request->getParameter("letter", letter);
      request->getParameter("id", listCCId);
      request->getParameter("activeid", activeId);
      request->getParameter("activeline", activeLine);
      request->getParameter("baseline", baseline);

      int sessionIndex = getActiveSessionFromToken(stoi(token));
      if(sessionIndex != -1)
      {
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        auto j = json::parse(listCCId);
        for (json::iterator it = j.begin(); it != j.end(); ++it) 
        {
          int idCC = it->find("idCC")->get<int>();
          int idLine = it->find("idLine")->get<int>();
          int oldBaseline;
          if(idCC == stoi(activeId) && idLine == stoi(activeLine))
          {
            activeSessions.at(sessionIndex)->getImage()->setBoundingBoxAtIndex(idCC, idLine,stoi(up),stoi(down),stoi(left),stoi(right));
            oldBaseline = activeSessions.at(sessionIndex)->getImage()->getBaselineAtIndex(idCC, idLine);
            activeSessions.at(sessionIndex)->getImage()->setBaselineAtIndex(idCC, idLine, stoi(baseline));
          }
          int indexCharacterForCC = activeSessions.at(sessionIndex)->getFont()->indexOfCharacterForCC(idCC, idLine);
          if(indexCharacterForCC != -1)
          {
            activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacterForCC)->removeComposant(idCC, idLine);
            if(activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacterForCC)->countComposant() <= 0)
              activeSessions.at(sessionIndex)->getFont()->removeCharacter(indexCharacterForCC);
          }
          if(letter != "")
          {

            int indexCharacter = activeSessions.at(sessionIndex)->getFont()->indexOfCharacter(letter);

            if(indexCharacter == -1)
            {
              activeSessions.at(sessionIndex)->getFont()->addCharacter(Character(letter));
              indexCharacter = activeSessions.at(sessionIndex)->getFont()->indexOfCharacter(letter);
              activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacter)->setBaseline(round(((stof(baseline)-stof(up))/(stof(down) - stof(up))) * 100));
            }

            activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacter)->addComposant(idCC, idLine);

            if(stoi(baseline) != oldBaseline)
            {
              activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacter)->setBaseline(round(((stof(baseline)-stof(up))/(stof(down) - stof(up))) * 100));
            }
          }

        }
      } else {
        return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
      }
      return fromString("ok", response);
    }

  } updateInfoOnCC;

  class stopSession: public MyDynamicPage
  {
    bool getPage(HttpRequest* request, HttpResponse *response)
    {
      string token;
      request->getParameter("token", token);
      int sessionIndex = getActiveSessionFromToken(stoi(token));
      if(sessionIndex != -1)
      {
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        string filePath = activeSessions.at(sessionIndex)->getFileName();
        if( remove( filePath.c_str() ) != 0 )
        {
          NVJ_LOG->append(NVJ_ERROR, "Error Deleted");
          return fromString("{\"error\":\"An error append when deleting the image\"}",response);
        } else {
          activeSessions.erase(activeSessions.begin() + sessionIndex);
          NVJ_LOG->append(NVJ_ERROR, "Deleted");
          return fromString("{\"success\":\"Goodbye\"}",response);
        }
      } else {
        return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
      }
    }

  } stopSession;

  class extractFont: public MyDynamicPage
  {
    bool getPage(HttpRequest* request, HttpResponse *response)
    {
      string token;
      request->getParameter("token", token);
      int sessionIndex = getActiveSessionFromToken(stoi(token));
      if(sessionIndex != -1)
        { 
          int sessionIndex = getActiveSessionFromToken(stoi(token));
          string fontname;
          request->getParameter("fontname", fontname);
          return fromString(extractFontInOl(sessionIndex, fontname),response);
        } else {
          return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
        }
      }

    } extractFont;

    class updateBaseline: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string token;
        request->getParameter("token", token);
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        if(sessionIndex != -1)
        {
          int sessionIndex = getActiveSessionFromToken(stoi(token));
          string idLine;
          request->getParameter("idLine", idLine);
          if(activeSessions.at(sessionIndex)->getImage()->isValidIdLine(stoi(idLine)) != - 1)
          {
            string value;
            request->getParameter("value", value);
            activeSessions.at(sessionIndex)->getImage()->setBaselineForLine(stoi(idLine), stoi(value));
            return fromString("ok", response);
          } else { 
            return fromString("{\"error\" : You don't have a valid Line, retry please\"}", response);
          }
        } else {
          return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
        }
      }

    } updateBaseline;

    class Controller: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
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
      add("getInfoOnCC.txt",&getInfoOnCC);
      add("updateInfoOnCC.txt",&updateInfoOnCC);
      add("stopSession.txt",&stopSession);
      add("extractFont.txt",&extractFont);
      add("updateBaseline.txt",&updateBaseline);
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


