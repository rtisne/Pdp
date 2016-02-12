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


void ConnectedComponent::initBB()
{
	
}

int ConnectedComponent::sizeListP()
{
	return ListP.size();
}
