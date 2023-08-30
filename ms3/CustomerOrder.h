

#ifndef _CUSTOMER_ORDER_H
#define _CUSTOMER_ORDER_H

#include "Station.h"

using namespace std;

namespace sdds {
    struct Item
    {
        string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const string& src) : m_itemName(src)
        {
            // empty
        };
    };

    class CustomerOrder
    {
        string m_name;
        string m_product;
        size_t m_countItem;
        
        Item** m_listItem;
        static size_t m_widthField;

    public:
        
        CustomerOrder();
        CustomerOrder(const string& inputString);
        CustomerOrder(const CustomerOrder& source);
        
        CustomerOrder& operator=(const CustomerOrder& source) = delete;
        CustomerOrder(CustomerOrder&& source) noexcept;
        CustomerOrder& operator=(CustomerOrder&& source) noexcept;
        ~CustomerOrder();
        
        bool isOrderFilled() const;
        bool isItemFilled(const string& itemName) const;
        void fillItem(Station& station, ostream& os);
        
        void display(ostream& os) const;

    };
};

#endif
