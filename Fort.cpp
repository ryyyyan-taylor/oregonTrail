#include <iostream>
#include <string>
#include "Fort.h"
using namespace std;

// used in reading the forth final

Fort::Fort(){
    name = "";
    distance = 0;
}

Fort::Fort(string a, int b){
    name = a;
    distance = b;
}

string Fort::getName(){
    return name;
}

void Fort::setName(string n){
    name = n;
}

int Fort::getDistance(){
    return distance;
}

void Fort::setDistance(int n){
    distance = n;
}