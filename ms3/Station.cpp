// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>

#include "Utilities.h"
#include "Station.h"

size_t sdds::Station::m_widthField = 0;

int sdds::Station::id_generator = 0;

sdds::Station::Station(const string& record)
{
    Utilities Utils;
    size_t next_pos = 0;
    bool more = true;

    m_id = ++id_generator;
    m_name = Utils.extractToken(record, next_pos, more);
    
    nextSerial = stoi(Utils.extractToken(record, next_pos, more));
    stockQty = stoi(Utils.extractToken(record, next_pos, more));
    
    m_widthField = m_widthField > Utils.getFieldWidth() ? m_widthField : Utils.getFieldWidth();
    m_desc = Utils.extractToken(record, next_pos, more);
}

size_t sdds::Station::getNextSerialNumber()
{
    return nextSerial++;
}

const string& sdds::Station::getItemName() const
{
    return m_name;
}

void sdds::Station::updateQuantity()
{
    if (stockQty > 0)
    {
        stockQty--;
    }
}

size_t sdds::Station::getQuantity() const
{
    return stockQty;
}

void sdds::Station::display(ostream& os, bool full) const
{
    os << std::right;
    os << setw(3) << setfill('0') << m_id << " | ";
    os << left << setfill(' ') << setw(m_widthField + 1) << m_name << " | ";
    os << right << setw(6) << setfill('0') << nextSerial << " | ";

    if (full)
    {
        os << setfill(' ');
        os << right;
        os << setw(4) << stockQty << " | " << m_desc;
    }
    os << endl;
}
