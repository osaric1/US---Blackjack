#include "mbed.h"
#include <time.h>
#include <string>
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"
#include <vector>


const int CARD_LENGHT = 51;
const int CARD_WIDTH = 38;
uint16_t card_template[CARD_LENGHT][CARD_WIDTH] ={};

const char* placeBetText[] = {"PLACE A BET", ">> 50", ">> 100", ">> 150", ">> 200", "Quit", "Current bet: ", "Play"};
const char* menuText[] = {"Start", "How To Play","Highscore", "About", "Quit"};
const char* aboutText[] = {"Mbed OS application", "Build time: ", "Version: v0.9", "Contact: ", "dsiljegovi1@etf.unsa.ba", "osaric1@etf.unsa.ba"};

const char* firstPageText[] = {
    "Continue", "INTRO", "Blackjack is played against", "the dealer, who also has a",
    "hand of his own. The dealer", "opens the game by dealing", "two cards to everyone. A", "player examins his cards to",
    "decide if he wants to hit,","or stand. Though there are..."
    
};
const char* secondPageText[] =
{
    "Continue", "several players at a table","each one is playing the","dealer individually. The","object of Blackjack is to",
    "beat the dealer total without", "going over a total of 21.", "CARDS", "The cards are counted and..."
};

const char* thirdPageText[] = {
    "totaled as follows:", ">> 1-10 = number on the card", ">> J, Q, K = 10 points", ">> A = 1 or 11 (situational)",
    "OPTIONS", "Hit - you want another card", "Stand - don't want a new card", "Blackjack! -  you got an ace"
};

const char* playText[] = {
    "DEALER", "YOU", "TIE!", "BLACKJACK!", "BUST!", "Stand", "Hit", "Continue"
};

const char* scoreText[] = {
    "You bottomed out.", "FINAL SCORE", "Return"
};

const char* highScoreText[] = {
    "Back", "HIGHSCORES"
};

const char* introText[] = {
      "UGRADBENI SISTEMI 2021", "DENINA SILJEGOVIC", "OMAR SARIC", "BLACKJACK", "PRESS <ANY> TO CONTINUE"  
};

/* 10 x 8*/

uint16_t color = 0x00;

uint16_t sveBoje[] = {0x54D,0xFA49,0x4208};

TS_StateTypeDef  TS_State = {0};

int indeks = 0;

const char* nums[] = { "50", "100", "150", "200", "250", "300", "350", "400", "450",
"500", "550", "600", "650", "700", "750" ,"800", "850", "900", "950", "1000"};


int highscores[] = {0,0,0};

/* niz koji se sastoji od slova/brojeva reprezentovanih u pikselima, gdje svaki piksel predstavlja RGB kombinaciju brojeva
zapisanih u obliku heksadecimalnog broja */
uint16_t numbers[13][10][8] = {
   //broj A 
{
    0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,color,color,color,color,0xFFFF,0xFFFF,
    0xFFFF,color,color,color,color,color,color,0xFFFF,
    color,color,color,0xFFFF,0xFFFF,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
},

    //2
{
    0xFFFF,color,color,color,color,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,color,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,color,color,color,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,color,color,color,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,color,color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    
},

    //3
{
   0xFFFF,color,color,color,color,color,color,0xFFFF,
   color,color,color,color,color,color,color,color,
   color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
   0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
   0xFFFF,0xFFFF,0xFFFF,color,color,color,color,0xFFFF,
   0xFFFF,0xFFFF,0xFFFF,color,color,color,color,0xFFFF,
   0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
   color, color, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
   color,color,color,color,color,color,color,color,
   0xFFFF,color,color,color,color,color,color,0xFFFF,
    
},
    //4
{
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,color,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,color,color,color,color,0xFFFF,
    0xFFFF,0xFFFF,color,color,color,color,color,0xFFFF,
    0xFFFF,color,color,color,0xFFFF,color,color,0xFFFF,
    color,color,color,0xFFFF,0xFFFF,color,color,0xFFFF,
    color,color,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF
},
    //5
{
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color,color,color,color,color,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,0xFFFF,

 
},
    //6
{
    0xFFFF,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    color, color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color, color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color,color,color,color,color,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,color,color,color,color,color,color,
    0xFFFF,color,color,color,color,color,color,0xFFFF,
},
    //7
{
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,color,color,
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,color,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,color,color,color,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,color,color,color,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,color,color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color,color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF
},
    //8
{
    0xFFFF,color,color,color,color,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    0xFFFF,color,color,color,color,color,color,0xFFFF,
    0xFFFF,color,color,color,color,color,color,0xFFFF,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,color,color,color,color,color,color,
    0xFFFF,color,color,color,color,color,color,0xFFFF,
},
    //9
{
    0xFFFF,color,color,color,color,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    0xFFFF,color,color,color,color,color,color,color,
    0xFFFF,color,color,color,color,color,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,0xFFFF,
},
    //10
{
    color,color,0xFFFF,color,color,color,color,color,
    color,color,0xFFFF,color,color,color,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,color,color,color,
    color,color,0xFFFF,color,color,color,color,color,
},
    //J
{
    color,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,
    color,color,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,
    color,color,0xFFFF,0xFFFF,color,color,0xFFFF,0xFFFF,
    color,color,color,color,color,color,color,color,
    0xFFFF,color,color,color,color,color,color,0xFFFF,
},
    //K
{
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,color,color,color,
    color,color,0xFFFF,0xFFFF,color,color,color,0xFFFF,
    color,color,0xFFFF,color,color,color,0xFFFF,0xFFFF,
    color,color,color,color,color,0xFFFF,0xFFFF,0xFFFF,
    color,color,color,color,color,0xFFFF,0xFFFF,0xFFFF,
    color,color,0xFFFF,color,color,color,0xFFFF,0xFFFF,
    color,color,0xFFFF,0xFFFF,color,color,color,0xFFFF,
    color,color,0xFFFF,0xFFFF,0xFFFF,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
},
    //Q
{
    0xFFFF,color,color,color,color,color,color,color,
    color,color,color,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,0xFFFF,0xFFFF,0xFFFF,color,color,
    color,color,0xFFFF,color,color,0xFFFF,color,color,
    color,color,0xFFFF,color,color,color,color,color,
    color,color,0xFFFF,0xFFFF,color,color,color,0xFFFF,
    color,color,color,color,color,color,color,color,
    0xFFFF,color,color,color,color,0xFFFF,color,color,
}
    
};

