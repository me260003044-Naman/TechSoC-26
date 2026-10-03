## Problem Understanding
**What the problem is asking:
Problem is asking us to create an ability based battle simulator involving multiple features such as duel, AI duel, Tournament mode.

## **Key concepts involved:**

Object Oriented Programing,
Creating a common class for different Benders and duel class,ai duel class definging their constructors to take the data from different objects of bender class and performing the task they are supposed to do.
Using duel class to define a tournament class where we perform multiple duels inside a tournament class to get a winner among multiple benders.

We used:
Classes
Defined a data type through structure for moves involving move name and its power and also the effect it carries(if it does).
Used friend class to use private data from a class in another class(ex. Duel was a friend class of Bender and Tournament was a friend class of both Duel and Bender).


##  Conceptual Learning

### **New Concepts I Discovered**
Structure:to define a datatype of my use.

### **How I Applied These Concepts**
I needed a set containing move_name ,move_power and move_effect so i defined a structure move which had 2 things first the name of move as a string and 2nd the power of that move as an integer and also the effect that move will produce as a string.
I also needed a pair of elements where 1st being dominant over the 2nd.I could have used map here but i was getting confused on the algorithms i had to perform on it and i already got familiar with using structure so i used that.


### **Real-World Connections**
In a situation where u have to compare any 2 or multiple people/object over different things or you just have to give marking to a particular person/object on the basis of multiple stats u can use this

For example: in valo after the game ends, the scoreboard shows ACS(Average Combat Score).It can be calculated by creation a class for every particular player having class attribute called ACS and making a class for rounds calculating the ACS for each class on the basis of abilities used, value gained by abilities, kills, assists and after the completion of game taking an average of all the objects(different rounds) of round class.



