#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "Player.h"
#include "Travel.h"
#include "Inventory.h"
using namespace std;

void endStats(Inventory& supplies, string leader, Travel& journey){
    string filename = "results.txt";
    ofstream file(filename);
    
    //outputs the final stats and at the same time rights it to the results final
    cout<<"===FINAL STATS==="<<endl;
    cout<<"Party Leader: "<<leader<<endl;
    file<<"Party Leader: "<<leader<<endl;
    cout<<"Miles Traveled: "<<journey.getTotalMiles()<<"lbs"<<endl;
    file<<"Miles Traveled: "<<journey.getTotalMiles()<<"lbs"<<endl;
    cout<<"Food Remaining: "<<supplies.getFood()<<"lbs"<<endl;
    file<<"Food Remaining: "<<supplies.getFood()<<"lbs"<<endl;
    cout<<"Money: $"<<setprecision(2)<<supplies.getMoney()<<endl;
    file<<"Money: $"<<setprecision(2)<<supplies.getMoney()<<endl;
}

// used throughout the program to check that an input string is all numbers and not letters
bool ifNumber(string input){
    int numNums = 0;
    for(int i=0;i<input.length();i++){
        if(isdigit(input[i])){
            numNums++;
        }
        else if(input[i])
    }
    if(numNums == input.length()){
        return true;
    }
    else if(numNums != input.length()){
        return false;
    }
}

// runs the puzzle used for hunting and raider attacks
bool puzzle(){
    int num = rand() % 10 + 1;
    int guess;
    string input;
    
    cout<<"You will try to guess a number between 1 and 10."<<endl;
    cout<<"If you guess correct within 3 tries, you will be successful"<<endl;
    
    for(int i=0; i<3; i++){
        start:
        if(i==0){
            cout<<"First guess: "<<endl;
        }
        else if(i==1){
            cout<<"Second guess: "<<endl;
        }
        else if(i==2){
            cout<<"Third guess: "<<endl;
        }
        
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please enter a number between 1 and 10"<<endl;
            goto start;
        }
        guess=stoi(input);
        if(guess>10 || guess<1){
            cout<<"Enter a number between 1 and 10"<<endl;
            goto start;
        }
        
        if(guess == num){
            cout<<"You're correct! The number was " <<num<<endl;
            return true;
        }
        else{
            if(i==2){
                cout<<"Sorry, you failed"<<endl;
            }
            else{
                cout<<"Sorry, the number is not "<<guess<<" guess again"<<endl;
            }
        }
    }
    return false;
}

// displays the menu at the beginning of each turn
void displayMenu(){
    
    cout<<"\n===What would you like to do?==="<<endl;
    cout<<"1. Stop to rest"<<endl;
    cout<<"2. Continue on the trail"<<endl;
    cout<<"3. Hunt"<<endl;
    cout<<"4. Quit the trail"<<endl;
    
}

