// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>

#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
using namespace sdds;

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() : m_name{},
                                 m_product{},
                                 m_countItem{},
                                 m_listItem{nullptr}
{
}

CustomerOrder::CustomerOrder(const string &input)
{
    Utilities util;
    size_t npos = 0;
    bool more = true;

    m_name = util.extractToken(input, npos, more);
    m_product = util.extractToken(input, npos, more);

    string listOfItems = "";
    size_t count = 0;

    do
    {
        string tmp = util.extractToken(input, npos, more);
        if (listOfItems.length() > 0)
        {
            listOfItems += Utilities::getDelimiter();
        }
        listOfItems += tmp;
        count++;
    } while (more);

    m_listItem = new Item *[count];
    m_countItem = count;
    
    npos = 0;
    count = 0;
    more = true;

    do
    {
        string tmp = util.extractToken(listOfItems, npos, more);
        m_listItem[count++] = new Item(tmp);
    } while (more);

    if (m_widthField < util.getFieldWidth())
    {
        m_widthField = util.getFieldWidth();
    }
}

CustomerOrder::CustomerOrder(CustomerOrder &&order) noexcept : m_name{}, m_product{}, m_countItem{}, m_listItem{nullptr}
{
    *this = move(order);
}

CustomerOrder::CustomerOrder(const CustomerOrder &order)
{
    throw string("Copy constructor cannot be called");
}


CustomerOrder::~CustomerOrder()
{
    for (size_t i = 0; i < m_countItem; i++)
    {
        delete m_listItem[i];
    }

    delete[] m_listItem;
}

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&order) noexcept
{
    if (this == &order)
    {
        return *this;
    }

    swap(m_name, order.m_name);
    swap(m_product, order.m_product);
    swap(m_countItem, order.m_countItem);
    swap(m_listItem, order.m_listItem);

    return *this;
}

bool CustomerOrder::isItemFilled(const string &itemName) const
{
    size_t itemCount = 0;
    size_t filledCount = 0;

    for (size_t i = 0; i < m_countItem; i++)
    {
        if (m_listItem[i]->m_itemName == itemName)
        {
            itemCount++;

            if (m_listItem[i]->m_isFilled)
            {
                filledCount++;
            }
        }
    }

    return itemCount == filledCount;
}

bool CustomerOrder::isOrderFilled() const
{
    size_t count = 0;

    for (size_t i = 0; i < m_countItem; i++)
    {
        if (m_listItem[i]->m_isFilled)
        {
            count++;
        }
    }

    return count == m_countItem;
}

void CustomerOrder::fillItem(Station &station, ostream &os)
{
    for (size_t i = 0; i < m_countItem; i++)
    {

        if (m_listItem[i]->m_isFilled == false && m_listItem[i]->m_itemName == station.getItemName())
        {

            if (station.getQuantity() > 0)
            {
                m_listItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_listItem[i]->m_isFilled = true;
                station.updateQuantity();
                os << setw(11) << right;
                os << "Filled " << m_name << ", " << m_product << " [" << m_listItem[i]->m_itemName << "]" << endl;
                break;
            }
            else
            {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_listItem[i]->m_itemName << "]" << endl;
            }
        }
    }
}

void CustomerOrder::display(ostream &os) const
{
    os << m_name << " - " << m_product << endl;

    for (size_t i = 0; i < m_countItem; i++)
    {
        os << std::right;
        os << "[" << setw(6) << setfill('0') << m_listItem[i]->m_serialNumber << "] ";
        os << setfill(' ') << left;
        os << setw(m_widthField + 2) << m_listItem[i]->m_itemName << " - ";
        os << (m_listItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
        os << endl;
    }
}
