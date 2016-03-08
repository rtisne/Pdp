#ifndef LINE_H
#define LINE_H

#include "ConnectedComponent.hpp"

class Line
{
public:
    Line();
    void computeBaseline();
    void setBaseline(int x);
    const int getBaseline();
    void setListConnectedComponent(std::vector<ConnectedComponent> cc);
    const std::vector<ConnectedComponent> getListConnectedComponent();
    void addConnectedComponent(ConnectedComponent cc);
private:
   	int m_baseline;
   	std::vector<ConnectedComponent> m_listConnectedComponent;
};

#endif // LINE__H