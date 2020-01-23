#ifndef INVENTORY_H_
#define INVENTORY_H_
using namespace std;
        
class Inventory{
    
    private:
        
        int oxen, food, medkits, bullets, parts, tongues, wheels, axels;
        double money;
        
    public:
        
        Inventory();
        
        int getOxen();
        void setOxen(int);
        int getFood();
        void setFood(int);
        void decreaseFood(int);
        void addFood(int);
        int getMedkits();
        void setMedkits(int);
        int getBullets();
        void setBullets(int);
        int getParts();
        void setParts(int);
        int getTongues();
        void setTongues(int);
        int getWheels();
        void setWheels(int);
        int getAxels();
        void setAxels(int);
        double getMoney();
        void setMoney(double);
        void pay(double);
        
};

#endif