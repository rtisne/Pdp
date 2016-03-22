#ifndef LINE_H
#define LINE_H

#include "ConnectedComponent.hpp"

class Line
{
public:
    Line();
  	void setBaseline(int x);
  	const int getBaseline();
  	void setListCC(std::vector<ConnectedComponent> cc);
  	const std::vector<ConnectedComponent> getListCC();
  	void addCC(ConnectedComponent cc);
  	ConnectedComponent getConnectedComponentAtIndex(int index);
  	void setBoundingBoxAtIndex(int index, int up, int down, int left, int right);
    void computeBaseLine();

private:
  std::vector<ConnectedComponent> m_ListCC;
  int m_baseline;
};

#endif // LINE__H