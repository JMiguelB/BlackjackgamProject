/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: J Miguel Belarmino
 * Created on June 2, 2025
 * Purpose:  Blackjack(21) Project 2 Version 2 
 *           adding a suit and faces with the a deck
 */

//System Libraries
#include <iostream>  //Input Output Library
#include <iomanip>   //Format Library
#include <ctime>     //Time Library
#include <cstdlib>   //Random Library
#include <string>    //String Library
#include <fstream>   //File Library//for reading from and writing to files
using namespace std;

//User Libraries

//Global Constants not Variables
//Science, Math, Conversions, Dimensions
const int MINCARD=2;  //minimum card value
const int MAXCARD=11; //maximum card value, Ace=11
const int MAXVAL=21;  //Highest value allowed in Blackjack
const int DECSIZE=52; 

//Function Prototypes
void start(string&, bool&, int&, int&);  //Input name and check for saved
void pTurn(string, int&, int&, int&, string[], int[], int);       //User's turn loop
void dTurn(string, int&, int&, int&, int&, string[], int[], int); //dealer's turn
void stats(int , int);                   //Win stats
void saveGam(string, int, int);          //Save game stats
void bldDeck(string [],int [], string [], string [] //build deck of cards
            ,int [],const int);
void shuffle(string [],int [], int);     //shuffle deck/swapping

//Execution begins here at main
int main(int argc, char** argv) {
    //Set random number seed
    srand(static_cast<unsigned int>(time(0))); //random number generator
    
    //Declare Variables
    //player's and computer's card value and total
    int pTotal, cTotal, topCard=0; 
    int wins=0, rounds=0;               //Track total wins and rounds
    bool play;                          //controls game loop
    string name;                 //USer's name & temporary file word
    bool found = false;                 //indicate if existing user found
    
    string face[]={"2","3","4","5",
                   "6","7","8","9",
                   "10","Jack","Queen","King","Ace"};  //face value of the cards
    string suit[]={"Spades","Diamond",
                   "Clubs","Hearts"};                  //All the suits in a deck
    int values[]={2,3,4,5,6,7,8,9,
                   10,10,10,10,11};                    //Card values
    string deck[DECSIZE];
    int deckVal[DECSIZE];
    
    //Map/Process the Inputs -> Outputs
    
    bldDeck(deck, deckVal, face, suit, values, DECSIZE);
    shuffle(deck,deckVal,DECSIZE);
    
    start(name,found,wins,rounds);
    
    play=true;//Start main game loop
    do {
        //both starts at the total value of 0
        if(topCard>DECSIZE-10){      //restart deck when became less than 10
            cout<<"Shuffle deck"<<endl;
            bldDeck(deck, deckVal, face, suit, values, DECSIZE);
            shuffle(deck,deckVal,DECSIZE);
            topCard=0;
        }
        
        pTotal=0; //Initialize Variables
        cTotal=0;
        
        //User's two initial card
        cout << name << " first 2 cards are:"<<endl;
        for (int i = 0; i < 2; i++) {
            cout << deck[topCard] << " (" << deckVal[topCard] << ")"<<endl;
            pTotal += deckVal[topCard++];
        }
        
        cout << "Total = " << pTotal << endl;
        cout << endl;
        
        //dealer's initial card
        cout<<"Dealer's first card is a "<<deck[topCard]<<endl;
        cTotal+=deckVal[topCard++];
        cout<<endl;
        
        pTurn(name,pTotal,wins,topCard,deck,deckVal,DECSIZE); //User's turn
        
        if(pTotal<MAXVAL) {     //Dealer/computer's turn if player hasn't busted
            dTurn(name,pTotal,cTotal,wins,topCard,deck,deckVal,DECSIZE);
        }
        
        rounds++;               //counts the rounds
        stats(wins,rounds);     //calculate of win rate
        
        cout<<endl;
        char again;             //Ask Useer if they want to play again
        cout<<"Do you wanna play again?(y/n): ";
        cin>>again;
        play=(again=='y'||again=='Y');
    } while (play);
    //Display Inputs/Outputs
    
    //Clean up memory and files
    
    saveGam(name, wins, rounds);
    
    //Exit the Program
    return 0;
}

