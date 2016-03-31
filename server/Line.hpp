#ifndef LINE_H
#define LINE_H

#include "ConnectedComponent.hpp"

class Line
{
public:
    Line();
  	void setBaseline(int x);
  	int getBaseline() const;
  	std::vector<ConnectedComponent> getListCC() const;
  	void addCC(const ConnectedComponent &cc);
  	ConnectedComponent getConnectedComponentAtIndex(int index) const;
  	void setBoundingBoxAtIndex(int index, int up, int down, int left, int right);
  	void setBaselineAtIndex(int index, int value);
    void computeBaseLine();

private:
  std::vector<ConnectedComponent> m_ListCC;
  int m_baseline;
};

#endif // LINE__H