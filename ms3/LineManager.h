// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _LINE_MANAGER_H
#define _LINE_MANAGER_H

#include <iostream>
#include <string>
#include <vector>

#include "Workstation.h"

using namespace std;

namespace sdds
{
    class LineManager
    {
        vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        
        Workstation* m_firstStation;

    public:
        
        LineManager(const string& file, const vector<Workstation*>& stations);
        void reorderStations();
        bool run(ostream& os);
        
        void display(ostream& os) const;
    };
};

#endif
