#ifndef STORE_H_
#define STORE_H_
#include "Inventory.h"
using namespace std;

class Store{
        
    private:
        
        double pOxen, pFood, pMedkits, pBullets, pParts;
            
    public:
    
        Store(int);
        void displayStore(Inventory&, int);

};

#endif