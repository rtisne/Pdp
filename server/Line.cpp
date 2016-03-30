#include "Line.hpp"

Line::Line():m_baseline(0){

}

void Line::setBaseline(int y)
{
	for(std::vector<ConnectedComponent>::iterator it = m_ListCC.begin(); it != m_ListCC.end(); ++it)
		if(it->getBaseline() == m_baseline)
    	it->setBaseline(y);
  m_baseline = y;
}

const int Line::getBaseline() const
{
  return m_baseline;
}

void Line::addCC(ConnectedComponent cc)
{
  m_ListCC.push_back(cc);
}

const std::vector<ConnectedComponent> Line::getListCC() const
{
  return m_ListCC;
}

ConnectedComponent Line::getConnectedComponentAtIndex(int index){
	return m_ListCC.at(index);
}

void Line::setBoundingBoxAtIndex(int index, int up, int down, int left, int right){
	m_ListCC[index].setBoundingBox(up, down, left, right);
}

void Line::computeBaseLine(){
	sort(m_ListCC.begin(), m_ListCC.end(), [](ConnectedComponent &c1, ConnectedComponent &c2){
        return cv::boundingRect(c1.getListPoint()).x < cv::boundingRect(c2.getListPoint()).x;
    });

  int median = (int)m_ListCC.size()/2;
  cv::Rect bb = cv::boundingRect(m_ListCC[median].getListPoint());
  setBaseline(bb.y + bb.height);
	for(int unsigned i=0;i<m_ListCC.size();i++)
	{
		m_ListCC[i].setBaseline(bb.y + bb.height);
	} 
}

void Line::setBaselineAtIndex(int index, int value)
{
	m_ListCC[index].setBaseline(value);
}
