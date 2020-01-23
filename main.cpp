#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>
#include <cctype>
#include "Travel.h"
#include "Player.h"
#include "Misc.h"
#include "Store.h"
#include "Inventory.h"
using namespace std;

int main(){
    
    // INITIALIZE NECESSARY OBJECTS
    Inventory supplies;
    Player travelers[6];
    Travel journey;
    int n, u; // integers used throughout for switches
    string input; // input string used throughout
    int numStore = 1;
    journey.readRivers();
    journey.readForts();
    int party; // number of people in the party
    
    // WELCOME TEXT
    
    cout<<"THIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM \nINDEPENDENCE, MISSOURI TO OREGON CITY, OREGON IN 1847. YOUR FAMILY OF \nFIVE WILL COVER THE 2040 MILE OREGON TRAIL IN 5-6 MONTHS --- \nIF YOU MAKE IT ALIVE."<<endl;
    
    // temporary player object to take in names
    Player person;
    for(int i=1; i<=5; i++){
        
        if(i==1){
            cout<<"\nWhat is your name?"<<endl;
        }
        
        else{
            cout<<"\nWhat is your next party member's name?"<<endl;
        }
        
        cin>>input;
        person.setName(input);
        travelers[i] = person;
    }
    
    party = 5;
    cout<<"\nYour party will consist of:"<<endl;
    for(int i=0;i<=5;i++){
        cout<<travelers[i].getName()<<endl;
    }
    
    // SET OWN DATE OR USE ORIGINAL
    
    dateChoose:
    cout<<"\nThe default departure date is March 28th, 1847\nWould you like to (1) use this departure date or (2) set your own?"<<endl;
    cin>>input;
    if(ifNumber(input) == false){
        goto elseMonth;
    }
    n=stoi(input);
    if(n==1){
        journey.setDate(28, "March");
    }
    else if(n==2){
        string monthIn;
        int dateIn;
        
        cout<<"\nThe earlier you start your journey, the more time you will have and thus the easier the journey will be."<<endl;
        cout<<"If you're up for it, choose a later start date for an added challenge."<<endl;
        monthChoice:
        cout<<"Would you like to start in March, April, or May?"<<endl;
        cin>>monthIn;
        if(monthIn=="March" || monthIn=="march"){
            marchDay:
            cout<<"What day in March would you like to start?"<<endl;
            cin>>input;
            if(ifNumber(input)==false){
                goto elseMarch;
            }
            n=stoi(input);
            if(n>0 && n<=31){
                cout<<"Okay, you will start on March "<<n<<", 1847"<<endl;
                journey.setDate(n, "March");
            }
            else{
                elseMarch:
                cout<<"Please choose a day within the month of March"<<endl;
                goto marchDay;
            }
        }
        else if(monthIn=="April" || monthIn=="april"){
            aprilDay:
            cout<<"What day in April would you like to start?"<<endl;
            cin>>input;
            if(ifNumber(input)==false){
                goto elseApril;
            }
            n=stoi(input);
            if(n>0 && n<=30){
                cout<<"Okay, you will start on April "<<n<<", 1847"<<endl;
                journey.setDate(n, "April");
            }
            else{
                elseApril:
                cout<<"Please choose a day within the month of April"<<endl;
                goto aprilDay;
            }
        }
        else if(monthIn=="May" || monthIn=="may"){
            cout<<"The latest available start date is May 1st, so you will start then"<<endl;
            journey.setDate(1, "May");
        }
        else{
            cout<<"Please choose either 'March', 'April', or 'May'\n"<<endl;
            goto monthChoice;
        }
    }
    else{
        elseMonth:
        cout<<"Please choose one of the given options"<<endl;
        goto dateChoose;
    }
    // VISITING FIRST STORE
    
    double startMoney = 1000;
    supplies.setMoney(startMoney);
    int first = 1;
    Store initial(first);
    initial.displayStore(supplies, numStore);
    numStore++;

    // START TURN LOOP
    dead:
    while(1){
        
        // gameover if out of food
        if(supplies.getFood()<=0){
            gameOver(4);
            endStats(supplies, travelers[1].getName(), journey);
            return 0;
        }
        
        // gameover if didn't make it by winter
        if(journey.getCurMonth() == "December"){
            gameOver(5);
            endStats(supplies, travelers[1].getName(), journey);
            return 0;
        }
        
        //Current States
        cout<<"\n---"<<journey.getCurMonth()<<" "<<journey.getCurDay()<<", 1847---"<<endl;
        cout<<"Total Miles: "<<journey.getTotalMiles()<<"mi"<<endl;
        if(journey.getNextMilestone() != 0){
            cout<<"Next milestone at: "<<journey.getNextMilestone()<<"mi"<<endl;
        }
        cout<<"Available Food: "<<supplies.getFood()<<"lbs"<<endl;
        cout<<"Available Bullets: "<<supplies.getBullets()<<endl;
        cout<<"Available Money: $"<<fixed<<setprecision(2)<<supplies.getMoney()<<endl;
        
        dispMenu:
        displayMenu();
        
        // take menu choice
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose one of the menu options"<<endl;
            goto dispMenu;
        }
        n = stoi(input);
        
        switch(n){
            
            case 1:
            //rest
                n = rand() % 3 + 1;
                journey.advanceDays(n);
                supplies.decreaseFood(party*3);
                break;
                    
            case 2:
            //continue
                moveOn:
                
                n = rand() % 140 + 70;
                if(n>140){
                    n=140;
                }
                
                // move miles and eat food
                journey.advanceMiles(n);
                journey.advanceDays(14);
                supplies.decreaseFood(3 * party);
                // win if miles is greater than 2040
                if(journey.getTotalMiles() >= 2040){
                    win();
                    endStats(supplies, travelers[1].getName(), journey);
                }
                // go to river or fort if at correct distance
                if(journey.getNextMilestone() != 0){
                    if(journey.getTotalMiles()>journey.getNextMilestone()){
                        journey.setTotalMiles(journey.getNextMilestone());
                        // visit fort 
                        if(journey.getMilestoneType() == "fort"){
                            numStore++;
                            cout<<"\nYou reached "<<journey.getFortName()<<endl;
                            Store fortStore(numStore);
                            fort:
                            cout<<"\n---"<<journey.getCurMonth()<<" "<<journey.getCurDay()<<", 1847---"<<endl;
                            cout<<"What would you like to do?"<<endl;
                            cout<<"1. Continue on the trail"<<endl;
                            cout<<"2. Visit the fort's store"<<endl;
                            cout<<"3. Rest for the day"<<endl;
                            
                            cin>>input;
                            if(ifNumber(input) == false){
                                cout<<"Please choose one of the menu options"<<endl;
                                goto fort;
                            }
                            
                            u=stoi(input);
                            cout<<u<<endl;
                            
                            // continue on the trail
                            if(u==1){
                                journey.visitFort();
                                goto moveOn;
                            }
                            // visit the fort store
                            else if(u==2){
                                fortStore.displayStore(supplies, numStore);
                                goto fort;
                            }
                            // rest for the night
                            else if(u==3){
                                journey.advanceDays(1);
                                supplies.decreaseFood(3*party);
                                cout<<"Your party rested through the night"<<endl;
                                goto fort;
                            }
                            else{
                                cout<<"Please choose one of the menu options"<<endl;
                                goto fort;
                            }
                            
                            // This whole section stopped working after I added the stoi(), thought it would be interesting to leae in
                            // switch(u){
                                
                            //     case 1:
                            //         journey.visitFort();
                            //         goto moveOn;
                            //         break;
                                    
                            //     case 2: 
                            //         fortStore.displayStore(supplies, numStore);
                            //         numStore++;
                            //         goto fort;
                            //         break;
                                    
                            //     case 3:
                            //         journey.advanceDays(1);
                            //         supplies.decreaseFood(3*party);
                            //         cout<<"Your party rested through the night"<<endl;
                            //         goto fort;
                            //         break;
                                    
                            //     default:
                            //         cout<<"Please choose one of the menu options"<<endl;
                            //         goto fort;
                            //         break;
                            // }
                        }
                        // visit river
                        else if(journey.getMilestoneType() == "river"){
                            cout<<"\nYou reached the "<<journey.getRiverName()<<endl;
                            river:
                            cout<<"\n---"<<journey.getCurMonth()<<" "<<journey.getCurDay()<<", 1847---"<<endl;
                            cout<<"What would you like to do?"<<endl;
                            cout<<"1. Cross the river"<<endl;
                            cout<<"2. Rest for the day"<<endl;
                            cin>>input;
                            if(ifNumber(input)==false){
                                cout<<"Please choose one of the menu options"<<endl;
                                goto river;
                            }
                            u=stoi(input);
                            switch(u){
                                
                                // cross the river
                                case 1:
                                    // if the river is more than 3 feet deep
                                    if(journey.getRiverDepth()>3){
                                        // pay if enough money
                                        if(supplies.getMoney()>=(party * 10)){
                                            cout<<"You payed the ferryman $10 per person to cross the river\n"<<endl;
                                            supplies.pay(party*10);
                                            journey.crossRiver();
                                            break;
                                        }
                                        // leave the whole party behind if not enough money
                                        else if(supplies.getMoney()<(party * 10)){
                                            cout<<"You do not have enough money for the entire party to cross, so you will have to leave your entire party behind and continue yourself"<<endl;
                                            supplies.pay(10);
                                            for(int i=2;i<party-1;i++){
                                                travelers[i].kill();
                                            }
                                            party = 1;
                                            journey.crossRiver();
                                            break;
                                        }
                                    }
                                    // river less than 3 feet deep
                                    else if(journey.getRiverDepth()<=3){
                                        cout<<"Your party crossed the river\n"<<endl;
                                        journey.crossRiver();
                                        break;
                                    }
                                // rest
                                case 2:
                                    journey.advanceDays(1);
                                    supplies.decreaseFood(3*party);
                                    cout<<"Your party rested through the night"<<endl;
                                    goto river;
                                    break;
                                    
                                default:
                                    cout<<"Please choose one of the given choices"<<endl;
                                    goto river;
                                    break;
                            }
                        }
                    }
                }
                break;
            
            case 3:
            //hunt
                journey.advanceDays(1);
                // not enough bullets
                if(supplies.getBullets()<10){
                    cout<<"You tried to go hunting, but you didn't have enough bullets"<<endl;
                }
                else{
                    hunt(supplies);
                }
                break;
                
            case 4:
            // quit
                gameOver(0);
                endStats(supplies, travelers[1].getName(), journey);
                return 0;
                break;
                
            default:
                cout<<"Please choose one of the menu options"<<endl;
                goto dispMenu;
        }
        
        //misfortunes
        misf:
        // choose which player might get sick
        n = rand() % party + 1;
        if(n == 1){
            input == "You";
        }
        else{
            if(travelers[n].ifDead() == true){
                srand(567);
                n = rand() % party + 1;
                goto misf;
            }
            input = travelers[n].getName();
        }
        
        int med = 1;
        int result, j, b=0;
        string choice;
        switch(misfortunes(input)){
            
            // party member gets sick
            case 1:
                // give the option to use a medkit
                if(supplies.getMedkits() > 0){
                    cout<<"You have "<<supplies.getMedkits()<<" medkits.\nWould you like to use one?\n1. Yes\n2. No"<<endl;
                    medChoice:
                    cin>>input;
                    if(ifNumber(input)==false){
                        cout<<"Please choose to either (1) use a medkit or (2) not?"<<endl;
                        goto medChoice;
                    }
                    n=stoi(input);
                    if(n == 1){
                        int x = rand() % 2 + 1;
                        if(x == 1){
                            cout<<"You used a medkit, but unfortunately "<<input<<" died anyways."<<endl;
                            result = 0;    
                        }
                        else{
                            cout<<"You used a medkit and "<<input<<" survived!"<<endl;
                            result = 1;
                        }
                    }
                    else if(n == 2){
                        med=0;
                        break;
                    }
                }
                // move on or rest of no medkits or medkits not used
                else if(supplies.getMedkits() == 0 || med==0){
                    cout<<"Would you like to (1) press on or (2) rest for a few days?"<<endl;
                    cout<<input<<" has a much higher chance of dying if you push on"<<endl;
                    j = rand() % 10 + 1;
                    string str;
                    sick:
                    cin>>str;
                    if(ifNumber(str)==false){
                        goto wrong;
                    }
                    n=stoi(str);
                    switch(n){
                        
                        case 1: 
                            if(j<=7){
                                result = 0;
                                cout<<"You risked it by pressing on, and "<<input<<" died"<<endl;
                                b = 1;
                            }
                            else{
                                result = 1;
                                cout<<"You risked it by pressing on on and "<<input<<" survived!"<<endl;
                                b=1;
                            }
                            break;
                        case 2:
                            if(j>7){
                                result = 0;
                                cout<<"You played it safe and rested, but "<<input<<" died anyways"<<endl;
                            }
                            else{
                                result = 1;
                                cout<<"You played it safe and rested and "<<input<<" survived!"<<endl;
                            }
                            break;
                        default:
                            wrong:
                            cout<<"Please choose to either (1) press on or (2) stay and rest"<<endl;
                            goto sick;
                    }
                }    
                // gameover if leader died
                if(result==0){
                    if(input=="You"){
                        gameOver(1);
                        endStats(supplies, travelers[1].getName(), journey);
                        return 0;
                    }
                    // kill whichever player
                    else{
                        for(int p=0; p<6; p++){
                            if(travelers[p].getName() == input){
                                travelers[p].kill();
                                party--;
                            }
                        }
                    }
                }
                if(b==1){
                    goto moveOn;
                }
                break;
            
            // an oxen died
            case 2:
                
                supplies.setOxen(supplies.getOxen() - 1);
                if(supplies.getOxen() == 0){
                    // gameover if all oxen are dead
                    gameOver(2);
                    endStats(supplies, travelers[1].getName(), journey);
                    return 0;
                }
                else{
                    cout<<"You have "<<supplies.getOxen()<<" left"<<endl;
                }
                break;
                
            // wagon parts broke    
            case 3:
            
                if(supplies.getWheels() == 0){
                    cout<<"You do not have the necessary parts to fix your wagon"<<endl;
                    // gameover if cannot fix the wagon
                    gameOver(3);
                    endStats(supplies, travelers[1].getName(), journey);
                    return 0;
                }
                else{
                    cout<<"You used one of your replacement wheels to fix your wagon"<<endl;
                    supplies.setWheels(supplies.getWheels()- 1);
                }
                break;
            
            case 4:
            
                if(supplies.getAxels() == 0){
                    cout<<"You do not have the necessary parts to fix your wagon"<<endl;
                    gameOver(3);
                    endStats(supplies, travelers[1].getName(), journey);
                    return 0;
                }
                else{
                    cout<<"You used one of your replacement axels to fix your wagon"<<endl;
                    supplies.setAxels(supplies.getAxels() - 1);
                }
                break;
                
            case 5:
            
                if(supplies.getTongues() == 0){
                    cout<<"You do not have the necessary parts to fix your wagon"<<endl;
                    gameOver(3);
                    endStats(supplies, travelers[1].getName(), journey);
                    return 0;
                }
                else{
                    cout<<"You used one of your replacement tongues to fix your wagon"<<endl;
                    supplies.setTongues(supplies.getTongues() - 1);
                }
                break;
        }
        
        //run raiders
        
        raiders(supplies, journey);
        
    }
}