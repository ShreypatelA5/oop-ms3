

#ifndef _WORKSTATION_H
#define _WORKSTATION_H

#include <iostream>
#include <deque>

#include "Station.h"
#include "CustomerOrder.h"

using namespace std;

extern deque<sdds::CustomerOrder> g_pending;
extern deque<sdds::CustomerOrder> g_completed;
extern deque<sdds::CustomerOrder> g_incomplete;

namespace sdds
{
    class Workstation : public Station
    {
        deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation = nullptr;

    public:
        
        bool empty() const;
        Workstation(const string& str);
        bool attemptToMoveOrder();
        void fill(ostream& os);
        
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        
        Workstation& operator+=(CustomerOrder&& newOrder);
        void display(ostream& os) const;
    };
};

#endif
