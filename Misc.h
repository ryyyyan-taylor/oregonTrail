#ifndef MISC_H_
#define MISC_H_
#include "Player.h"
#include "Inventory.h"
#include "Travel.h"
using namespace std;

void endStats(Inventory&, string, Travel&);

bool ifNumber(string);

bool puzzle();

void displayMenu();

int hunt(Inventory&);

int misfortunes(string);

int raiders(Inventory&, Travel&);

void gameOver(int);

void win();

#endif