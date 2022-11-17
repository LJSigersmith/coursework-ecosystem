//
//  ECLifeSimulator.cpp
//  
//
//  Created by Yufeng Wu on 10/12/22.
//

#include "ECLifeSimulator.h"
#include "ECOrganism.h"
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

// ********************************************************
// Life simulator

ECLifeSimulator::ECLifeSimulator() {
}

void ECLifeSimulator::Initialize(double start, double limit) {
    _currentTime = start;
    _dayNum = 1;
    _timeExpired = false;
    _startTime = start;
    _timeLimit = limit;

    dailyEventsCopy = dailyEvents;
    if (_timeLimit < 24) {
        _lastDay = 1;
        _lastTime = limit;
    } else if (limit == 24) {
        _lastDay = 1;
        _lastTime = 24;
    } else {
        _lastDay = ceil(limit / 24);
        _lastTime = ((int)floor(limit) % 24 ) + ( ceil(limit) - limit ) - 1;
    }
}

int ECLifeSimulator::AddOrganism(ECOrganism* ptr) {
    ptr->SetID(organisms.size());
    organisms.push_back(ptr);
    return organisms.size() - 1;
}

void ECLifeSimulator::AddDailyEvent( double hours, int indexOrganism, int type, int subtype ) {

    ECOrganism* org = organisms[indexOrganism];

    // If the organism will be sleeping at this hour, they can't have an event
    if (org->IsSleeping(hours)) { return; }

    Event* e = new Event(type, subtype, hours, org);

    if (dailyEvents.count(hours) == 1) {
        dailyEvents[hours].push_back(e);
    } else {
        dailyEvents.insert(make_pair(hours,vector<Event*>()));
        dailyEvents[hours].push_back(e);
    } 
    
    existingEvents.push_back(e);

}

map<double, vector<int> > ECLifeSimulator::findEventsToErase(ECOrganism* die) {

    map<double, vector<int> > eventsToErase;
    // For every hour, event pair in daily events
    for (auto p : dailyEvents) {
       vector<Event*> events = p.second;
        int index = 0;

        // Loop through each event, if its an event of the dying organism, add it to events to be erased
        for (auto it = events.begin(); it != events.end(); it++) {
            Event* e = *it;
            if (e->organism->GetID() == die->GetID()) {
                // If the key doesn't exist yet create it and add event to be erased
                if (eventsToErase.count(p.first) == 1) {
                    eventsToErase[p.first].push_back(index);
                } else {
                    vector<int> indices = {index};
                    eventsToErase.insert(make_pair(p.first, indices));
                }
            }
           index++;
        }
    }
    return eventsToErase;

}

void ECLifeSimulator::eraseEvents(map<double, vector<int> > eventsToErase) {

    // eventsToErase is a double, vector<int> pair: time, and indexes at time to erase
    for (auto p : eventsToErase) {
        double time = p.first;
        vector<int> indexes = p.second;
        
        // Pointer to the events at the time, so I can actually manipulate it and erase elements
        vector<Event*>* eventsAtTime = &dailyEvents[time];

        // For every index that needs to be erased at this time (hour)
        for (int i : indexes) {
            // Erase it
            Event* toBeErased = (*eventsAtTime)[i];
            eventNoLongerExists(toBeErased);
            eventsAtTime->erase(eventsAtTime->begin() + i);
            // If there are now no events at this hour, erase the key too get the whole entry
            if (eventsAtTime[i].size() == 0) {
                dailyEvents.erase(time);
            }
        }
    }

}

void ECLifeSimulator::KillOrganism(ECOrganism* die) {   
    
    // Dict : key is hour event occurs, vector is list of indexes within that hour where events are stored
    map<double, vector<int> > eventsToErase = findEventsToErase(die);
    
    eraseEvents(eventsToErase);

    // If the organism is some other organism's prey, set that pointer to NULL
    for (auto organism : organisms) {
        if (organism->GetPrey() == die) {
            organism->SetPrey(NULL);
        }
    }

    // Finally erase the organism from the list of organisms
    organisms.erase(organisms.begin() + die->GetID());
    //delete die;
    
    // Adjust id values
    int i = 0;
    for (auto organism : organisms) {
        organism->SetID(i);
        i++;
    }

    cout << die->GetName() << " is now dead" << endl;
}