void start(string &name, bool &found, int &wins, int &rounds) {
    cout<<"Enter player's name: ";
    cin>>name;                             //Prompt the user to enter their name
    
    fstream in;                            //Input file streams
    in.open(name+"blackjack.dat",ios::in); //Attempt to load previous progress
    if(in.is_open()){
        //read data     
        in>>wins>>rounds;
        in.close();
        found=true;
    }
    
    if(found){ 
        cout<<"Resume rounds."<<endl<<endl;
    }else{
        cout<<"New game."<<endl<<endl;
    }
}

void pTurn(string name, int &pTotal, int &wins, int &topCard,
        string deck[], int deckVal[], int size) { //User's turn
    char move;
    do { //User's decision loop for hit or stand 
        cout<<name<<" Hit(h) or Stand(s)? : ";   //Hit=another card or Stand=stay
        cin>>move;
        cout<<endl;
        if (move=='h'||move=='H'){
            cout<<name<<" hit a "<<deck[topCard]<< "(" <<deckVal[topCard] <<")"<<endl;
            pTotal += deckVal[topCard++];
            cout<<"a new total of = "<<pTotal<<endl;
        }
        if (pTotal>MAXVAL){               //if its over 21 game over
            cout<<name<<" Busted! :'{ (Over 21)"<<endl<<endl;
            move='s';                     //exit loop
        }
        if(pTotal==MAXVAL){ //player hits 21 
            cout<<name<<" Blackjack/WINNER "<<endl<<endl;
            wins++;                       //increment user's win count
            move='s';                     //exit loop
        }    
    } while (move=='h'||move=='H');
}

void dTurn(string name, int &pTotal, int &cTotal, int &wins,
           int &topCard, string deck[], int deckVal[], int size) { //dealer's turn
    cout<<"Dealer's turn:"<<endl;
    cout<<"Dealer reveals second card..." << endl;
    
    // Dealer's hidden second card
    cout << deck[topCard] << " (" << deckVal[topCard] << ")" << endl;
    cTotal += deckVal[topCard++];
    cout << "Dealer's first 2 cards are total of: " << cTotal << endl;
    
    while(cTotal<17){                 //Dealer hits until 17 or more
        cout << "Dealer draws: " << deck[topCard] << " (" << deckVal[topCard] << ")" << endl;
        cTotal += deckVal[topCard++];
        cout << "Dealer's new total: " << cTotal << endl;
        cout << endl;
    }

    if (cTotal>MAXVAL){             //Determine outcome
        cout<<"Dealer Busted! ;) (Over 21)"<<endl;
        cout<<name<<" is a WINNER! :)"<<endl<<endl;
        wins++;
    }else if(cTotal>pTotal){        //if dealer has more than the user
        cout << "Dealer wins this round." << endl;
    }else if(cTotal==pTotal){       //if dealer and user total are equal
        cout<<endl<<"DRAW!"<<endl<<endl;
    }else{
        cout<<name<<" is a WINNER! :)"<<endl<<endl;
        wins++;                     //increment user's win count
    }
}

void stats(int wins, int rounds) {
    float winRate;                            //win probability in % out of 100%
    winRate=(rounds>0)?(100.0*wins/rounds):0; //calculate of win rate
        cout<<fixed<<setprecision(1);
        cout<<"Win rate= "<<winRate<<"% ("<<wins
                <<"/"<<rounds<<")"<<endl;
}

void saveGam(string name, int wins, int rounds) {
    fstream out;                           //Output file streams/save
    out.open(name+"blackjack.dat",ios::out);  //Save game results to file  
    if(out.is_open()){  
        out<<wins<<" "<<rounds;
        out.close();
    }
}

void bldDeck(string deck[],int deckVal[], string face[], string suit[]
            ,int values[],const int DECSIZE) {
    int indx=0;                                // Index for filling the deck
    for(int s=0;s<4;s++) {                      // Loop through 4 suits
        for(int f=0;f<13;f++) {
            deck[indx]=face[f]+" of "+suit[s];   //combine
            deckVal[indx]=values[f];             //assign card value
            indx++;
        }
    }
}

void shuffle(string deck[],int deckVal[],const int size) {
    for(int i=0;i<size;i++) {
        int j=rand()%size;    //random from size
        string temp=deck[i];  //swap strings
        deck[i]=deck[j];
        deck[j]=temp;
        int tempV=deckVal[i]; //swap values
        deckVal[i]=deckVal[j];
        deckVal[j]=tempV;
        
    }
}