#ifndef PLAYER_H_
#define PLAYER_H_
using namespace std;

class Player{
    
        private:
            
            string name;
            bool dead, sick;
            
        public:
            
            Player();
            void setName(string);
            string getName();
            void kill();
            bool ifDead();
            void getSick();
            bool ifSick();
};

#endif