// hunting function when the player chooses to hunt
int hunt(Inventory& supplies){
    int z = rand() % 2 + 1;
    int in, animals = 0;
    bool hunt;
    string input;
    
    //rabbit
    if(z==2){
        rabChoice:
        animals++;
        cout<<"\nYou encountered a rabit! Would you like to hunt it?"<<endl;
        cout<<"1. Yes\n2. No"<<endl;
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose either 1. Yes or 2. No"<<endl;
            goto rabChoice;
        }
        in=stoi(input);
        if(in==1){
            hunt = puzzle();
            supplies.setBullets(supplies.getBullets() - 10);
            if(hunt==true){
                cout<<"Congratulations, you successfully hunted a rabit and gained 2lbs of food"<<endl;
                supplies.addFood(2); // if the hunt is successful, add for to the player's inventory
                animals++;
            }
            else if(hunt==false){
                cout<<"You were unsuccessful in hunting the rabit..."<<endl;
            }
        }
        else if(in==2){
            goto fox;
        }
        else if(in!=1 || in!=2){
            cout<<"Please choose either yes or no"<<endl;
            goto rabChoice;
        }
    }
    // hunting trip ends if the player does not have enough bullets to hunt the next animal
    if(supplies.getBullets()<10){
        cout<<"You ran out of bullets and could not continuing hunting..."<<endl;
        return 0;
    }
    
    //fox
    fox:
    z = rand() % 4 + 1;
    if(z<3){
        foxChoice:
        cout<<"\nYou encountered a fox! Would you like to hunt it?"<<endl;
        cout<<"1. Yes\n2. No"<<endl;
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose either 1. Yes or 2. No"<<endl;
            goto foxChoice;
        }
        in=stoi(input);
        if(in==1){
            hunt= puzzle();
            supplies.setBullets(supplies.getBullets() - 8);
            if(hunt==true){
                cout<<"Congratulations, you successfully hunted a fox and gained 5lbs of food"<<endl;
                supplies.addFood(5);
                animals++;
            }
            else if(hunt==false){
                cout<<"You were unsuccessful in hunting the fox..."<<endl;
            }
        }
        else if(in==2){
            goto deer;
        }
        else if(in!=1 || in!=2){
            cout<<"Please choose either yes or no"<<endl;
            goto foxChoice;
        }
    }
    if(supplies.getBullets()<10){
        cout<<"You ran out of bullets and could not continuing hunting..."<<endl;
        return 0;
    }
    
    //deer
    deer:
    z = rand() % 100 + 1;
    if(z<16){
        animals++;
        deerChoice:
        cout<<"\nYou encountered a deer! Would you like to hunt it?"<<endl;
        cout<<"1. Yes\n2. No"<<endl;
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose either 1. Yes or 2. No"<<endl;
            goto deerChoice;
        }
        in=stoi(input);
        if(in==1){
            hunt= puzzle();
            supplies.setBullets(supplies.getBullets() - 5);
            if(hunt==true){
                int deer = rand() % 55 + 30;
                cout<<"Congratulations, you successfully hunted a deer and gained "<<deer<<"lbs of food"<<endl;
                supplies.addFood(deer);
            }
            else if(hunt==false){
                cout<<"You were unsuccessful in hunting the deer..."<<endl;
            }
        }
        else if(in==2){
            goto bear;
        }
        else if(in!=1 || in!=2){
            cout<<"Please choose either yes or no"<<endl;
            goto deerChoice;
        }
    }
    if(supplies.getBullets()<10){
        cout<<"You ran out of bullets and could not continuing hunting..."<<endl;
        return 0;
    }
    
    //bear
    bear:
    z = rand() % 100 + 1;
    if(z<8){
        animals++;
        bearChoice:
        cout<<"\nYou encountered a bear! Would you like to hunt it?"<<endl;
        cout<<"1. Yes\n2. No"<<endl;
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose either 1. Yes or 2. No"<<endl;
            goto bearChoice;
        }
        in=stoi(input);
        if(in==1){
            hunt= puzzle();
            supplies.setBullets(supplies.getBullets() - 10);
            if(hunt==true){
                int bear = rand() % 350 + 100;
                cout<<"Congratulations, you successfully hunted a bear and gained "<<bear<<"lbs of food"<<endl;
                supplies.addFood(bear);
            }
            else if(hunt==false){
                cout<<"You were unsuccessful in hunting the bear..."<<endl;
            }
        }
        else if(in==2){
            goto moose;
        }
        else if(in!=1 || in!=2){
            cout<<"Please choose either yes or no"<<endl;
            goto bearChoice;
        }
    }
    
    if(supplies.getBullets()<12){
        cout<<"You ran out of bullets and could not continuing hunting..."<<endl;
        return 0;
    }
    
    //moose
    moose:
    z = rand() % 100 + 1;
    if(z<6){
        animals++;
        mooseChoice:
        cout<<"\nYou encountered a moose! Would you like to hunt it?"<<endl;
        cout<<"1. Yes\n2. No"<<endl;
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose to either 1. Yes or 2. No"<<endl;
            goto mooseChoice;
        }
        in=stoi(input);
        if(in==1){
            hunt= puzzle();
            supplies.setBullets(supplies.getBullets() - 12);
            if(hunt==true){
                int moose = rand() % 600 + 300;
                cout<<"Congratulations, you successfully hunted a bear and gained "<<moose<<"lbs of food"<<endl;
                supplies.addFood(moose);
            }
            else if(hunt==false){
                cout<<"You were unsuccessful in hunting the moose..."<<endl;
            }
        }
        else if(in!=1 || in!=2){
            cout<<"Please choose either yes or no"<<endl;
            goto mooseChoice;
        }
    }
    
    if(animals==0){
        cout<<"Sorry, you didn't encounter anything on your hunting trip"<<endl;
    }
}

// outputs the correct text for each different misfortune that may occur
// take innput of the name of the possibly sick party member
int misfortunes(string name){
    int chance = rand() % 5 + 1;
    int n;
    switch(chance){
        
        // one of the party members gets sick
        case 1:
            if(name=="You"){
                cout<<"\nOh no! You have gotten sick"<<endl;
            }
            else{
                cout<<"\nOh no! "<<name<<" has gotten sick!"<<endl;
            }
            
            return 1;
            break;
        
        // one of the oxen dies
        case 2:
        
            cout<<"Oh no! One of your oxen has died!"<<endl;
            return 2;
            break;
        
        // wagon part breaks
        case 3:
        
            n = rand() % 3 + 1;
            if(n == 1){
                cout<<"Oh no! One of your wheels has broken!"<<endl;
                return 3;
            }
            else if(n == 2){
                cout<<"Oh no! One of your axels has broken!"<<endl;
                return 4;
            }
            else if(n ==3){
                cout<<"Oh no! One of your tongues has broken!"<<endl;
                return 5;
            }
            break;
        
        // nothing happens
        default:
            return 6;
    }
}

