#include <iostream>
#include <string>
#include "River.h"
using namespace std;

// used in reading the river file

River::River(){
    name = "";
    depth = 0;
    distance = 0;
}

River::River(string a, int b, int c){
    name = a;
    distance = b;
    depth = c;
}

string River::getName(){
    return name;
}

void River::setName(string n){
    name = n;
}

int River::getDistance(){
    return distance;
}

void River::setDistance(int n){
    distance = n;
}

int River::getDepth(){
    return depth;
}

void River::setDepth(int n){
    depth = n;
}