/*  
    index 0 => club
    index 1 => heart
    index 2 => spade
    index 3 => diamond
*/

const uint16_t suitsPixel[4][22][22] = {
    
 {
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xFFFF, 0xFFFF,0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xFFFF, 0xFFFF,0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xFFFF, 0xFFFF,0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xFFFF, 0xFFFF,0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,
    
    0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00,
    
    0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0x00,0x00,0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0x00,0x00,0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF
},
    
{
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,

    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,
    
    0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    
    0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFA49,0xFA49,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
}, 

{
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00, 0x00, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00, 0x00, 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
   
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
    
    0xFFFF,0xFFFF,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFFFF,0xFFFF,
    0xFFFF,0xFFFF,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xFFFF,0xFFFF,
    
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    
    0xFFFF, 0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF,0x00,0x00,0xFFFF, 0xFFFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF,0x00,0x00,0xFFFF, 0xFFFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFFFF, 0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 

    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00, 0xFFFF, 0xFFFF, 0x00, 0x00, 0x00, 0x00,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,

    
},

{
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,
    0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF,

    0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFA49,0xFA49,0xFA49,0xFA49,0xFA49, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF, 0xFFFF,0xFFFF,
    
}
    
};

int countDigit(int number) {
   int count = 0;
   if(number == 0) return 1;
   while(number != 0) {
      number = number / 10;
      count++;
   }
   return count;
}

/* funkcija zadužena za osvježavanje top 3 liste u prozoru highscore */
void refreshHighScores(int score){
    if (score > highscores[0])
    {
        highscores[2] = highscores[1];
        highscores[1] = highscores[0];
        highscores[0] = score;
    }

    else if (score > highscores[1])
    {
        highscores[2] = highscores[1];
        highscores[1] = score;
    }

    else if (score > highscores[2])
        highscores[2] = score;
}

enum Suits{
    CLUB, HEART, SPADE, DIAMOND
};

enum Status{
    Beginning, InProgress, Ended
};

class Card{
    std::string value;
    Suits suit;
    public:
    
    Card(std::string value, Suits suit){
        this->value = value;
        this->suit = suit; 
    }
    
    Card(){}
    
    std::string getValue() const{
        return value;
    }
    
    Suits getSuit() const{
        return suit;
    }
    
    void drawCard(int positionX, int positionY, bool hide = false);
    
};

/* Funkcija za crtanje simbola karte */
void drawSuit(const uint16_t suit[22][22],int positionX, int positionY){
    for(int i = 0; i< 22; i++)
        for(int j = 0; j < 22; j++){
            BSP_LCD_DrawPixel(j+positionX,i+positionY, suit[i][j]);
        }
}

/* Funkcija za crtanje vrijednosti karte */
void drawNum(Card card, int positionX, int positionY){
    int index = 0;
    std::string val = card.getValue();
    
    if(val == "J")index = 10;
    else if(val == "K") index = 11;
    else if(val == "Q") index = 12;
    else if(val == "A") index = 0;
    else index = std::stoi(val)-1;
    
    for(int i = 0; i< 10; i++)
        for(int j = 0; j < 8; j++){
            BSP_LCD_DrawPixel(j+positionX,i+positionY, numbers[index][i][j]);
        }
}

void Card::drawCard(int positionX, int positionY, bool hide){
    for(int i = 0; i< CARD_LENGHT; i++)
        for(int j = 0; j < CARD_WIDTH; j++){
            //prvo što će se crtati na ekranu je bijela pozadina karata nakon čega se dodaju odgovarajući broj i tip karte tj. suit
            BSP_LCD_DrawPixel(j+positionX,i+positionY, card_template[i][j]);
        }
    
    if(hide){
        for(int i = 0; i< CARD_LENGHT-6; i++)
            for(int j = 0; j < CARD_WIDTH-6; j++){
                //prvo što će se crtati na ekranu je bijela pozadina karata nakon čega se dodaju odgovarajući broj i tip karte tj. suit
                BSP_LCD_DrawPixel(j+positionX+3,i+positionY+3, 0xFA49);
            }
    }
    else{
        drawSuit(suitsPixel[suit],positionX+8,positionY+12);
        drawNum(*this,positionX+2,positionY+2);
        drawNum(*this,positionX+28,positionY+37);
    }
}


