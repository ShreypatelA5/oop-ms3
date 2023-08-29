// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

char sdds::Utilities::m_delimiter = '|';

size_t sdds::Utilities::getFieldWidth() const
{
    return m_widthField;
}

void sdds::Utilities::setFieldWidth(size_t newWidth)
{
    m_widthField = newWidth;
}

string sdds::Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
{

    if (str[next_pos] == m_delimiter || next_pos >= str.length())
    {
        more = false;
        throw invalid_argument("Invalid next_pos arguement");
    }

    string tokenVar = "";
    string whitespace = "";

    while (next_pos < (size_t)str.length())
    {
        if (str[next_pos] != ' ')
        {
            if (str[next_pos] == '\n' || str[next_pos] == '\r')
            {
                break;
            }
            else if (str[next_pos] == m_delimiter)
            {
                if (m_widthField < tokenVar.length())
                {
                    m_widthField = tokenVar.length();
                }
                more = true;
                next_pos++;
                return tokenVar;
            }
            else
            {
                if (tokenVar.length() > 0)
                {
                    tokenVar += whitespace + str[next_pos];
                    whitespace = "";
                }
                else
                {
                    tokenVar += str[next_pos];
                    whitespace = "";
                }

                if (next_pos == (size_t)str.length() - 1)
                {
                    if (m_widthField < tokenVar.length())
                    {
                        m_widthField = tokenVar.length();
                    }
                    more = false;
                    next_pos++;
                    return tokenVar;
                }
            }
        }
        else
        {
            whitespace += ' ';
        }
        next_pos++;
    }
    more = false;
    return tokenVar;
}
