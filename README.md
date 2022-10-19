# US-Projekat-Blackjack :spades: :diamonds: :clubs: :hearts:
<p align="justify">US-Projekat-Blackjack is a program, specifically, a game demo made as a part of the Embedded Systems course. It was written in C++ and made for use and testing in mbed simulator. The game is supposed to be a simplified version of the traditional casino banking game Blackjack. This repository contains a code for the game and detailed documentation written in Bosnian language.</p> 
<p align="center">
  <br>
  <img align="middle" src="https://github.com/osaric1/US-Projekat-Blackjack/blob/main/BlackjackMain.png" height="300" width="300" >
</p>

<p align="center">
  <img src="https://j.gifs.com/NOBkB8.gif" alt="animated" height="300" width="300" />
</p>

## Characteristics  
This Blackjack version is very simplified compared to the real game. Like in real life, at the beginning of the game the player is dealt two random cards. Player can then choose to tie or hit. After making a move, the dealer will make his move and after that the winner is decided. Before starting a new game, player chooses how many chips he wants to start with. These chips are updated as the game progresses.
<p align="center">
  <br>
  <img align="middle" src="https://github.com/osaric1/US-Projekat-Blackjack/blob/main/BlackjackGameplay.png" height="300" width="300" >
</p>

## Limitations 
Since it is a demo, the program does not have any kind of data persistence which means that all progress is lost once the player closes the game or recompiles it. In the beginning there were plans to add multiplayer, for example two or more players all participating in a single game of Blackjack. However, mostly due to time limitations, this feature was scrapped.  

## Testing 
Anybody interested in playing around with the demo or testing it can do so by visiting https://labs.mbed.com/simulator (until December 2022). If you're reading this after December 2022, you can set up this simulator on your local machine by following the appropriate guide in the readme section https://github.com/ARMmbed/mbed-simulator#readme. In order for the code to work you need to add an LCD display component `ST7789H2 LCD + FT6x06 Touch Screen`. After doing so, you can copy the code found in Blackjack.cpp and run the demo. 
