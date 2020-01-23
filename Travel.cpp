#include <iostream>
#include <fstream>
#include <string>
#include "Travel.h"
#include "River.h"
#include "Fort.h"
#include <algorithm>
#include <cctype>
using namespace std;

// split function from earlier homeworks
void split (string str, char c, string array[], int size)
{
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
            array[count++] = word;
            word = "";
        } else {
            word = word + str[i];
        }
    }
 }


// initialize arrays of days in each month and names of each month
Travel::Travel(){
    for(int i=0;i<13;i++){
        if(i==0){
            monthDays[i] = 0;
        }
        else if(i==1||i==3||i==5||i==7||i==8||i==10||i==12){
            monthDays[i] = 31;
        }
        else if(i==2){
            monthDays[i] = 28;
        }
        else{
            monthDays[i] = 30; 
        }
    }
    for(int i=0;i<13;i++){
        if(i==0)
            monthNames[i] = "";
        if(i==1)
                monthNames[i] = "January";
        if(i==2)
            monthNames[i] = "February";
        if(i==3)
            monthNames[i] = "March";
        if(i==4)
            monthNames[i] = "April";
        if(i==5)
            monthNames[i] = "May";
        if(i==6)
            monthNames[i] = "June";
        if(i==7)
            monthNames[i] = "July";
        if(i==8)
            monthNames[i] = "August";
        if(i==9)
            monthNames[i] = "September";
        if(i==10)
            monthNames[i] = "October";
        if(i==11)
            monthNames[i] = "November";
        if(i==12)
            monthNames[i] = "December";
    }
    totMiles = 0, numForts = 0, numRivers = 0;
}

//read from the forts file
void Travel::readForts(){
    string line = "";
    string name = "";
    int distance;
    int v = 0;
    char m = ' ';
    int x = 0;
    string read[20];
    string distanceMi[20];
    string filename = "forts.txt";
    
    ifstream file(filename);
    
    // parse through the file and put each line in array of strings
    while(getline(file,line)){
        read[v] = line;
        v++;
    }
    
    for(int i=0; i<v; i++){
        // every odd line is the name of the fort
        name = read[i];
        i++;
        
        // split the miles off the end of the distance
        split(read[i], m, distanceMi, 20);
        // every even line is the distance
        distance = stoi(distanceMi[0]);
        
        // use temporary fort object to initialize array of fort objects in order of distance
        Fort fortsobj;
        fortsobj.setName(name);
        fortsobj.setDistance(distance);
        forts[x] = fortsobj;
        x++;
    }
}

// read from the rivers files
void Travel::readRivers(){
    string line = "";
    string name = "";
    int depth;
    int distance;
    int v = 0, x = 0;
    char m = 'm';
    string Line[20];
    string read[20];
    string filename = "rivers.txt";
    string str = "";
    
    ifstream file(filename);
    
    // parse through the rivers file and fill and array of strings
    while(getline(file,line)){
        read[v] = line;
        v++;
    }
    
    for(int i=0; i<v; i++){
        // every odd line
        name = read[i];
        i++;
        str = "";
        
        // split at the mi at the end of the distance
        split(read[i], m, Line, 20);
        // distance will be the first item in that array
        distance = stoi(Line[0]);
        // parse through the second array and only add numbers to the depth
        for(int j=0;j<Line[1].length(); j++){
            string temp = Line[1];
            if(isdigit(temp[j])){
                str += temp[j];
                depth = stoi(str);
            }
        }
        
        // use a temporary river objec to initiate string of river objects
        River riverObj;
        riverObj.setName(name);
        riverObj.setDepth(depth);
        riverObj.setDistance(distance);
        rivers[x] = riverObj;
        x++;
    }
}

// compare the distances of the next river and fort and return the distance of the next one
int Travel::getNextMilestone(){
    int tempRiv, tempFort;
    tempRiv = rivers[numRivers].getDistance();
    tempFort = forts[numForts].getDistance();
    if(tempRiv>tempFort){
        return tempFort;
    }
    else if(tempFort>tempRiv){
        return tempRiv;
    }
}

// compare the next fort and river and whichever is closer is the type of the next milestone
string Travel::getMilestoneType(){
    int tempRiv, tempFort;
    tempRiv = rivers[numRivers].getDistance();
    tempFort = forts[numForts].getDistance();
    if(tempRiv>tempFort){
        return "fort";
    }
    else if(tempFort>tempRiv){
        return "river";
    }
}

// getters and setters for the forts and rivers
void Travel::visitFort(){
    numForts++;
}

void Travel::crossRiver(){
    numRivers++;
}

string Travel::getRiverName(){
    return rivers[numRivers].getName();
}

int Travel::getRiverDepth(){
    return rivers[numRivers].getDepth();
}

string Travel::getFortName(){
    return forts[numForts].getName();
}

void Travel::advanceMiles(int miles){
    totMiles = totMiles + miles;
}

void Travel::setTotalMiles(int miles){
    totMiles = miles;
}

int Travel::getTotalMiles(){
    return totMiles;
}

// advance days and advance the month as well if necessary
void Travel::advanceDays(int days){
    curDay = curDay + days;
    if(curDay>monthDays[curMonth]){
        curDay = curDay - monthDays[curMonth];
        curMonth++;
    }
}

// initialze day and month
void Travel::setDate(int day, string month){
    curDay = day;
    for(int i=0; i<13; i++){;
        if(monthNames[i] == month){
            curMonth = i;
        }
    }
}

int Travel::getCurDay(){
    return curDay;
}

string Travel::getCurMonth(){
    return monthNames[curMonth];
}