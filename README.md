# oregonTrail

This was my final project from my Intro to Computing (CSCI1300) course. This is a copy of the old "Oregon Trail" DOS game, played in the command line.
I'll go over what each txt and Header / Class file does.
## Player
This handles each of the players in your party at any given time. Each player is an object containing info such as their name, whether they are currently sick, or if the player is already dead.
## River / Forts
The text files here provide the program with the info about each of the roadblocks along the journey. As lon as the formatting remains, these numbers can be changed and will affect gameplay. Each fort has a name and a distance into the total journey, while a river has a name, distance, as well as a depth.
## Store
The store is displayed when starting a new game and when visiting a fort.
## Travel
This covers most of the core gameplay aspects, including reading the text files at the start of a new game, reading the info about upcoming obstacles, running the different options when visiting a river or fort, advancing and setting the current date, and updating the number of miles which the player has traveled.
## Misc
Most of the other random game happenings are stored here. Functions stored here display the menu each turn, run the puzzles for hunting and getting attacked, and some general QOL functions. When the game ends, this outputs the final stats to a text file.
## Main
Self explanatory, the driver which will create the necessary objects and call all the necessary functions.
