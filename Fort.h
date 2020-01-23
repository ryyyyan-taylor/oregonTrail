#ifndef FORT_H_
#define FORT_H_
using namespace std;

class Fort{
    
    private:
    
        string name;
        int distance;
        
    public:
    
        Fort();
        Fort(string, int);
        string getName();
        void setName(string);
        int getDistance();
        void setDistance(int);
    
};

#endif