// compute chance of raider attack and run raider attack if needed
int raiders(Inventory& supplies, Travel& journey){
    // compute the chance of raiders
    float x = pow((journey.getTotalMiles()/100)- 4, 2);
    float y = pow((journey.getTotalMiles()/100)- 4, 2);
    float z = ((x+ 72)/(y+ 12))- 1;
    float chance = z/10;
    float prob = 10/chance;
    float raiders = rand() % 100 + 1;
    // run raider attack if probability is enough
    if(raiders<=prob){
        int choice;
        string input;
        string part;
        bool fight = false;
        int ranD;
        double steal;
        cout<<"\nThere's a party approaching, they look hostile!"<<endl;
        input:
        cout<<"\nWhat would you like to do?"<<endl;
        cout<<"1. Run"<<endl;
        cout<<"2. Attack"<<endl;
        cout<<"3. Surrender"<<endl;
        cin>>input;
        if(ifNumber(input)==false){
            cout<<"Please choose one of the given options"<<endl;
            goto input;
        }
        choice=stoi(input);
        switch(choice){
            
            // run away
            case 1:
                // determine which wagon part is dropped
                ranD = rand() % 3 + 1;
                switch(ranD){
                    case 1:
                        part = "axel";
                        supplies.setAxels(supplies.getAxels() - 1);
                        break;
                    case 2:
                        part = "wheel";
                        supplies.setWheels(supplies.getWheels() - 1);
                        break;
                    case 3:
                        part = "tongue";
                        supplies.setTongues(supplies.getTongues() - 1);
                        break;
                }
                cout<<"Your party escaped, but in your haste you left behind an oxen, 10lbs of food, and 1 "<<part<<endl;
                supplies.setOxen(supplies.getOxen() - 1);
                supplies.decreaseFood(10);
                break;
            
            // fight back
            case 2:
                // don't let them attack if they don't have enough bullets
                if(supplies.getBullets()<50){
                    cout<<"You tried to fend them off but you didn't have enough bullets to protect your party"<<endl;
                    fight = false;
                    goto lost;
                }
                
                // run puzzle to see if player wins
                fight = puzzle();
                
                lost:
                if(fight == true){
                    cout<<"Congragulations you won! You got 50lbs of food, $60, and 50 bullets from the fools that tried to mess with you!"<<endl;
                    supplies.addFood(50);
                    supplies.setBullets(supplies.getBullets() + 50);
                    supplies.setMoney(supplies.getMoney() + 60);
                }
                else if(fight == false){
                    double stolen = supplies.getMoney() * 0.25;
                    cout<<"You lost! The raiders stole $"<<setprecision(2)<<stolen<<" and you used 50 bullets trying to fend them off"<<endl;
                    supplies.pay(stolen);
                    supplies.setBullets(supplies.getBullets() - 50);
                    if(supplies.getBullets()<0){
                        supplies.setBullets(0);
                    }
                }
                break;
            
            // surrender
            case 3:
                steal = supplies.getMoney() * 0.25;
                cout<<"You surrendered to the raiders and they stole $"<<fixed<<setprecision(2)<<steal<<endl;
                supplies.pay(steal);
                break;
                
            default:
                cout<<"Please choose one of the given choices"<<endl;
                goto input;
        }
    }
}

// output the correct endgame text for each different condition that the player can loose for
void gameOver(int reason){
    switch(reason){
        
        // quit from the menua
        case 0:
            cout<<"\nThanks for playing"<<endl;
            break;
          
        // party leader dies    
        case 1:
            cout<<"\n\nYou made a valiant effort, but you have died on your journey"<<endl;
            cout<<"Thanks for playing"<<endl;
            break;
        
        // all oxen die    
        case 2:
            cout<<"\n\nYou made a valiant effort, but all of your oxen have died along your journey"<<endl;
            cout<<"Thanks for playing"<<endl;
            break;
        
        // can't fix wagon    
        case 3:
            cout<<"\n\nYou made a valiant effort, but your wagon broke along your journey and you couldn't fix it"<<endl;
            cout<<"Thanks for playing"<<endl;
            break;
        
        // ran out of food    
        case 4:
            cout<<"\n\nYou made a valiant effort, but your party ran out of food along the trail"<<endl;
            cout<<"Thanks for playing"<<endl;
            break;
        
        // did not make it before winter    
        case 5:
            cout<<"\n\nYou madea valiant effort, but you did not make it to Oregon City before winter came"<<endl;
            cout<<"Thanks for playing"<<endl;
            break;
    }
}

// output winning text
void win(){
    cout<<"Congratulations, you made it the full 2040mi to Oregon City!"<<endl;
}