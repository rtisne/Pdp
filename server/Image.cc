#include "Image.h"

#include <deque>

Image::Image(std::string path)
{
   Img = cv::imread(path, CV_LOAD_IMAGE_COLOR);
}

void Image::setImg(cv::Mat P)
{
   Img = P;
}

cv::Mat Image::getImg()
{
	return Img;
}

void Image::setListCC(std::vector<ConnectedComponent> L)
{
  ListCC = L;
}

std::vector<ConnectedComponent> Image::getListCC()
{
	return ListCC;
}

void Image::BinarizedImage()
{
  cv::Mat Image_Bin;

  //Passage en niveau de gris
  cv::Mat mat_gray;
  if (Img.channels() == 3) 
    cv::cvtColor(Img, mat_gray, cv::COLOR_BGR2GRAY);
  else 
    mat_gray = Img;

  //we get 0 where there is black, 255 where there is white.

  cv::threshold(mat_gray, Image_Bin, 0, 255, cv::THRESH_OTSU);
  
  Img = Image_Bin;
}

void Image::extractConnectedComponent(cv::Mat &input,const cv::Point &seed,ConnectedComponent &cc)
{
  assert(input.type() == CV_8U);
  assert(seed.x < input.cols && seed.y < input.rows && seed.x >= 0 && seed.y >= 0);
  std::vector<cv::Point> ListTmp;
  ListTmp = cc.getListP();
  ListTmp.clear();
  cc.setListP(ListTmp);

  std::deque<cv::Point> ptsQueue;
  uchar &pixS = input.at<unsigned char>(seed.y, seed.x);
  if (pixS != BACKGROUND) {
    ptsQueue.push_back(seed);
    pixS = BACKGROUND;
  }    

  while (! ptsQueue.empty()) {

    cv::Point current = ptsQueue.front();
    ptsQueue.pop_front();

    ListTmp = cc.getListP();
    ListTmp.push_back(current);
    cc.setListP(ListTmp);

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
  assert(Img.type() == CV_8U);

  ListCC.clear();
  ListCC.reserve(Img.rows); //arbitrary

  cv::Mat tmp = Img.clone();

  ConnectedComponent cc;

  for (int i = 0; i < Img.rows; ++i) {
    const uchar *r = tmp.ptr<uchar>(i);
    for (int j = 0; j < Img.cols; ++j) {
      if (r[j] != BACKGROUND) {
        std::vector<cv::Point> ListTmp;
        ListTmp = cc.getListP();
        ListTmp.clear();
        cc.setListP(ListTmp);
        extractConnectedComponent(tmp, cv::Point(j, i), cc);
        cc.initBase(); //modify tmp
        ListCC.push_back(cc);
      }
    }
  }

}

void Image::putInLine()
{

  Line * L = new Line();
  L->addConnectedComponent(ListCC[0]);
  int maxEcart = 0;

  for(int i= 1; i < ListCC.size()-1; i++)
    {
      if (ListCC[i].getBoundingBox().getHeight()  >= maxEcart)
      {
        maxEcart = ListCC[i].getBoundingBox().getHeight();
      }
      if(ListCC[i].getBase > ListCC[i+1].getBase)
        ListLine.push_back(L);
        Line * L2 = new Line();

      }
    }

}

