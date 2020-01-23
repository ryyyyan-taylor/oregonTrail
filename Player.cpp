#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

// used to keep track of names and if players are dead mostly

Player::Player(){
    
    name = "";
    dead = false;
    sick = false;
}

void Player::setName(string in){
    name = in;
}

string Player::getName(){
    return name;
}

void Player::kill(){
    dead = true;
}

bool Player::ifDead(){
    return dead;
}

void Player::getSick(){
    sick = true;
}

bool Player::ifSick(){
    return sick;
}