# 2048 Playing Algorithm and Application
This C++ file contains a console app for 2048 Game which can be played by either a person or an algorithm. 


Algorithm works like this:

In each step of calculation there is 2 sub-levels: Decision level and Probability level

1) In Decision Level there are 4 swiping directions and the player can decide which one is best.
2) In Probability Level every empty cell is filled with either 2 or 4 and each one of those possible positions needs to pass through a decision level itself.

Because these levels have multiple outcomes and one sub-level causes another to start. This process leads to a tree model.

In each Decision Level, the algorithm defines a chance of death and point of gain variables which will become next level's parent chance of death and point of gain.

In the deepest probability level's positions; if the game is finished parent chance of death increases, otherwise if the game continues the parent point of gain increases.

* When parent values of the lowest level increase that means the previous decision level's values are determined so the algorithm can select the lowest chance of death and highest point of gain. When all selections of that decision level are made, the previous probability level's positions has its own values. Which is the same situation as in the deepest probability level. That causes a chain because this starred section starts all over

That chain continues until all levels are complete. Which will cause the first level, as a decision level, to have a selection and that would be the best move for that position.
