#include "libnavajo/AuthPAM.hh"
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"

#include <time.h>
#include <signal.h> 
#include <string.h> 
#include <unordered_set>

#include "../headers/Image.hpp"
#include "../headers/Font.hpp"
#include "../headers/Session.hpp"
#include "../headers/json.hpp"


using namespace cv;
using namespace std;
using json = nlohmann::json;



#define CLIENT_DIR "../client/"
#define UPLOAD_DIR "../client/data/"

const int rng = 10;

WebServer *webServer = NULL;

LocalRepository *myUploadRepo = NULL;

std::vector<Session*> activeSessions;

/*
* \brief Function use when the service is closed and killed the active session
*
* \param dummy : the dummy as integer 
*/

void exitFunction( int dummy )
{
  for (unsigned i=0; i<activeSessions.size(); i++)
  {
    delete activeSessions.at(i);
  }
  if (webServer != NULL) webServer->stopService();
}

/*
* \brief Verify if the format's image uploaded is supported 
*
* \param &filenane : the filename as string 
*
* \return a bool
*/

bool isFormatSupported( const std::string &fileName)
{
  string extension = fileName.substr(fileName.find(".") + 1);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper);
  std::unordered_set<std::string> format ={"JPG","JPEG","PNG","TIFF","TIF"};
  std::unordered_set<std::string>::const_iterator got = format.find(extension);
  for(const auto &s: format){
    if(got == format.end())
      return false;
    else
      return true;
  }
  return false;
}


/*
* \brief Extract all informations about the font  
*
* \param sessionindex : the index as integeer
* \param fontname : the fontname as string 
*
* \return a string
*/
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

    for(int j = 0; j < character->countComponent(); j++)
    {
      pair<int,int> ids = character->getIdComponentAtIndex(j);
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

/*
* \brief Generate a random name for image uploaded 
*
* \param extension : the extension as string
*
* \return a string
*/
std::string gen_random(std::string extension) {
  static const char letter[] =
  "0123456789"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz";
  srand(time(NULL));    
  string random;
  for (int i = 0; i < rng; ++i) {
    random += letter[rand() % (sizeof(letter))];
  }

  return random + extension;
}

/*
* \brief Creater User session when image was uploading
*
* \param filenane : the filename as string 
* \param *request : the request as HttpRequest
*
* \return a string JSON
*/

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

/*
* \brief Verify if token is valid
*
* \param token : the token as integer
*
* \return a integer
*/
int getActiveSessionFromToken(int token)
{
  for (unsigned i=0; i<activeSessions.size(); i++)
  {
    const Session *s = activeSessions.at(i);
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

      // retrieval of the image
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


            std::ifstream  src(fields[it->first]->GetTempFileName().c_str(), std::ios::binary);
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
    /*
    * \brief Extract all bounding box and baseline
    *
    * \param *response : the response as HttpReponse 
    * \param *request : the request as HttpRequest
    *
    * \return a string in response and a bool
    */
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
    /*
    * \brief Get informations about a bounding box
    *
    * \param *response : the response as HttpReponse 
    * \param *request : the request as HttpRequest
    *
    * \return a string in response and a bool
    */
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
    /*
    * \brief Update informations about a bounding box
    *
    * \param *response : the response as HttpReponse 
    * \param *request : the request as HttpRequest
    *
    * \return a string in response and a bool
    */
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
        // For each component connexe
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
            activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacterForCC)->removeComponent(idCC, idLine);
            if(activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacterForCC)->countComponent() <= 0)
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

            activeSessions.at(sessionIndex)->getFont()->characterAtIndex(indexCharacter)->addComponent(idCC, idLine);

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
      /*
      * \brief Update informations about a baseline
      *
      * \param *response : the response as HttpReponse 
      * \param *request : the request as HttpRequest
      *
      * \return a string in response and a bool
      */
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

/*
* \author Provided by Thierry DESCOMBES, Creator of Libnavajo Server
*/
  int main(int argc, char** argv )
  {
    signal( SIGTERM, exitFunction );
    signal( SIGINT, exitFunction );

    NVJ_LOG->addLogOutput(new LogStdOutput);
    AuthPAM::start(); 
    webServer = new WebServer;

  //webServer->setUseSSL(true, "../mycert.pem");
    LocalRepository *myLocalRepo = new LocalRepository("", CLIENT_DIR);
  //myLocalRepo.addDirectory("", "../client/"); 
    webServer->addRepository(myLocalRepo);

    MyDynamicRepository myRepo;
    webServer->addRepository(&myRepo);

    myUploadRepo = new LocalRepository("data", UPLOAD_DIR);
    webServer->addRepository(myUploadRepo);


    webServer->startService();

    webServer->wait();

    AuthPAM::stop();
    LogRecorder::freeInstance();
    return 0;
  }