class Deck{
    std::vector<Card> cards;
    
    public:
    
    Card &operator[](int indeks){
        return cards[indeks];
    }
    
    Deck(std::vector<Card> cards){
        this->cards = cards;
    }
    
    std::vector<Card> getCards() const {
        return cards;
    }
    
    Deck(const Deck &deck){
        this->cards = deck.getCards();
    }
    
    
    Deck(){}
    
    Deck shuffle();
    
};
/* Funkcija za miješanje špila karata */
Deck Deck::shuffle(){
    // Initialize seed randomly
    srand(time(0));
  
    for (int i=0; i< cards.size() ; i++)
    {
        int r = i + (rand() % (52 -i));
  
        std::swap(cards[i], cards[r]);
    }
    return *this;
}

/* Klasa ima dosta atributa iz razloga što je struktura programa takva da smo bili primorani
da neke vrijednosti/varijable stavimo kao atribute klase, da ne bi dolazilo do
nepotrebnih komplikacija */

class Blackjack{
    Deck deck;
    std::vector<Card> userCards;
    std::vector<Card> dealerCards;
    int currentCard = 0;
    Status gameStatus;
    int score = 0;
    int chips;
    int totalUser = 0;
    int totalDealer = 0;

    public:
    
    Blackjack(Deck deck){
        this->deck = deck;
    }
    
    void resetGame(){
        userCards.resize(0);
        dealerCards.resize(0);
        currentCard = 0;
        totalUser = 0; 
        totalDealer = 0;
        gameStatus = Beginning;
    }
    void setDeck(Deck deck){
        this->deck = deck;
    }
    
    void setChips(int chips){
        this->chips = chips;
    }
    
    int getChips() const{
        return chips;
    }
    
    void setScore(int score){
        this->score = score;
    }
    
    int getScore() const{
        return score;
    }
    
    void setTotalUser(int totalUser){
        this->totalUser = totalUser;
    }
    
    int getTotalUser() const{
        return totalUser;
    }
    
    void setTotalDealer(int totalDealer){
        this->totalDealer = totalDealer;
    }
    
    int getTotalDealer() const{
        return totalDealer;
    }
    
    std::vector<Card> getUserCards() const{
        return userCards;
    }
    
    std::vector<Card> getDealerCards() const{
        return dealerCards;
    }
    
    Deck getDeck() const{
        return deck;
    }
    
    int compareTotals();
    
    Status getStatus()const{
        return gameStatus;
    }
    
    void actionHit(int initialBet);
    
    void dealerPlays(bool natural, int initialBet);
    
    Blackjack(Deck deck, int chips){
        this->deck = deck;
        this->chips = chips;
        this->gameStatus = Beginning;
    }
    
    void addUserCard(Card card){
        userCards.insert(userCards.end(), card);
    }
    
    void addDealerCard(Card card){
        dealerCards.insert(dealerCards.end(), card);
    }
    
    void setUp(int initialBet);

    void setStatus(Status stat){
        gameStatus = stat;
    }
    
};

/* Header funckije smo ovdje premjestili iz razloga što je 
drawPlay potrebna jednoj od sljedećih metoda */

void drawPlay(Blackjack blackjack);

int Blackjack::compareTotals(){
    if(totalUser > 21) return -1;
    else if(totalDealer > 21) return 1;
    return totalDealer - totalUser;
}

void Blackjack::setUp(int initialBet){
    addUserCard(deck.getCards().at(0));
    addDealerCard(deck.getCards().at(1));
    addUserCard(deck.getCards().at(2));
    addDealerCard(deck.getCards().at(3));
    
    /* Pamti trenutnu kartu na vrhu špila */
    currentCard = 4;
    std::string temp = "";
    
    /* Može ostati userCards veličina jer na početku i igrač i diler imaju isti broj karata */
    for(int i = 0; i < userCards.size(); i++){
        /* Računanje inicijalnog broja poena za igrača */
       temp = userCards[i].getValue();

        if(temp == "A"){
            if(totalUser <= 11)
                totalUser += 11;
            else totalUser += 1;
        }
        else if(temp == "J" || temp == "K" || temp =="Q") totalUser += 10;
        else totalUser += std::stoi(temp);
        
        
        /* Računanje inicijalnog broja poena za dilera */
        temp = dealerCards[i].getValue();
        
        if(temp == "A"){
            if(totalDealer <= 11)
                totalDealer += 11;
            else totalDealer += 1;
        }
        
        else{
            if(temp == "J" || temp == "K" || temp =="Q") totalDealer += 10;
            else totalDealer += std::stoi(temp);
        }
    }
    
    /* Korisnik automatski gubi ako pređe 21 */
    if(totalUser > 21){ 
        chips -= initialBet;
        gameStatus = Ended;
    }
    else if(totalUser == 21){
        dealerPlays(true, initialBet); /* natural blackjack = auto win, provjerava ima li diler blackjack */
    }
}

