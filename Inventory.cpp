#include <iostream>
#include <string>
#include "Inventory.h"
using namespace std;

// nothing special, keeps all of the necessary supplies values throughout the game

Inventory::Inventory(){
    oxen=0, food=0, medkits=0, bullets=0,  parts=0, tongues=0, axels=0, wheels=0;
    money=0;
}

int Inventory::getOxen(){
    return oxen;
}

void Inventory::setOxen(int n){
    oxen = n;
}

int Inventory::getFood(){
    return food;
}

void Inventory::setFood(int n){
    food = n;
}

void Inventory::decreaseFood(int n){
    food = food - n;
}

void Inventory::addFood(int n){
    food = food + n;
}

int Inventory::getMedkits(){
    return medkits;
}

void Inventory::setMedkits(int n){
    medkits = n;
}

int Inventory::getBullets(){
    return bullets;
}

void Inventory::setBullets(int n){
    bullets = n;
}

int Inventory::getParts(){
    return tongues+axels+wheels;
}

int Inventory::getTongues(){
    return tongues;
}

void Inventory::setTongues(int n){
    tongues = n;
}

int Inventory::getWheels(){
    return wheels;
}

void Inventory::setWheels(int n){
    wheels = n;
}

int Inventory::getAxels(){
    return axels;
}

void Inventory::setAxels(int n){
    axels = n;
}

double Inventory::getMoney(){
    return money;
}

void Inventory::setMoney(double n){
    money = n;
}

void Inventory::pay(double n){
    money = money - n;
}