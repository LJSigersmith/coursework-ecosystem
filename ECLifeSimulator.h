//
//  ECLifeSimulator.h
//  
//
//  Created by Yufeng Wu on 10/12/22.
//

#ifndef ECLifeSimulator_h
#define ECLifeSimulator_h

#include "ECOrganism.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

// ********************************************************
// Life simulator

class Event {
  public :
    Event(int type, int subtype, double startTime, ECOrganism* org) : type(type), subtype(subtype), startTime(startTime), organism(org) {}
    int type;
    int subtype;
    double startTime;
    ECOrganism* organism;
};

class ECLifeSimulator
{
public:
    ECLifeSimulator();
    
    // Initialize the simulation. Clear out all previous inputs (including the organisms)
    void Initialize(double hoursStart, double timeLimit);
    
    // Add an organism to simulate. Note: don't free its memory inside simulator
    // return its position in the list of organisms (to be used in future reference)
    int AddOrganism(ECOrganism *ptr);
    
    // Schedule a daily event for an organism, at certain time of day (hours), type of event (0: eat, 1: work), subtype of the event (for work, the kind of work)
    void AddDailyEvent( double hours, int indexOrganism, int type, int subtype );
    
    // Run simulation from some time (hours) until there is no living organisms or run out of time (as specified in timeLimt, which is in the unit of hours)
    //Return the total elapsed time from start to end of the simulation (in hours).
    double Simulate(double hoursStart, double timeLimit);
    
    // Collect info on simulation
    // Get the alive organisms and return their names in the passed-in set
    void GetAliveOrganisms(std::set<std::string> &setAlives) const;
    
    // Get the vitality of a specific organism (as named)
    double GetVitalityFor(const std::string &orgName) const;

    void handleEvent(Event *e);
    
private:
    std::vector<ECOrganism*> organisms;
    std::map<double, std::vector<Event*> > dailyEvents;
    std::map<double, std::vector<Event*> > dailyEventsCopy;
    std::vector<Event*> existingEvents;

    double _currentTime, _startTime, _timeLimit, _lastTime;
    int _dayNum, _lastDay;
    bool _timeExpired;

    void KillOrganism(ECOrganism *die);

    bool doesEventExist(Event* e) {
        if (find(existingEvents.begin(), existingEvents.end(), e) != existingEvents.end()) {
            return true;
        }
        return false;
    }

    void eventNoLongerExists(Event* e) {
        auto it = find(existingEvents.begin(), existingEvents.end(), e);
        if (it != existingEvents.end()) {
            existingEvents.erase(it);
        }
    }

    map<double, vector<int> > findEventsToErase(ECOrganism *die);

    void eraseEvents(map<double, vector<int> > eventsToErase);

    void SimInfo();
};

#endif /* ECLifeSimulator_h */
