#include "ConnectedComponent.hpp"

ConnectedComponent::ConnectedComponent()
{
	m_up = 0;
	m_down = 0;
	m_left = 0;
	m_right = 0;
}

ConnectedComponent::ConnectedComponent(std::vector<cv::Point> vec){
	m_listPoint = vec;
	m_up = 0;
	m_down = 0;
	m_left = 0;
	m_right = 0;
}

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

void ConnectedComponent::setOffsetBaseline(int x)
{
	m_offset_baseline = x;
}

const int ConnectedComponent::getOffsetBaseline()
{
	return m_offset_baseline;
}

const bool ConnectedComponent::getInline()
{
	return m_inline;
}

void ConnectedComponent::setInline(bool x)
{
	m_inline = x;
}

void ConnectedComponent::setBoundingBox(int up, int down, int left, int right){
	m_up = up;
	m_down = down;
	m_right = right;
	m_left = left;
}
cv::Rect ConnectedComponent::getBoundingBox(){
	if (m_up == 0 && m_down == 0 && m_left == 0 && m_right == 0)
	{
		cv::Rect bb = cv::boundingRect(m_listPoint);
		m_up = bb.y;
		m_down = bb.y + bb.height;
		m_left = bb.x;
		m_right = bb.x + bb.width;
	}
	return cv::Rect(m_left, m_up, m_right - m_left, m_down - m_up); 
}