/* Obavlja Hit funckionalnost */
void Blackjack::actionHit(int initialBet){

    addUserCard(deck[currentCard++]);
    
    std::string temp = deck[currentCard-1].getValue();
    
    if(temp == "A"){
            if(totalUser <= 11)
                totalUser += 11;
            else totalUser += 1;
        }
    
    else{
        if(temp == "J" || temp == "K" || temp =="Q") totalUser += 10;
        else totalUser += std::stoi(temp);
    }
    
    if(totalUser > 21){ //auto LOSE
        chips -= initialBet;
        gameStatus = Ended;
        drawPlay(*this);
    }
    else if(totalUser == 21){
        dealerPlays(false,initialBet); 
    }
    
}

/* Parametar natural se odnosi na situaciju kada korisnik u zbiru početne dvije karte ima 21 poen.
    Nakon igrača igra diler, te ako ima manje ili 16 poena uzima karte dok ne pređe 17 bodova, i tada se porede konačni bodovi. */
void Blackjack::dealerPlays(bool natural, int initialBet){
    gameStatus = InProgress;
    if(!natural && totalDealer <= totalUser){
        while(totalDealer <= 16){
            std::string temp = deck[currentCard].getValue();
            
            if(temp == "A"){
                if(totalDealer <= 11)
                    totalDealer += 11;
                else totalDealer += 1;
            }
            
            else{
                if(temp == "J" || temp == "K" || temp =="Q") totalDealer += 10;
                else totalDealer += std::stoi(temp);
            }
            addDealerCard(deck[currentCard++]);
            
            drawPlay(*this);
        }
    }

    if(totalDealer > 21){ //auto WIN
        chips += 2 * initialBet;
        score += 50;
    }
    
    else if(totalUser > totalDealer){
        chips += initialBet;
        score += 50;
    }
    
    else if(totalUser < totalDealer){
        chips -= initialBet;
    }
    gameStatus = Ended;
    drawPlay(*this);
}

void addCardsType(Suits suit, std::vector<Card> &cards){
    cards.insert(cards.end(), Card("A", suit ));
    for(int i = 2; i <= 10; i++){
        cards.insert(cards.end(), Card(std::to_string(i), suit ));
        
    }
    cards.insert(cards.end(), Card("J", suit ));
    cards.insert(cards.end(), Card("K", suit ));
    cards.insert(cards.end(), Card("Q", suit ));
}

/* kockarski žeton predstavljen u RGB888 brojevima */
const uint16_t chip[14][14] = {
    0xFFFF, 0xFFFF, 0XFA49, 0XFA49, 0x00, 0x00, 0xfa49, 0xfa49,0x00, 0x00, 0xfa49, 0xfa49, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0XFA49, 0XFA49, 0x00, 0x00, 0xfa49, 0xfa49,0x00, 0x00, 0xfa49, 0xfa49, 0xFFFF, 0xFFFF,
    0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49,
    0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49,
    0x00, 0x00, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0x00, 0x00,
    0x00, 0x00, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0x00, 0x00,
    0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49,
    0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49,
    0x00, 0x00, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0x00, 0x00,
    0x00, 0x00, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0x00, 0x00,
    0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49,
    0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49, 0XFA49, 0XFA49,0XFA49, 0XFA49,
    0xFFFF, 0xFFFF, 0XFA49, 0XFA49, 0x00, 0x00, 0xfa49, 0xfa49,0x00, 0x00, 0xfa49, 0xfa49, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0XFA49, 0XFA49, 0x00, 0x00, 0xfa49, 0xfa49,0x00, 0x00, 0xfa49, 0xfa49, 0xFFFF, 0xFFFF,
    
    
};
/* Funkcija za crtanje okvira prozora */
void drawEdge(){
    BSP_LCD_SetTextColor(sveBoje[1]);
    
    int br =0;
    //petlja se vrti 24 puta, odnosno toliko je kocki sadržano na svakoj strani prozora
    for(int i = 0; i <= 230; i+=10){
        if(br%2 ==0 )BSP_LCD_SetTextColor(sveBoje[2]);
        else if(i == 110) BSP_LCD_SetTextColor(sveBoje[0]);
        else BSP_LCD_SetTextColor(sveBoje[1]);
        
    	BSP_LCD_FillRect (i, 0, 10, 10);
    	BSP_LCD_FillRect (0, i, 10, 10);
    	BSP_LCD_FillRect (i+10, 230, 10, 10);
    	BSP_LCD_FillRect (230, i+10, 10, 10);
        br++;
    }
    BSP_LCD_SetTextColor(sveBoje[2]);
}

void drawMainMenu(){
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    drawEdge();
    BSP_LCD_SetFont	(&Font16);

    BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)menuText[0], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 75, (uint8_t *)menuText[1], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 105, (uint8_t *)menuText[2], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 135, (uint8_t *)menuText[3], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 165, (uint8_t *)menuText[4], CENTER_MODE);
}

void displaySetUp(){
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    drawEdge();
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(20, 210, (uint8_t *)"Back", LEFT_MODE);
}

