#ifndef LINE_H
#define LINE_H

/**
 * \file Line.hpp
 * \brief Lines in this picture
 * \author  T.Autret, A.Boschet, T.Labrousse, R.Tisné
 * \version 1.0
 * \date Mars 2016
 *
 * Lines in this picture
 *
 */


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