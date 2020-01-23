#ifndef TRAVEL_H_
#define TRAVEL_H_
#include "Fort.h"
#include "River.h"
using namespace std;

void split(string, char, string[], int);

class Travel{
    
    private:
    
        int totMiles;
        int curDay, curMonth;
        int numForts, numRivers;
        int monthDays[13];
        string monthNames[13];
        River rivers[10];
        Fort forts[10];
        
        
    public:
    
        Travel();
        
        void readForts();
        void readRivers();
        
        int getNextMilestone();
        string getMilestoneType();
        void visitFort();
        void crossRiver();
        string getRiverName();
        int getRiverDepth();
        string getFortName();
        
        void advanceMiles(int);
        void setTotalMiles(int);
        int getTotalMiles();
        
        void advanceDays(int);
        void setDate(int, string);
        int getCurDay();
        string getCurMonth();
        
};

#endif