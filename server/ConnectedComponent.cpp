#include "ConnectedComponent.hpp"

ConnectedComponent::ConnectedComponent()
{}

void ConnectedComponent::setListPoint(std::vector<cv::Point> L)
{
  m_listPoint = L;
}

const std::vector<cv::Point> ConnectedComponent::getListPoint()
{
  return m_listPoint;
}

int ConnectedComponent::sizeListP()
{
	return m_listPoint.size();
}

void ConnectedComponent::initBoundingBox()
{
	cv::Point P_Max;
	 P_Max.x = m_listPoint[0].x;
	 P_Max.y = m_listPoint[0].y;
	cv::Point P_Min;
	 P_Min.x = m_listPoint[0].x;
	 P_Min.y = m_listPoint[0].y;
          for(int i= 1; (unsigned)i < m_listPoint.size()-1; i++)
            {
                  cv::Point P = m_listPoint[i];
                  if(P.y < P_Min.y && P.x < P_Min.x)
                  {
                  	P_Min.y = P.y;
                  	P_Min.x = P.x;
                  }

                 if(P.y > P_Max.y && P.x > P_Max.x)
                  {
                  	P_Min.y = P.y;
                  	P_Min.x = P.x;
                  }


            }

    m_boundingBox.setX(P_Max);
    m_boundingBox.setHeight(P_Max.y - P_Min.y);
    m_boundingBox.setWidth(P_Max.x - P_Min.x);
}

BoundingBox ConnectedComponent::getBoundingBox()
{
  return m_boundingBox;
}

void ConnectedComponent::initCharacter(std::string name)
{
  m_char.setLabel(name);

   int base;
   base = m_listPoint[0].y;
          for(int i= 1; (unsigned)i < m_listPoint.size()-1; i++)
            {
              cv::Point P = m_listPoint[i];
              if(P.y > base)
               {
                 base = P.y;
               }
            }
  m_char.setBase(base);

}

void ConnectedComponent::initBase()
{
   int baseTmp;
   baseTmp = m_listPoint[0].y;
          for(int i= 1; (unsigned)i < m_listPoint.size()-1; i++)
            {
              cv::Point P = m_listPoint[i];
              if(P.y > baseTmp)
               {
                 baseTmp = P.y;
               }
            }
  m_base = baseTmp;

}

void ConnectedComponent::setCharacter(Character c)
{
   m_char = c;
}

Character ConnectedComponent::getCharacter()
{
  return m_char;
}

void ConnectedComponent::setBase(int x)
{
  m_base = x;
}

const int ConnectedComponent::getBase()
{
  return m_base;
}