void drawAbout(const char* buildTime){
    displaySetUp();
    BSP_LCD_SetFont	(&Font12);
    BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)aboutText[0], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 40, (uint8_t *)aboutText[1], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 60, (uint8_t *)buildTime, LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 80, (uint8_t *)aboutText[2], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)aboutText[3], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)aboutText[4], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)aboutText[5], LEFT_MODE);
}


void firstPage(){
    displaySetUp();
    BSP_LCD_DisplayStringAt(130, 210, (uint8_t *)firstPageText[0], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)firstPageText[1], LEFT_MODE);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(20, 40, (uint8_t *)firstPageText[2], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 60, (uint8_t *)firstPageText[3], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 80, (uint8_t *)firstPageText[4], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)firstPageText[5], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)firstPageText[6], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)firstPageText[7], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)firstPageText[8], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 180, (uint8_t *)firstPageText[9], LEFT_MODE);
}

void secondPage(){
    displaySetUp();
    BSP_LCD_DisplayStringAt(130, 210, (uint8_t *)secondPageText[0], LEFT_MODE);
    BSP_LCD_SetFont(&Font12); 
    BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)secondPageText[1], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 40, (uint8_t *)secondPageText[2], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 60, (uint8_t *)secondPageText[3], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 80, (uint8_t *)secondPageText[4], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)secondPageText[5], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)secondPageText[6], LEFT_MODE);
    BSP_LCD_SetFont	(&Font16);
    BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)secondPageText[7], LEFT_MODE);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(20, 180, (uint8_t *)secondPageText[8], LEFT_MODE);
}

void thirdPage(){
    displaySetUp();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)thirdPageText[0], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 40, (uint8_t *)thirdPageText[1], LEFT_MODE);

    BSP_LCD_DisplayStringAt(20, 60, (uint8_t *)thirdPageText[2], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 80, (uint8_t *)thirdPageText[3], LEFT_MODE);
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)thirdPageText[4], LEFT_MODE);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)thirdPageText[5], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)thirdPageText[6], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)thirdPageText[7], LEFT_MODE);
}
void drawHowTo(int nekst){
    
    if(nekst == 0){
        firstPage();
    }
    else if(nekst == 1){
        secondPage();
    }
    else{
        thirdPage();
    }
}

void exitScreen(){
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"You'll come back..", CENTER_MODE);
}

int startScreen(){
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    drawEdge();
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"STARTING CHIPS", CENTER_MODE);
    BSP_LCD_DrawHLine (40, 75, 150);
    BSP_LCD_DrawRect (80, 100, 75, 20);
    
    if(indeks == 0)
        BSP_LCD_DisplayStringAt(25, 104, (uint8_t *)nums[indeks], CENTER_MODE);
    else if(indeks < 19)
        BSP_LCD_DisplayStringAt(20, 104, (uint8_t *)nums[indeks], CENTER_MODE);
    else
        BSP_LCD_DisplayStringAt(15, 104, (uint8_t *)nums[indeks], CENTER_MODE);
        
        
    int chips = std::stoi(nums[indeks]); //pocetni cipovi

    BSP_LCD_SetTextColor(sveBoje[0]);
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_DisplayStringAt(15, 151, (uint8_t *)"+", CENTER_MODE);
    BSP_LCD_SetTextColor(sveBoje[1]);
    BSP_LCD_DisplayStringAt(-10, 151, (uint8_t *)"-", CENTER_MODE);
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetTextColor(sveBoje[1]);
    BSP_LCD_DisplayStringAt(20, 210, (uint8_t *)"Quit", LEFT_MODE);
    BSP_LCD_SetTextColor(sveBoje[2]);
    BSP_LCD_DisplayStringAt(20, 210, (uint8_t *)"Place bet", RIGHT_MODE);
    
    return chips;
}

void drawChip(){
    for(int i = 0; i< 14; i++)
        for(int j = 0; j < 14; j++)
            BSP_LCD_DrawPixel(i+47,j+14, chip[i][j]);
}

void drawPlaceBet(int chips, int score, int bet){
    BSP_LCD_SetBackColor(0xFFFF);
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    drawEdge();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(17, 17, (uint8_t *)std::to_string(chips).c_str(), LEFT_MODE);
    drawChip();
    BSP_LCD_DisplayStringAt(15 + countDigit(score)*6, 15, (uint8_t *)"Score: ", RIGHT_MODE);
    BSP_LCD_DisplayStringAt(15, 15, (uint8_t *)std::to_string(score).c_str(), RIGHT_MODE);
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(0,60, (uint8_t *)placeBetText[0], CENTER_MODE);
    BSP_LCD_DrawHLine (55, 75, 120);
    BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)placeBetText[1], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)placeBetText[2], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)placeBetText[3], LEFT_MODE);
    BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)placeBetText[4], LEFT_MODE);
    BSP_LCD_SetTextColor(sveBoje[1]);
    BSP_LCD_DisplayStringAt(20, 210, (uint8_t *)placeBetText[5], LEFT_MODE);
    BSP_LCD_SetTextColor(sveBoje[2]);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(20, 180, (uint8_t *)std::string(placeBetText[6]).append(std::to_string(bet)).c_str(), LEFT_MODE);
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(20, 210, (uint8_t *)placeBetText[7], RIGHT_MODE);
}

