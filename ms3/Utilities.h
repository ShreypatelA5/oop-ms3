// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _UTILITIES_H
#define _UTILITIES_H

#include <string>
#include <stdexcept>

using namespace std;

namespace sdds
{
    class Utilities
    {
        size_t m_widthField = 1;
        static char m_delimiter;

    public:
        
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        
        string extractToken(const string &str, size_t &next_pos, bool &more);
        
        static char getDelimiter()
        {
            return m_delimiter;
        }
        static void setDelimiter(char newDelimiter)
        {
            m_delimiter = newDelimiter;
        }
    };
};

#endif


