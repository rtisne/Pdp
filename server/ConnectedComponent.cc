#include "ConnectedComponent.h"



ConnectedComponent::ConnectedComponent()
{

}

void ConnectedComponent::setListP(std::vector<cv::Point> L)
{
  ListP = L;
}

std::vector<cv::Point> ConnectedComponent::getListP()
{
  return ListP;
}



int ConnectedComponent::sizeListP()
{
	return ListP.size();
}

void ConnectedComponent::initBoundingBox()
{
	cv::Point P_Max;
	 P_Max.x = ListP[0].x;
	 P_Max.y = ListP[0].y;
	cv::Point P_Min;
	 P_Min.x = ListP[0].x;
	 P_Min.y = ListP[0].y;
          for(int i= 1; (unsigned)i < ListP.size()-1; i++)
            {
                  cv::Point P = ListP[i];
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

    BB.setX(P_Max);
    BB.setY(P_Min);
}

void ConnectedComponent::initCharacter(std::string name)
{
  C.setLabel(name);

   int Base;
   Base = ListP[0].y;
          for(int i= 1; (unsigned)i < ListP.size()-1; i++)
            {
              cv::Point P = ListP[i];
              if(P.y > Base)
               {
                 Base = P.y;
               }
            }
  C.setBase(Base);

}