

#ifndef STATION_H
#define STATION_H

#include <string>

using namespace std;

namespace sdds
{
    class Station
    {
        int m_id;
        string m_name;
        string m_desc;
        
        unsigned int nextSerial;
        unsigned int stockQty;

        static size_t m_widthField;
        static int id_generator;

    public:
        
        Station(const string& record);
        const string& getItemName() const;
        
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        
        void display(ostream& os, bool full) const;
    };
};

#endif