void drawScore(int score, bool bottomedOut = false){
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    drawEdge();
    refreshHighScores(score);
    if(bottomedOut){
        BSP_LCD_SetTextColor(sveBoje[1]);
        BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)scoreText[0], CENTER_MODE);
        BSP_LCD_SetTextColor(sveBoje[2]);
    }
    BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)scoreText[1], CENTER_MODE);
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_DisplayStringAt(-5, 90, (uint8_t *)std::to_string(score).c_str(), CENTER_MODE);
    
    
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DrawHLine (40, 75, 150);
    BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)scoreText[2], CENTER_MODE);
}

void drawPlay(Blackjack blackjack){
    BSP_LCD_SetBackColor (sveBoje[0]);
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    BSP_LCD_SetTextColor(sveBoje[2]);
    BSP_LCD_DisplayStringAt(0, 10, (uint8_t *)playText[0], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 220, (uint8_t *)playText[1], CENTER_MODE);
    
    BSP_LCD_SetTextColor(0xFEA0);
    if(blackjack.getStatus() == 2){
        if(blackjack.getTotalUser() > 0 && blackjack.compareTotals() == 0){
            BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)playText[2], CENTER_MODE);
        }
        else if(blackjack.getTotalDealer() > 21 || (blackjack.getTotalUser() <= 21 && blackjack.getTotalUser() > blackjack.getTotalDealer())){
            BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)playText[3], CENTER_MODE);
        }
        else if(blackjack.getTotalUser() > 21 || blackjack.compareTotals() > 0){
            BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)playText[4], CENTER_MODE);
        }

    }
    BSP_LCD_SetBackColor (sveBoje[0]);
    BSP_LCD_SetTextColor(0xFFFF);
    
    if(blackjack.getStatus() != 2){
        BSP_LCD_DisplayStringAt(10, 220, (uint8_t *)playText[5], LEFT_MODE);
        BSP_LCD_DisplayStringAt(5, 220, (uint8_t *)playText[6], RIGHT_MODE);
    }
    else{
        
        BSP_LCD_DisplayStringAt(0, 220, (uint8_t *)playText[7], RIGHT_MODE);
    }
    BSP_LCD_SetTextColor(sveBoje[2]);
    
    
    int test= 5;
    for(int i = 0; i < blackjack.getDealerCards().size(); i++){
        /* Sakrij kartu ako dealer nije igrao */
        if(i == 0 && blackjack.getStatus() == 0)
            blackjack.getDealerCards()[i].drawCard(test, 50, true);
        
        else 
            blackjack.getDealerCards()[i].drawCard(test, 50);
            
        test+=45;
    }
    
    test = 5;
    for(int i = 0; i < blackjack.getUserCards().size(); i++){
        blackjack.getUserCards()[i].drawCard(test, 140);
        test+=45;
    }
}

/* priprema template za crtanje karata*/
void prepCard(){
    for(int i = 0; i < 51; i++){
        for(int j = 0; j < 38; j++){
            if(i == 0 || i == 50){
                if(j < 3 || j> 34) card_template[i][j] = 0x54D;
                else card_template[i][j] = 0xFFFF;
            }
            else if(i == 1 || i == 49){
                if(j < 2 || j > 35) card_template[i][j] = 0x54D;
                else card_template[i][j] = 0xFFFF;
            }
            else if(i == 2 || i == 48){
                if(j < 1 || j > 36) card_template[i][j] = 0x54D;
                else card_template[i][j] = 0xFFFF;
            }
            else card_template[i][j] = 0xFFFF;
        }
    }  
}

void drawHighScore(){
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    drawEdge();
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(20, 210, (uint8_t *)highScoreText[0], LEFT_MODE);
    BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)highScoreText[1], CENTER_MODE);
    BSP_LCD_DrawHLine (60, 45, 110);
    
    int space = 0;
    for(int i = 0; i < 3; i++){
        BSP_LCD_DisplayStringAt(60, 80 + space, (uint8_t *)std::to_string(i+1).append(".").c_str(), LEFT_MODE);
        BSP_LCD_DisplayStringAt(100, 80 + space, (uint8_t *)std::to_string(highscores[i]).c_str(), LEFT_MODE);
        space += 40;
    }
}

void drawCircles(int posX, int posY){
    BSP_LCD_FillCircle (posX,posY,5);
}

