#ifndef LINE_H
#define LINE_H

#include "ConnectedComponent.hpp"

class Line
{
public:
    Line();
    void initBaseline();
    void setBaseline(int y);
    int getBaseline();
    void setListCC(std::vector<ConnectedComponent> L);
    std::vector<ConnectedComponent> getListCC();
    void addConnectedComponent(ConnectedComponent cc);
private:
   	int Baseline;
   	std::vector<ConnectedComponent> ListCC;
};

#endif // LINE__H