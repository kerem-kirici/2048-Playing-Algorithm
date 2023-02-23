# 2048 Playing Algorithm and Application
This C++ file contains a console app for 2048 Game which can be played by either a person or an algorithm. 

First of all some results of this program: 
* I've simulated 32 games played with this algorithm
  1) 3 of those games ended with '4096' number achieved and scores were about 55000.
  2) 16 of those games ended with '2048' number achieved and scores were about 31000.
  3) 13 of those games ended with '1024' number achieved and scores were about 15500.
  4) Maximum score was 58248 and minimum score was 12148.
  5) All scores have an arithmetic mean of about 27200 and standard deviation was about 12000.
  
* Which means about 50% of the time algorithm achieves the number '2048', about 40% of the time it achieves the number '1024' and 10% of the time '4096' number will be achieved.


Algorithm works like this:

In each step of calculation there is 2 sub-levels: Decision level and Probability level

1) In Decision Level there are 4 swiping directions and the player can decide which one is best.
2) In Probability Level every empty cell is filled with either 2 or 4 and each one of those possible positions needs to pass through a decision level itself.

Because these levels have multiple outcomes and one sub-level causes another to start. This process leads to a tree model.

In each Decision Level, the algorithm defines a chance of death and point of gain variables which will become next level's parent chance of death and point of gain.

In the deepest probability level's positions; if the game is finished parent chance of death increases, otherwise if the game continues the parent point of gain increases.

* When parent values of the lowest level increase that means the previous decision level's values are determined so the algorithm can select the lowest chance of death and highest point of gain. When all selections of that decision level are made, the previous probability level's positions has its own values. Which is the same situation as in the deepest probability level. That causes a chain because this starred section starts all over

That chain continues until all levels are complete. Which will cause the first level, as a decision level, to have a selection and that would be the best move for that position.
![alt text](https://github.com/kerem-kirici/2048-Playing-Algorithm/blob/main/2048Algorithm.jpg)
