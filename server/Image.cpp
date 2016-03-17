#include "Image.hpp"


Image::Image(std::string path)
{
  m_img = cv::imread(path, CV_LOAD_IMAGE_COLOR);
  m_filename = path;
  if(! m_img.data )                              // Check for invalid input
  {
    std::cout <<  "Could not open or find the image" << std::endl ;
  }
}

void Image::setImg(cv::Mat P)
{
   m_img = P;
}

const cv::Mat Image::getImg()
{
  return m_img;
}

void Image::setListLine(std::vector<Line> L)
{
  m_listLine = L;
}

const std::vector<Line> Image::getListLine()
{
  return m_listLine;
}

cv::Rect Image::getBoundingBoxAtIndex(int index,int line)
{

  std::vector<ConnectedComponent> ListTmpCC = m_listLine[line].getListCC();
  return cv::boundingRect(ListTmpCC[index].getListPoint());
}


ConnectedComponent Image::getConnectedComponnentAt(int index, int line){
  return m_listLine[line].getConnectedComponentAtIndex(index);
}

cv::Mat Image::BinarizedImage()
{
  cv::Mat m_img_bin (m_img.rows, m_img.cols, CV_8U);
  NiblackSauvolaWolfJolion (m_img, m_img_bin, WOLFJOLION);
  return m_img_bin;
}

cv::vector<ConnectedComponent> Image::extractComposentConnectImage(cv::Mat img){

  if(img.channels()>1){
    cv::cvtColor(img,img,CV_RGB2GRAY);
  }

  bitwise_not(img,img);
  cv::vector<ConnectedComponent> tmpCC;
  cv::vector<cv::vector<cv::Point>> contours;
  cv::findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
  for(int i =0; i< contours.size();i++){
    ConnectedComponent cc = ConnectedComponent(contours[i]);
    tmpCC.push_back(cc);
  }
  return tmpCC;
}

int Image::getCharacterHeight(cv::Mat img){
    /* Returns the median height of a character in a given binary image */
  if(img.empty())
    return false;
  else if(img.channels()>1){
    cv::cvtColor(img,img,CV_RGB2GRAY);
  }
    // Smooth the image to remove unwanted noise from extracted CCs
    cv::medianBlur(img,img,9);

    bitwise_not(img,img);

    // CCs extraction
    cv::vector<cv::vector<cv::Point> > contours;
    cv::findContours(img, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS);
    // We sort the array with respect to their height
    sort(contours.begin(), contours.end(), [](const cv::vector<cv::Point>& c1, const cv::vector<cv::Point>& c2){
        return cv::boundingRect(c1).height < cv::boundingRect(c2).height;
    });


    // Merely return the median's height
    int median = (int)contours.size()/2;
    return cv::boundingRect(contours[median]).height; 
}

void Image::ComputeMask()
{   
  BinarizedImage().copyTo(m_img);
  int character_height = getCharacterHeight(m_img.clone());

  cv::Mat tmp;

  // horizontal blur
  cv::blur(m_img,tmp,cv::Size(5*character_height,0.5*character_height));

  // binarization + median filtering
  cv::threshold(tmp,tmp,190,255,1);
  if(tmp.empty())
    return;
  else if(tmp.channels()>1){
    cv::cvtColor(tmp,tmp,CV_RGB2GRAY);
  }
 
  cv::medianBlur(tmp,tmp,9);
  cv::vector<cv::vector<cv::Point>> contours_mask;
  cv::findContours(tmp, contours_mask, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS);
  cv::vector<ConnectedComponent> tmpCC = extractComposentConnectImage(m_img.clone());

  for(int i = 0 ; i < contours_mask.size(); i++)
  {
    Line line = Line();
    cv::Rect rMask = cv::boundingRect(contours_mask[i]);
    cv::vector<ConnectedComponent>::iterator itr = tmpCC.begin();
      for(int k = tmpCC.size()-1; k >= 0;k--)
      {
          cv::Rect r = cv::boundingRect(tmpCC[k].getListPoint());
          if(CompareBB(rMask,r) == true && tmpCC[k].getInline() == false)
          {
            line.addCC(tmpCC[k]);
            tmpCC[k].setInline(true);
          }
        }  
      m_listLine.push_back(line);
  }

  Line line = Line();
  for(int i = 0; i < tmpCC.size(); i++)
  {
    if(tmpCC[i].getInline() == false){line.addCC(tmpCC[i]);}
  }
  m_listLine.push_back(line);
}

std::string Image::jsonBoundingRect(){
  std::string json;
  int id = 0;
  for(int line = 0 ; line < m_listLine.size(); line++)
  {
    std::vector<ConnectedComponent> ListTmpCC = m_listLine[line].getListCC();
    for(int i = 0; i < ListTmpCC.size(); i++)
    {
      cv::Rect rect = cv::boundingRect(ListTmpCC[i].getListPoint());
      json += ("\""+ std::to_string(id) +"\":{");
      json += ("\"idCC\":" + std::to_string(i) + ",");
      json += ("\"idLine\":" + std::to_string(line) + ",");
      json += ("\"x\":" + std::to_string(rect.x) + ",");
      json += ("\"y\":" + std::to_string(rect.y) + ",");
      json += ("\"width\":" + std::to_string(rect.width) + ",");
      json += ("\"height\":" + std::to_string(rect.height));
      json += ("}");
      json += (",");
      id++;
    }
  }
  std::cout << "nb objet" << id << std::endl;
  json = json.substr(0, json.size()-1);
  return json;
}


const std::string Image::extractDataFromComponent(int index, int lineId)
{

  cv::Mat img = cv::imread(m_filename, CV_LOAD_IMAGE_COLOR);
  if(! img.data )                              // Check for invalid input
  {
    std::cout <<  "Could not open or find the image" << std::endl ;
  }

  std::string data;
  int rows = img.rows;
  int cols = img.cols;
  cv::Rect bb = getBoundingBoxAtIndex(index, lineId);
  for (int i=bb.y; i<=bb.y+bb.height; ++i) {
    cv::Vec3b *p = img.ptr<cv::Vec3b>(i);
    for (int j=bb.x; j<=bb.x+bb.width; ++j) {
      const cv::Vec3b pix = p[j];
      unsigned char opacity = 255;
      unsigned int v = (opacity<<24)|(pix[0]<<16)|(pix[1]<<8)|(pix[2]);
      std::cout << pix << std::endl;
      data += std::to_string(v);
      data += ",";

    }
  }
  return data.substr(0, data.size()-1);
} 


bool Image::CompareBB(cv::Rect bb1, cv::Rect bb2)
{
  int x_bb1 = std::max(bb1.x,bb2.x);
  int x_bb2 = std::max(bb1.y,bb2.y);
  int y_bb1 = std::min(bb1.x + bb1.width,bb2.x + bb2.width);
  int y_bb2 = std::min(bb1.y + bb1.height,bb2.y + bb2.height);

  if(x_bb1 < y_bb1 && x_bb2 < y_bb2)
  {
    return true;
  }
  return false;
}

