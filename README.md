# 2048 Playing Algorithm and Application
This C++ file contains a console app for 2048 Game which can be played by either a person or an algorithm. 

First of all some results of this program (which calculates only 3 layers of death chance and gain point): 
* I've simulated 100 games played with this algorithm
  1) 38 of those games ended with '4096' number achieved and scores were listed between 51000 and 80000 with standard deviation of 9200.
  2) 56 of those games ended with '2048' number achieved and scores were about 34000 with standard deviation of 3400.
  3) 6 of those games ended with '1024' number achieved and scores were about 16500 with standard deviation of 450.
  4) Maximum score was 79864 (4096) and minimum score was 15808 (1024).
  5) All scores have an arithmetic mean of about 43690 and general standard deviation was about 16500.
  
* Which means about
    4096 -> 38%
    2048 -> 56%
    1024 -> 6%
  of times these numbers will be achived.

* So this code guarantees a victory of achieving '2048' 94% of the time, which is pretty high, with only 3 layers of death chance and gain point calculations. If your computer has more power than mine you can guarantee that every time code works it wins the game with more layers of calculation.


Algorithm works like this:

In each step of calculation there is 2 sub-levels: Decision level and Probability level

1) In Decision Level there are 4 swiping directions and the player can decide which one is best.
2) In Probability Level every empty cell is filled with either 2 or 4 and each one of those possible positions needs to pass through a decision level itself.

Because these levels have multiple outcomes and one sub-level causes another to start. This process leads to a tree model.

In each Decision Level, the algorithm defines a chance of death and point of gain variables which will become next level's parent chance of death and point of gain.

In the deepest probability level's positions; if the game is finished parent chance of death increases, otherwise if the game continues the parent point of gain increases.

* When parent values of the lowest level increase that means the previous decision level's values are determined so the algorithm can select the lowest chance of death and highest point of gain. When all selections of that decision level are made, the previous probability level's positions have their own values. Which is the same situation as in the deepest probability level. That causes a chain because this starred section starts all over

That chain continues until all levels are complete. Which will cause the first level, as a decision level, to have a selection and that would be the best move for that position.
![alt text](https://github.com/kerem-kirici/2048-Playing-Algorithm/blob/main/2048Algorithm.jpg)