void ECLifeSimulator::handleEvent(Event* e) {

    ECOrganism* organism = e->organism;

    int eventResult;
    if (e->type == 0) {
        eventResult = organism->Eat();
    }
    if (e->type == 1) {
        eventResult = organism->Work(e->subtype);
    }

    // -1 Kill Itself and Prey
    if (eventResult == -1) {
        ECOrganism* prey = organism->GetPrey();
        organism->SetPrey(NULL);
        KillOrganism(prey);
        KillOrganism(organism);
    } else if (eventResult == -2) {
    // -2 Kill Prey
        ECOrganism* prey = organism->GetPrey();
        organism->SetPrey(NULL);
        KillOrganism(prey);
    // -3 Kill Itself, Prey Health - X
    } else if (eventResult == -3) {
        KillOrganism(organism);
    // -5 Kill Itself
    } else if (eventResult == -5) {
        KillOrganism(organism);
    }


}

void ECLifeSimulator::SimInfo() {
    cout << "**** Simulation Information ****" << endl;
    cout << "\tStarting Time: " << _startTime << endl;
    cout << "\tTime Limit: " << _timeLimit << endl;
    cout << "\tCalculated Last Day: " << _lastDay << endl;
    cout << "\tCalculated Last Hour: " << _lastTime << endl;
    cout << "\tSimulation Events: " << endl;
    for (auto p : dailyEvents) {
        double hour = p.first;
        cout << "\tHour: " << hour << endl;
        for (Event* e : p.second) {
            cout << "\t\t" << e->organism->GetName() << ": " << e->type << "," << e->subtype << endl;
        }
    }
    cout << "\tOrganisms:" << endl;
    for (auto o : organisms) {
        cout << "\t\t(" << o->GetID() << ") " << o->GetName() << "(" << o->GetClass() << ")" << endl;
        if (o->GetPrey()) {
            cout << "\t\t\tPrey: " << o->GetPrey()->GetName() << endl;
        }
    }
    cout << "********************************" << endl;
}

double ECLifeSimulator::Simulate(double hoursStart, double timeLimit) {

    Initialize(hoursStart, timeLimit);
    SimInfo();

    while (!_timeExpired) {
        cout << endl << "== Day " << _dayNum << " ==" << endl;
        
        for (auto& p : dailyEventsCopy) {
            double hour = p.first;
            if (_dayNum == 1 && hour < hoursStart) { continue; }
            if (_dayNum == _lastDay && hour > (_lastTime + 1)) {
                _timeExpired = true;
                return ((_dayNum - 1) * 24) + (_lastTime + 1);
            }

            bool hourPrint = true;
            for (Event* e : p.second) {

                if (doesEventExist(e)) {
                    if (hourPrint) { cout << "\n== Hour " << hour << " ==" << endl; hourPrint = false; }
                    _currentTime = hour;
                    handleEvent(e);
                }
                
                if (existingEvents.size() == 0 || organisms.size() == 0) {
                    cout << "Out of events or organisms" << endl;
                    _timeExpired = true;
                    return ((_dayNum - 1) * 24) + _currentTime;
                }
            }
        }
        _dayNum++;
        if (_dayNum > _lastDay) {
            _timeExpired = true;
            return timeLimit;
        }
    }
    return -1;
}

void ECLifeSimulator::GetAliveOrganisms(std::set<std::string> &setAlives) const {

    for (auto org : organisms) {
        setAlives.insert(org->GetName());
    }

}

double ECLifeSimulator::GetVitalityFor(const std::string &orgName) const {

    for (ECOrganism* o : organisms) {
        if (o->GetName() == orgName) {
            return o->GetHealth();
        }
    }
    return 0;
}
    