void drawIntroScreen(){
    BSP_LCD_SetBackColor (sveBoje[1]);
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    BSP_LCD_SetTextColor(sveBoje[2]);
	BSP_LCD_FillRect (0, 0, 240, 20);
	BSP_LCD_FillRect (0, 20, 20, 240);
	BSP_LCD_FillRect (220, 20, 20, 240);
	BSP_LCD_FillRect (0, 220, 240, 20);

	
	int length = 260;
	int width = 240;
	BSP_LCD_SetTextColor(sveBoje[1]);
	
	int br = 0;
	for(int i = 0;i < length; i+=20){
	        if(br%2 == 0)
	            BSP_LCD_SetTextColor(sveBoje[1]);
            else
                BSP_LCD_SetTextColor(sveBoje[0]);
                
            /* Crtanje gornjih krugova */
	    	drawCircles(i-10, 10);
	    	drawCircles(10, i+10);
	    	drawCircles(230, i-10);
	    	drawCircles(i-10, 230);
	    	br++;
	}
	BSP_LCD_SetTextColor(0x00);
	
	BSP_LCD_SetFont	(&Font12);
	BSP_LCD_DisplayStringAt(0, 40, (uint8_t *)introText[0], CENTER_MODE);
	BSP_LCD_SetFont	(&Font16);
    BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)introText[3], CENTER_MODE);
    BSP_LCD_SetFont	(&Font12);
    BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)introText[1], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)introText[2], CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 160, (uint8_t *)introText[4], CENTER_MODE);

}
int main()
{
    
    uint16_t x1, y1;
    int nekst = 0;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    const char* buildTime = asctime(timeinfo);
    
    BSP_LCD_Init();

    /* Touchscreen initialization */
    if (BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_ERROR) {
        printf("BSP_TS_Init error\n");
    }

    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    
   prepCard();
    
    drawIntroScreen();
        
    bool MAIN_MENU= 0, ABOUT =0, HOWT=0, START = 0, PLACE_BET=0, SCORE = 0, PLAY, HIGHSCORE = 0, INTRO = 1;
    int chips = 0, initialBet = 50;
    
    /* Priprema partije (kreiranje karata, spila karata itd)*/
    std::vector<std::string> symbols;
    symbols.insert(symbols.end(), "A");
    for(int i = 2; i<= 10; i++)
        symbols.insert(symbols.end(), std::to_string(i));
        
    symbols.insert(symbols.end(), "J");
    symbols.insert(symbols.end(), "K");
    symbols.insert(symbols.end(), "Q");

    std::vector<Card> cards;
    
    addCardsType(DIAMOND, cards);
    addCardsType(HEART, cards);
    addCardsType(CLUB, cards);
    addCardsType(SPADE, cards);
    
    Deck deck(cards);
    Blackjack blackjack(deck);
                
    while (1) {
        BSP_TS_GetState(&TS_State);
        
        if(TS_State.touchDetected) {
            x1 = TS_State.touchX[0];
            y1 = TS_State.touchY[0];
            
            if(INTRO){
                INTRO = 0;
                MAIN_MENU = 1;
                BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
                drawMainMenu();
            }
            
            else if(MAIN_MENU){
                
                /* Action - select About */
                if(x1 >= 87 && x1<= 145 && y1 >= 132 && y1 <= 153){
                    drawAbout(buildTime);
                    ABOUT = 1;
                    MAIN_MENU = 0;
                }
                /* Action - select How to Play */
                else if(x1 >= 51 && x1<= 182 && y1 >= 75 && y1 <= 91){
                    drawHowTo(nekst);
                    MAIN_MENU = 0;
                    HOWT = 1;
                }
                /* Action - select How to Play */
                else if(x1 >= 51 && x1<= 182 && y1 >= 75 && y1 <= 91){
                    drawHowTo(nekst);
                    MAIN_MENU = 0;
                    HOWT = 1;
                }
                /* Exit game */
                else if(x1 >= 93 && x1<= 137 && y1 >= 165 && y1 <= 180){
                    MAIN_MENU = 0;
                    exitScreen();
                }
                /* Start game - select Chips */
                 else if(x1 >= 87 && x1<= 144 && y1 >= 44 && y1 <= 59){
                    MAIN_MENU = 0;
                    START = 1;
                    chips = startScreen();
                }
                else if(MAIN_MENU && x1 >= 64 && x1<= 167 && y1 >= 105 && y1 <= 120){ //Place bet
                    MAIN_MENU = 0;
                    HIGHSCORE = 1;
                    drawHighScore();
                }
            }
            
            else if(ABOUT){
                /* Vrati se iz About prozora na pocetni */
                if(x1 >= 17 && x1<= 63 && y1 >= 209 && y1 <= 221){
                    ABOUT = 0;
                    MAIN_MENU = 1;
                    drawMainMenu();
                }
            }
            
            else if(HOWT){
                /* Vrati se iz prozora How To Play na pocetni */
                if(!nekst && x1 >= 17 && x1<= 51 && y1 >= 209 && y1 <= 221){
                    HOWT = 0;
                    MAIN_MENU = 1;
                    drawMainMenu();
                }
                /* Otvori drugu stranicu how to play prozora */
                else if(!nekst && x1 >= 126 && x1<= 224 && y1 >= 208 && y1 <= 223){
                    nekst = 1;
                    drawHowTo(nekst);
                }
                /* Otvori trecu stranicu how to play prozora */
                 else if(nekst && x1 >= 126 && x1<= 224 && y1 >= 208 && y1 <= 223){
                    nekst = 2;
                    drawHowTo(nekst);
                }
                /* Vrati se na prvu stranicu ako si na drugoj */
                else if(nekst == 1 && x1 >= 17 && x1<= 51 && y1 >= 209 && y1 <= 221){
                    nekst = 0;
                    drawHowTo(nekst);
                }
                /* Vrati se na drugu stranicu ako si na trecoj */
                else if(nekst == 2 && x1 >= 17 && x1<= 51 && y1 >= 209 && y1 <= 221){
                    nekst = 1;
                    drawHowTo(nekst);
                }
            }
            
            else if(START){
                /* Povecava kolicinu startnih zetona */
                if(x1 >= 127 && x1<= 140 && y1 >= 154 && y1 <= 167){ // PLUS
                    if(indeks < 19) 
                        indeks++;
                    chips = startScreen();
                }
                /* Smanjuje kolicinu startnih zetona */
                else if(x1 >= 101 && x1<= 115 && y1 >= 154 && y1 <= 167){ // MINUS
                    if(indeks > 0) 
                        indeks--;
                    chips = startScreen();
                }
                /* Vrati se na main menu iz start prozora */
                else if(x1 >= 18 && x1<= 64 && y1 >= 211 && y1 <= 224){ //quit
                    START =0;
                    MAIN_MENU = 1;
                    drawMainMenu();
                }
                else if(x1 >= 120 && x1<= 218 && y1 >= 211 && y1 <= 224){ //Place bet
                    PLACE_BET = 1;
                    START = 0;
                    /* dodijelimo chipove u blackjack klasu */
                    blackjack.setChips(chips);
                    drawPlaceBet(chips, blackjack.getScore(), initialBet);
                    
                }
            }
            
            else if(PLACE_BET){
                /* Quit game - pokazuje final score prozor */
                if(x1 >= 18 && x1<= 64 && y1 >= 211 && y1 <= 224){
                    PLACE_BET =0;
                    SCORE = 1;
                    drawScore(blackjack.getScore());
                    blackjack.setScore(0);
                }
                /* Pocni novu rundu */
                else if(x1 >= 167 && x1<= 211 && y1 >= 211 && y1 <= 223){
                    PLACE_BET = 0;
                    PLAY = 1;
                    blackjack.setDeck(blackjack.getDeck().shuffle());
                    blackjack.resetGame();
                    blackjack.setUp(initialBet);   
                    drawPlay(blackjack);
                }
                else{
                    /* Svi ovi ifovi postavljaju novu vrijednost opklade */
                    if(blackjack.getChips() >= 50 && x1 >= 56 && x1<= 74 && y1 >= 100 && y1 <= 113){
                        initialBet = 50;
                    }
                    else if(blackjack.getChips() >= 100 && x1 >= 56 && x1<= 89 && y1 >= 121 && y1 <= 133){
                        initialBet = 100;
        
                    }
                    else if(blackjack.getChips() >= 150 && x1 >= 56 && x1<= 89 && y1 >= 141 && y1 <= 155){
                        initialBet = 150;
                    }
                    else if(blackjack.getChips() >= 200 && x1 >= 56 && x1<= 89 && y1 >= 160 && y1 <= 173){
                        initialBet = 200;
                    }
                    drawPlaceBet(blackjack.getChips(), blackjack.getScore(), initialBet);
                }
                
            }
            /* Vrati se iz high score na main menu */
            else if(HIGHSCORE && x1 >= 17 && x1<= 63 && y1 >= 209 && y1 <= 221){
                HIGHSCORE = 0;
                MAIN_MENU = 1;
                drawMainMenu();
            }
            /* Vrati se iz total score na main menu */
            else if(SCORE && x1 >= 79 && x1<= 157 && y1 >= 121 && y1 <= 136){ //return
                SCORE = 0;
                MAIN_MENU = 1;
                drawMainMenu();
            }
            
            else if(PLAY){
                /* Sada pravimo Hit funkcionalnost */
                if(blackjack.getStatus() != 2 && x1 >= 190 && x1<= 227 && y1 >= 217 && y1 <= 236){
                    blackjack.actionHit(initialBet);
                    drawPlay(blackjack);
                }
                
                /* Sada pravimo Stand funkcionalnost */
                else if(blackjack.getStatus() != 2 && x1 >= 12 && x1<= 67 && y1 >= 217 && y1 <= 236){
                    blackjack.dealerPlays(false, initialBet);
                }
                
                /* Continue funckionalnost */
                else if(blackjack.getStatus() == 2 && x1 >= 141 && x1<= 233 && y1 >= 217 && y1 <= 236){
                    PLAY = 0;
                    if(blackjack.getChips() <= 0){
                        SCORE = 1;
                        BSP_LCD_SetBackColor(0xFFFF);
                        drawScore(blackjack.getScore(), true);
                        blackjack.setScore(0);
                    }
                    else{
                        /* Prisilno zaustavljanje igre - igrac nema zetona */
                        PLACE_BET = 1;
                        initialBet = 50;
                        drawPlaceBet(blackjack.getChips(), blackjack.getScore(), initialBet);
                    }
                        
                }
            }

            wait_ms(10);
        }
        if(MAIN_MENU){
            BSP_LCD_SetFont	(&Font12);
            BSP_LCD_SetTextColor(sveBoje[1]);
            BSP_LCD_DisplayStringAt(0, 20, (uint8_t *)"WARNING: Highrollers only!", CENTER_MODE);
        }
    }
}