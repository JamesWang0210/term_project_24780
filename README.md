# Term Project 24780
This is the final version for both the Single Player and the Multi Player mode.

## General Instruction: 
We create a game called StickyMan, which allow the users to interact with the game characters by using keyboard. 

The game has two modes: one is Single Player mode and the other is Multiplayer mode. In Single Player mode, user can fight against the computer controlled characters; user can control one character (player 1) by using certain keys, while the computer controls the enemies (up to 7). In Multiplayer mode, it requires two players to fight against each other; there are two characters with different colors controlled separately by two users using different keys.

## Definition & Declaration: 
In the game, players can do many actions like move (left/right), jump, crouch, punch, kick and shoot, etc. These actions are written as functions and defined and declared in the source file and a class in header file. 

The main class for this game is player, which contains the majority of functions declaration and variable definition. Also, there is two classes for menu part and environment part respectively, which create the menu and the background of the game.

## Default Keyboard Setup:
•	Choose Single Player/Multi Player and press ENTER. You can use the UP and DOWN arrows to make your selection.<br />
•	If you choose Multi Player, you can select “New Player” and insert a nickname for player 1. Then choose “New Player” and insert a nickname for Player 2. Press ENTER to start.<br />
•	If you choose Single Player, you only need to enter your name one time.<br />

## Specfic Keyboard Settings
  Player 1:<br /> 
  A: move left<br />
  S: crouch<br />
  D: move right<br />
  W: jump<br />
  Z: punch in normal state<br />
  X: kick<br />
  C: shoot in shooting state<br />
  2: enter shooting state<br /> 
  1: enter normal state<br />
  3: enter knife state<br />
  Z: attack with a knife in knife state<br />

  Player 2:<br /> 
  J: move left<br />
  K: crouch<br />
  L: move right<br />
  I: jump<br />
  B: punch in normal state<br />
  N: kick<br />
  M: shoot in shooting state<br />
  8: enter shooting state<br /> 
  7: enter normal state<br />
  9: enter knife state<br />
  B: attack with a knife in knife state<br /> 
