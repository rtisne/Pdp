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


string extractFontInOl(int sessionIndex, string fontName)
{
  ostringstream xmlDocument;

  xmlDocument << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><font name=\"" + fontName + "\">" << endl; 
  //string xmlDocument = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><font name=\"" + fontName + "\">";
  for(int i = 0; i < activeSessions.at(sessionIndex)->getFont()->countCharacter(); i ++)
  {
        Character* character = activeSessions.at(sessionIndex)->getFont()->characterAtIndex(i);
        xmlDocument << "<letter char=\"" +  character->getLabel() + "\">"<< endl; 
        xmlDocument << "<anchor>"<< endl; 
        xmlDocument << "<upLine>0</upLine>"<< endl; 
        xmlDocument << "<baseLine>100</baseLine>"<< endl; 
        xmlDocument << "<leftLine>0</leftLine>"<< endl; 
        xmlDocument << "<rightLine>100</rightLine>"<< endl; 
        xmlDocument << "</anchor>" << endl;

        for(int j = 0; j < character->countComposant(); j++)
        {
          int indexCC = character->getIdComposantAtIndex(j);
          ConnectedComponent* component = activeSessions.at(sessionIndex)->getImage()->getConnectedComponentAtIndex(indexCC); 
          xmlDocument << "<picture id=\"" + to_string(j) + "\">"<< endl; 
          xmlDocument << "<imageData>"<< endl; 
          xmlDocument << "<width>"+to_string((int) activeSessions.at(sessionIndex)->getImage()->getConnectedComponentAtIndex(indexCC)->getBoundingBox().getWidth() + 1)+"</width>"<< endl; 
          xmlDocument << "<height>"+to_string((int) activeSessions.at(sessionIndex)->getImage()->getConnectedComponentAtIndex(indexCC)->getBoundingBox().getHeight() + 1)+"</height>"<< endl; 
          xmlDocument << "<format>5</format>"<< endl; 
          xmlDocument << "<degradationlevel>0</degradationlevel>"<< endl; 
          xmlDocument << "<data>" + activeSessions.at(sessionIndex)->getImage()->extractDataFromComponent(indexCC) + "</data>"<< endl; 
          xmlDocument << "</imageData>"<< endl; 
          xmlDocument << "</picture>"<< endl; 
        }
        xmlDocument << "</letter>" << endl;

  }
  xmlDocument << "</font>" << endl;
  ofstream myfile;
  myfile.open ("example.of");
  myfile << xmlDocument.str();
  myfile.close();
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
  Session * mySession = new Session();
  
  srand(time(NULL));
  cptExample = rand();
  mySession->setToken(cptExample);
  mySession->setFileName((UPLOAD_DIR)+fileName);  
  activeSessions.push_back(mySession);
  mySession->getImage()->BinarizedImage();
  mySession->getImage()->extractAllConnectedComponents();

  //mySession->getImage()->extractAllConnectedComponents();
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

        Image* img = activeSessions.at(sessionIndex)->getImage();
        vector<ConnectedComponent> ListTmpCC = img->getListConnectedComponent();
        string json = "{";
        for(int i= 0; i < ListTmpCC.size()-1; i++)
        {
          BoundingBox bb = ListTmpCC[i].getBoundingBox();
          json += ("\" "+ to_string(i) +"\":{");
          json += ("\"x\":" + to_string(bb.getX().x) + ",");
          json += ("\"y\":" + to_string(bb.getX().y) + ",");
          json += ("\"width\":" + to_string(bb.getWidth()) + ",");
          json += ("\"height\":" + to_string(bb.getHeight()));
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

    class getInfoOnCC: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string token;
        string ccId;
        request->getParameter("token", token);
        request->getParameter("id", ccId);
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        ConnectedComponent cc = activeSessions.at(sessionIndex)->getImage()->getListConnectedComponent().at(stoi(ccId));
        BoundingBox bb = cc.getBoundingBox();
        int charactereId = activeSessions.at(sessionIndex)->getFont()->indexOfCharacterForCC(stoi(ccId));
        string letter = "";
        if(charactereId != -1)
          letter = activeSessions.at(sessionIndex)->getFont()->characterAtIndex(charactereId)->getLabel();
        
        string json = "{";
        json += ("\"id\":" + ccId + ",");
        json += ("\"left\":" + to_string(bb.getX().x) + ",");
        json += ("\"right\":" + to_string(bb.getX().x + bb.getWidth()) + ",");
        json += ("\"up\":" + to_string(bb.getX().y) + ",");
        json += ("\"down\":" + to_string(bb.getX().y + bb.getHeight()) + ",");
        json += ("\"letter\":\"" + letter + "\"");
        json += "}";
        return fromString(json, response);
      
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
        request->getParameter("token", token);
        request->getParameter("left", left);
        request->getParameter("right", right);
        request->getParameter("up", up);
        request->getParameter("down", down);
        request->getParameter("letter", letter);
        request->getParameter("id", listCCId);
        request->getParameter("activeid", activeId);

        int sessionIndex = getActiveSessionFromToken(stoi(token));

        auto j = json::parse(listCCId);
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
          int idCC = *it;

          if(idCC == stoi(activeId))
            activeSessions.at(sessionIndex)->getImage()->getConnectedComponentAtIndex(idCC)->setBoundingBox( BoundingBox(cv::Point2f(stof(left), stof(up)), stof(right) - stof(left), stof(down) - stof(up)));

          int indexCharacterForCC = activeSessions.at(sessionIndex)->getFont()->indexOfCharacterForCC(idCC);
          if(indexCharacterForCC != -1)
          {
            activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacterForCC)->removeComposant(
              idCC);
            if(activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacterForCC)->countComposant() <= 0)
              activeSessions.at(sessionIndex)->getFont()->removeCharacter(indexCharacterForCC);
          }
          int indexCharacter = activeSessions.at(sessionIndex)->getFont()->indexOfCharacter(letter);
          
          if(indexCharacter == -1)
            activeSessions.at(sessionIndex)->getFont()->addCharacter(Character(letter));

          indexCharacter = activeSessions.at(sessionIndex)->getFont()->indexOfCharacter(letter);

          activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacter)->addComposant(idCC);
        }
        
        // activeSessions.at(sessionIndex)->getImage()->getConnectedComponentAtIndex(stoi(ccId))->setBoundingBox( BoundingBox(cv::Point2f(stof(left), stof(up)), stof(right) - stof(left), stof(down) - stof(up)));

        
        
        


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
        string filePath = activeSessions.at(sessionIndex)->getFileName();
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

    class extractFont: public MyDynamicPage
    {
      bool getPage(HttpRequest* request, HttpResponse *response)
      {
        string token;
        request->getParameter("token", token);
        int sessionIndex = getActiveSessionFromToken(stoi(token));
        return fromString(extractFontInOl(sessionIndex, "font"),response);
      }
        
    } extractFont;

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
      add("getInfoOnCC.txt",&getInfoOnCC);
      add("updateInfoOnCC.txt",&updateInfoOnCC);
      add("stopSession.txt",&stopSession);
      add("extractFont.txt",&extractFont);
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


