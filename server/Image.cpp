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
  return ListTmpCC[index].getBoundingBox();
}
void Image::setBoundingBoxAtIndex(int index,int line, int up, int down, int left, int right)
{
  m_listLine[line].setBoundingBoxAtIndex(index, up, down, left, right);
}


ConnectedComponent Image::getConnectedComponnentAt(int index, int line){
  return m_listLine[line].getConnectedComponentAtIndex(index);
}

cv::Mat Image::BinarizedImage()
{
  cv::Mat m_img_bin (m_img.rows, m_img.cols, CV_8U);
  NiblackSauvolaWolfJolion (m_img, m_img_bin, WOLFJOLION);
  return m_img_bin;
  m_img_bin.release();
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
    cv::medianBlur(img,img,7);
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
  cv::Mat binarize; 
  BinarizedImage().copyTo(binarize);
  int character_height = getCharacterHeight(binarize.clone());

  cv::Mat tmp;

  // horizontal blur
  cv::blur(binarize,tmp,cv::Size(5*character_height,0.5*character_height));
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
  cv::vector<ConnectedComponent> tmpCC = extractComposentConnectImage(binarize.clone());
  sort(tmpCC.begin(), tmpCC.end(), []( ConnectedComponent& c1, ConnectedComponent& c2){
        return cv::boundingRect(c1.getListPoint()).x < cv::boundingRect(c2.getListPoint()).x;
    });

  sort(contours_mask.begin(), contours_mask.end(), [](const cv::vector<cv::Point>& c1, const cv::vector<cv::Point>& c2){
        return cv::boundingRect(c1).y < cv::boundingRect(c2).y;
    });
  int nbCCInline = 0;
  if(contours_mask.size() != 0)
  {
    for(int i = 0 ; i < contours_mask.size(); i++)
    {
      Line line = Line();
      cv::Rect rMask = cv::boundingRect(contours_mask[i]);
        for(int k = 0; k < tmpCC.size();k++)
        {
          cv::Rect r = cv::boundingRect(tmpCC[k].getListPoint());
          if(tmpCC[k].getInline() == false)
            {
            if(inMiddle(rMask,r) || rMask.contains(r.tl()) || rMask.contains(r.br()))
              {
                line.addCC(tmpCC[k]);
                tmpCC[k].setInline(true);
                nbCCInline++;
              }
            }  
        }  
        m_listLine.push_back(line);
        if(m_listLine[i].getListCC().size() != 0)
          {
            m_listLine[i].computeBaseLine();
          }     
    }
  } else if(tmpCC.size() == 1){
    Line line = Line();
    line.addCC(tmpCC[0]);
    nbCCInline++;
    m_listLine.push_back(line);
    m_listLine[0].computeBaseLine();
  }
  if(nbCCInline != tmpCC.size())
  {
  Line line = Line();
  for(int i = 0; i < tmpCC.size() ; i++){
    if(tmpCC[i].getInline() == false)
    line.addCC(tmpCC[i]);
    }
  m_listLine.push_back(line);
  }
  
  tmp.release();
  binarize.release();
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
  ListTmpCC.clear();
  }

  json = json.substr(0, json.size()-1);
  return json;
}

std::string Image::jsonBaseline(){
  std::string json;
  for(int line = 0 ; line < m_listLine.size(); line++)
  {
    if(m_listLine[line].getListCC().size() != 0)
    {
      std::vector<ConnectedComponent> ListTmpCC = m_listLine[line].getListCC();
      cv::Rect cc_begin = cv::boundingRect(ListTmpCC[0].getListPoint());
      cv::Rect cc_end = cv::boundingRect(ListTmpCC[ListTmpCC.size()-1].getListPoint());
      json += ("\"" + std::to_string(line) +"\":{");
      json += ("\"idLine\":" + std::to_string(line) + ",");
      json += ("\"x_begin\":" + std::to_string(cc_begin.x) + ",");
      json += ("\"x_end\":" + std::to_string(cc_end.x + cc_end.width) + ",");
      json += ("\"y_baseline\":" + std::to_string(m_listLine[line].getBaseline()));
      json += ("}");
      json += (",");
      ListTmpCC.clear();
    }
  }
  json = json.substr(0, json.size()-1);
  return json;
}


const std::string Image::extractDataFromComponent(int index, int lineId)
{

  cv::Mat imgBinarized; 
  BinarizedImage().copyTo(imgBinarized);

  std::string data;
  int rows = m_img.rows;
  int cols = m_img.cols;
  cv::Rect bb = getBoundingBoxAtIndex(index, lineId);
  for (int i=bb.y; i<=bb.y+bb.height; ++i) {
    cv::Vec3b *p = m_img.ptr<cv::Vec3b>(i);
    cv::Vec3b *pB = imgBinarized.ptr<cv::Vec3b>(i);
    for (int j=bb.x; j<=bb.x+bb.width; ++j) {
      unsigned int v;
      const cv::Vec3b pix = p[j];
      const cv::Vec3b pixB = pB[j];
      unsigned char opacity = 255;
      // if(pixB[0] == 255 && pixB[1] == 255 && pixB[2] == 255)
      //   v = (0<<24)|(255<<16)|(255<<8)|(255);
      // else
        v = (opacity<<24)|(pixB[0]<<16)|(pixB[1]<<8)|(pixB[2]);
  
      data += std::to_string(v);
      data += ",";

    }
  }
  imgBinarized.release();
  return data.substr(0, data.size()-1);
} 

bool Image::inMiddle(cv::Rect bb1, cv::Rect bb2)
{
  int bb2_x = bb2.x + (bb2.width/2);
  int bb2_y = bb2.y + (bb2.height/2);
  int bb1_x_max = bb1.x + bb1.width + 3;
  int bb1_y_max = bb1.y + bb1.height + 3;
  if((bb1.x) <= bb2_x && bb2_x <= bb1_x_max && (bb1.y) <= bb2_y &&  bb2_y <= bb1_y_max)
  {
    return true;
  }
  return false;
}

void Image::setBaselineForLine(int id, int value)
{
  m_listLine[id].setBaseline(value);
}
