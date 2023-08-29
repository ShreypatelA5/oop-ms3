// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

using namespace sdds;
using namespace std;

deque<CustomerOrder> g_pending{};
deque<CustomerOrder> g_completed{};
deque<CustomerOrder> g_incomplete{};

Workstation::Workstation(const string &str) : Station{str}
{
    // Empty
}

void Workstation::fill(ostream &os)
{
    if (!m_orders.empty())
    {
        m_orders.front().fillItem(*this, os);
    }
}

bool Workstation::attemptToMoveOrder()
{
    if (m_orders.empty())
    {
        return true;
    }
    else
    {
        if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0)
        {
            if (m_pNextStation == nullptr)
            {
                if (m_orders.front().isOrderFilled())
                {
                    g_completed.emplace_back(move(m_orders.front()));
                }
                else
                {
                    g_incomplete.emplace_back(move(m_orders.front()));
                }
            }
            else
            {
                (*m_pNextStation) += move(m_orders.front());
            }
            m_orders.pop_front();
            return true;
        }
        return false;
    }
}

Workstation *Workstation::getNextStation() const
{
    return m_pNextStation;
}

void Workstation::setNextStation(Workstation *station)
{
    m_pNextStation = station;
}

void Workstation::display(ostream &os) const
{
    os << getItemName();
    os << " --> ";

    if (m_pNextStation == nullptr)
    {
        os << "End of Line";
    }
    else
    {
        os << m_pNextStation->getItemName();
    }
    os << endl;
}

bool Workstation::empty() const
{
    return m_orders.empty();
}

Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
{
    m_orders.emplace_back(move(newOrder));
    return *this;
}
