#ifndef RIVER_H_
#define RIVER_H_
using namespace std;

class River{
    
    private:
    
        string name;
        int distance, depth;
        
    public:
    
        River();
        River(string, int, int);
        string getName();
        void setName(string);
        int getDistance();
        void setDistance(int);
        int getDepth();
        void setDepth(int);
    
};

#endif