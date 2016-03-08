#include "Image.hpp"


Image::Image(std::string path)
{
   m_img = cv::imread(path, CV_LOAD_IMAGE_COLOR);
}

void Image::setImg(cv::Mat P)
{
   m_img = P;
}

const cv::Mat Image::getImg()
{
	return m_img;
}

void Image::setListConnectedComponent(std::vector<ConnectedComponent> L)
{
  m_listConnectedComponent = L;
}

const std::vector<ConnectedComponent> Image::getListConnectedComponent()
{
	return m_listConnectedComponent;
}

void Image::setListLine(std::vector<Line> L)
{
  m_listLine = L;
}

const std::vector<Line> Image::getListLine()
{
  return m_listLine;
}

void Image::BinarizedImage()
{
  NiblackSauvolaWolfJolion (m_img, m_img, WOLFJOLION);
  // Create a window

}

void Image::ImgMask()
{
 cv::blur(m_img,m_mask,cv::Size(105,5));

 cv::threshold(m_mask, m_mask,170,255,1);

 cv::medianBlur(m_mask, m_mask,9);

 cv::namedWindow("foobar");
 
// Display image in window
cv::imshow("foobar", m_mask);
 
// Wait for user to press a key in window
cv::waitKey(0);
}

void Image::extractConnectedComponent(cv::Mat &input,const cv::Point &seed,ConnectedComponent &cc)
{
  //assert(input.type() == CV_8U);
  assert(seed.x < input.cols && seed.y < input.rows && seed.x >= 0 && seed.y >= 0);
  std::vector<cv::Point> ListTmp;
  ListTmp = cc.getListPoint();
  ListTmp.clear();
  cc.setListPoint(ListTmp);

  std::deque<cv::Point> ptsQueue;
  uchar &pixS = input.at<unsigned char>(seed.y, seed.x);
  if (pixS != BACKGROUND) {
    ptsQueue.push_back(seed);
    pixS = BACKGROUND;
  }    

  while (! ptsQueue.empty()) {

    cv::Point current = ptsQueue.front();
    ptsQueue.pop_front();

    ListTmp = cc.getListPoint();
    ListTmp.push_back(current);
    cc.setListPoint(ListTmp);

    // enque neighboors
    const cv::Point e(current.x + 1, current.y);
    const cv::Point w(current.x - 1, current.y);
    const cv::Point n(current.x, current.y - 1);
    const cv::Point s(current.x, current.y + 1);
    if (n.y >= 0) {
      uchar &pix = input.at<unsigned char>(n.y, n.x);
      if (pix != BACKGROUND) {
        ptsQueue.push_back(n);
    pix = BACKGROUND;
      }
    }
    if (e.x < input.cols) {
      uchar &pix = input.at<unsigned char>(e.y, e.x);
      if (pix != BACKGROUND) {
        ptsQueue.push_back(e);
        pix = BACKGROUND;
      }
    }
    if (s.y < input.rows) {
      uchar &pix = input.at<unsigned char>(s.y, s.x);
      if (pix != BACKGROUND) {
        ptsQueue.push_back(s);
        pix = BACKGROUND;
      }
    }
    if (w.x >= 0) {
      uchar &pix = input.at<unsigned char>(w.y, w.x);
      if (pix != BACKGROUND) {
        ptsQueue.push_back(w);
        pix = BACKGROUND;
      }
    }
  }
  
}

void Image::extractAllConnectedComponents()
{
  //assert(Img.type() == CV_8U);

  m_listConnectedComponent.clear();
  m_listConnectedComponent.reserve(m_img.rows); //arbitrary

  cv::Mat tmp = m_img.clone();

  ConnectedComponent cc;

  for (int i = 0; i < m_img.rows; ++i) {
    const uchar *r = tmp.ptr<uchar>(i);
    for (int j = 0; j < m_img.cols; ++j) {
      if (r[j] != BACKGROUND) {
        std::vector<cv::Point> ListTmp;
        ListTmp = cc.getListPoint();
        ListTmp.clear();
        cc.setListPoint(ListTmp);
        extractConnectedComponent(tmp, cv::Point(j, i), cc);
        cc.initBase();
        m_listConnectedComponent.push_back(cc);
      }
    }
  }

}



void Image::putInLine()
{
 int max = 0;

 // set Max value
 for(int i= 0; i < m_listConnectedComponent.size()-1; i++)
  {
     if (m_listConnectedComponent[i].getBoundingBox().getHeight()  > max)
     {
       max = m_listConnectedComponent[i].getBoundingBox().getHeight();
     }

  }

 Line * L = new Line();

 for(int i= 0; i < m_listConnectedComponent.size()-1; i++)
  {
    L->addConnectedComponent(m_listConnectedComponent[i]);

     if (m_listConnectedComponent[i+1].getBase() - m_listConnectedComponent[i].getBase() > max)
     {
        m_listLine.push_back(*L);
        L = new Line();
     }
  }

  //inialization all Baseline of Image
 for(int i= 0; i < m_listLine.size()-1; i++)
  {
      m_listLine[i].computeBaseline();
  }


}



