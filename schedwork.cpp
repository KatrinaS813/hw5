#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(
    const AvailabilityMatrix& avail, 
    size_t dailyNeed, 
    size_t maxShifts, 
    DailySchedule& sched, 
    vector<size_t>& shiftCount, 
    size_t day, 
    size_t slot
); 

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
    if(avail[0].size() == 0){
        return false; 
    }
    size_t n = avail.size();
    size_t k = avail[0].size(); 
    sched = DailySchedule(n, vector<Worker_T>()); 
    vector<size_t> shiftCount(k, 0); 
    return schedule_helper(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0); 
}

bool schedule_helper(
    const AvailabilityMatrix& avail, 
    size_t dailyNeed, 
    size_t maxShifts, 
    DailySchedule& sched, 
    vector<size_t>& shiftCount, 
    size_t day, 
    size_t slot
)
{
    size_t n = avail.size();
    size_t k = avail[0].size(); 

    if(day == n){
        return true;    
    }
    for(Worker_T worker = 0; worker < k; worker++){
        if(avail[day][worker] && 
            shiftCount[worker] < maxShifts &&
            find(sched[day].begin(), sched[day].end(), worker) == sched[day].end())
        {
            sched[day].push_back(worker);
            shiftCount[worker]++;

            size_t nextDay = day; 
            size_t nextSlot = slot + 1; 
            if(nextSlot == dailyNeed){
                nextDay++; 
                nextSlot = 0; 
            }
            if(schedule_helper(avail, dailyNeed, maxShifts, sched, shiftCount, nextDay, nextSlot)){
                return true; 
            }
            sched[day].pop_back(); 
            shiftCount[worker]--; 
        }
    }
    return false; 
}



