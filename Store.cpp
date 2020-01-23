#include <iostream>
#include <string>
#include <iomanip>
#include "Store.h"
#include "Inventory.h"
#include "Misc.h"
using namespace std;

// multiply the store prices as you go on
Store::Store(int mult){
    float n =1 + ((mult*0.25)- 0.25);
    pOxen = 40 * n;
    pFood = 0.5 * n;
    pMedkits = 25 * n;
    pBullets = 2 * n;
    pParts = 20 * n;
}

void Store::displayStore(Inventory& supplies, int numStore){
    double total = 0;
    int input, choice, temp;
    string enter;
    
    // display the info about the store if it's the first time at the beginning of the game
    if(numStore==1){
        cout<<"\nYou had saved $1200 for your trip, and you just spend $200 to buy your wagaon."<<endl;
        cout<<"You will need to spend the rest of your $1000 on the items in the store. Note you will be able to purchase items at stores along the way so you may want to save some money, however the later you buy supplies the more expensive it will be."<<endl;
        cout<<"\n1. OXEN: You must spend $100-$200 on your team. If you lose all your oxen along the trail, you will lose."<<endl;
        cout<<"2. FOOD: Your party consumes food for every day of your journey. If you run out of food, you will lose."<<endl;
        cout<<"3. BULLETS: You will use bullets to hunt for more food and fend off bandits along your journey."<<endl;
        cout<<"4. MEDICAL KITS: If one of your party members gets sick, you can use a medkit to decrease their chances of dying. If you die, you will lose."<<endl;
        cout<<"5. WAGON PARTS: You will use the different parts to fix your wagon. If your wagon breaks and you do not have the correct part to fix it, you will lose."<<endl;
        cout<<"\nPress 1 then 'enter' when you are ready to continue to the store"<<endl;
        cont:
        cin>>enter;
        if(enter!="1"){
            cout<<"Please enter 1 then the enter key"<<endl;
            goto cont;
        }
    }
    
    menu:
    cout<<"\nWhat would you like to purchase?"<<endl;
    cout<<"--Current Money: $"<<fixed<<setprecision(2)<<supplies.getMoney()<<"--"<<endl;
    cout<<"--Current Bill: $"<<fixed<<setprecision(2)<<total<<"--"<<endl;
    cout<<"1. Oxen"<<endl;
    cout<<"2. Food"<<endl;
    cout<<"3. Bullets"<<endl;
    cout<<"4. Wagon Parts"<<endl;
    cout<<"5. Medkits"<<endl;
    cout<<"6. Pay and exit the store"<<endl;
    cin>>enter;
    if(ifNumber(enter) == false){
        goto elseStore;
    }
    choice = stoi(enter);
    
    switch(choice){
        
        case 1:
            cout<<endl;
            // if it's the first store they must purchase a certain amount of oxen
            if(numStore==1){
                cout<<"You must purchase between $100 and $200 worth of oxen"<<endl;
            }
            cout<<"You currently have "<<supplies.getOxen()<<" oxen"<<endl;
            cout<<"A yoke of 2 oxen costs $"<<pOxen<<", how many would you like to purchase?"<<endl;
            cout<<"(to return items, enter a negative number)"<<endl;
            oxIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter a number of oxen to buy"<<endl;
                goto oxIn;
            }
            
            input = stoi(enter);
            temp = supplies.getOxen();
            supplies.setOxen(supplies.getOxen() + (2*input));
            if(numStore==1){
                if(supplies.getOxen()<6 || supplies.getOxen()>10){
                    cout<<"You must spend between $100 and $200 on your oxen"<<endl;
                    cout<<"How many yokes would you like to purchase?"<<endl;
                    supplies.setOxen(temp);
                    goto oxIn;
                }
            }
            
            total = total + (pOxen * input);
            goto menu;
        
        case 2:
            cout<<endl;
            if(numStore==1){
                cout<<"It is reccomended you purchase at least 200lbs of food"<<endl;
            }
            cout<<"You currently have "<<supplies.getFood()<<"lbs of food"<<endl;
            cout<<"A pound of food costs $"<<pFood<<", how much would you like to purchase?"<<endl;
            cout<<"(to return items, enter a negative number)"<<endl;
            foodIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter an amount of food to buy"<<endl;
                goto foodIn;
            }
            
            input = stoi(enter);
            supplies.setFood(supplies.getFood()+input);
            
            total = total + (pFood * input);
            goto menu;
            
        case 3:
            cout<<endl;
            cout<<"You currently have "<<supplies.getBullets()<<" bullets"<<endl;
            cout<<"A box of 20 bullets costs $"<<pBullets<<", how many would you like to purchase?"<<endl;
            cout<<"(to return items, enter a negative number)"<<endl;
            bulIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter a number of boxes to buy"<<endl;
                goto bulIn;
            }
            
            input = stoi(enter);
            
            supplies.setBullets(supplies.getBullets()+(input*20));
            total = total + (pBullets * input);
            goto menu;
            
        case 4:
            cout<<endl;
            int in1, in2, in3;
            cout<<"You currently have "<<supplies.getWheels()<<" wheels, "<<supplies.getTongues()<<" tongues, and "<<supplies.getAxels()<<" axels"<<endl;
            cout<<"A wheel, tongue, and axel each cost $"<<pParts<<endl;
            cout<<"(to return items, enter a negative number)"<<endl;
            cout<<"How many wheels would you like to buy?"<<endl;
            wheeIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter a number of wheels to buy"<<endl;
                goto wheeIn;
            }
            in1 = stoi(enter);
            cout<<"How many tongues would you like to buy?"<<endl;
            tongIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter a number of tongues to buy"<<endl;
                goto tongIn;
            }
            in2 = stoi(enter);
            cout<<"How many axels would you like to buy?"<<endl;
            axIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter a number of axels to buy"<<endl;
                goto axIn;
            }
            in3 = stoi(enter);
            supplies.setWheels(supplies.getWheels()+in1);
            supplies.setTongues(supplies.getTongues()+in2);
            supplies.setAxels(supplies.getAxels()+in3);
            total = total +(pParts * (in1 + in2 + in3));
            goto menu;
            
        case 5:
            cout<<endl;
            cout<<"You currently have "<<supplies.getMedkits()<<" medical kits"<<endl;
            cout<<"A medkit costs $"<<pMedkits<<", how many would you like to purchase?"<<endl;
            cout<<"(to return items, enter a negative number)"<<endl;
            medIn:
            cin>>enter;
            if(ifNumber(enter)==false){
                cout<<"Please enter a number of medkits to buy"<<endl;
                goto medIn;
            }
            input = stoi(enter);
            supplies.setMedkits(supplies.getMedkits()+input);
            total = total + (pMedkits * input);
            goto menu;
            
        case 6:
            // make them spend the correct amount on their oxen
            if(numStore==1){
                if(supplies.getOxen()<6 || supplies.getOxen()>10){
                    cout<<"You must spend between $100 and $200 on your oxen"<<endl;
                    goto menu;
                }
            }
            
            if(total>supplies.getMoney()){
                cout<<"Sorry, you're trying to buy more than you can afford, please return some items first\n"<<endl;
                goto menu;
            }
            
            cout<<"\nYour bill was $"<<fixed<<setprecision(2)<<total<<endl;
            cout<<"Thanks for shopping!\n"<<endl;
            supplies.pay(total);
            break;
            
        default:
            elseStore:
            cout<<"\nPlease choose one of the options 1-6\n"<<endl;
            goto menu;
    }
    
}