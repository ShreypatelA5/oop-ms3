// Name: Shrey Patel
// Seneca Student ID: 158379214
// Seneca email: spatel562@senecacollege.ca
// Date of completion: 7th April 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <algorithm>
#include <fstream>

#include "Utilities.h"
#include "LineManager.h"

using namespace sdds;
using namespace std;

LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
{
    Utilities utils;

    ifstream input(file);
    
    if (!input.is_open())
    {
        throw string("Unable to open file.");
    }
    
    string record;
    while (!input.eof())
    {
        getline(input, record);
        size_t npos = 0;
        bool more = true;
        
        string currStn, nextStn;
        currStn = utils.extractToken(record, npos, more);

        if (more)
        {
            nextStn = utils.extractToken(record, npos, more);
        }

        Workstation* currWS = nullptr;
        Workstation* nxtWS = nullptr;
        
        for_each(stations.begin(), stations.end(), [&currWS, &nxtWS, currStn, nextStn](Workstation* ws)
            {
            if (ws->getItemName() == currStn)
            {
                currWS = ws;
            }
            else if (ws->getItemName() == nextStn)
            {
                nxtWS = ws;
            }
            });

        if (m_activeLine.size() == 0)
        {
            m_firstStation = currWS;
        }

        currWS->setNextStation(nxtWS);
        m_activeLine.push_back(currWS);
    }

    input.close();
}

bool LineManager::run(ostream& os)
{
    static int count = 0;
    count++;
    
    os << "Line Manager Iteration: " << count << endl;

    if (!g_pending.empty())
    {
        (*m_firstStation) += move(g_pending.front());
        g_pending.pop_front();
    }

    for (unsigned int i = 0; i < m_activeLine.size(); i++)
    {
        m_activeLine[i]->fill(os);
    }

    for (unsigned int i = 0; i < m_activeLine.size(); i++)
    {
        m_activeLine[i]->attemptToMoveOrder();
    }

    bool isEmpty = true;
    
    for (unsigned int i = 0; i < m_activeLine.size(); i++)
    {
        if (!m_activeLine[i]->empty())
        {
            isEmpty = false;
            break;
        }
    }

    return isEmpty;
}

void LineManager::reorderStations()
{
    vector<Workstation*> newStations;
    Workstation* lastStation = nullptr;
    unsigned int count = 0;
    
    while (count < m_activeLine.size())
    {
        for (unsigned int i = 0; i < m_activeLine.size(); i++)
        {
            if (m_activeLine[i]->getNextStation() == lastStation)
            {
                newStations.push_back(m_activeLine[i]);
                lastStation = m_activeLine[i];
                count++;
                
                break;
            }
        }
    }
    reverse(newStations.begin(), newStations.end());
    m_firstStation = newStations[0];
    m_activeLine = newStations;
}

void LineManager::display(ostream& os) const
{
    for (unsigned int i = 0; i < m_activeLine.size(); i++)
    {
        m_activeLine[i]->display(os);
    }
}
