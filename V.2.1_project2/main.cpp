/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: J Miguel Belarmino
 * Created on May 31, 2025
 * Purpose:  Blackjack(21) Project 2
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
//Function Prototypes
void start(string&, bool&, int&, int&);  //Input name and check for saved
int drwCard(int);                        //draw random card based on current cards
void pTurn(string, int&, int&);          //User's turn loop
void dTurn(string, int&, int&, int&);    //dealer's turn
void stats(int , int);                   //Win stats
void saveGam(string, int, int);          //Save game stats 

//Execution begins here at main
int main(int argc, char** argv) {
    //Set random number seed
    srand(static_cast<unsigned int>(time(0))); //random number generator
    //Declare Variables
    //player's and computer's card value and total
    int pCards, cCards, pTotal, cTotal; 
    int wins=0, rounds=0;               //Track total wins and rounds
    char move;                          //for hit or stand
    bool play;                          //controls game loop
    string name;                 //USer's name & temporary file word
    bool found = false;                 //indicate if existing user found
    
    //Map/Process the Inputs -> Outputs
    
    start(name,found,wins,rounds);
    
    play=true;//Start main game loop
    do {
        //both starts at the total value of 0
        pTotal=0; //Initialize Variables
        cTotal=0;
        
        pCards=rand()%20+MINCARD;  //random draw between the range of 2-21
        pTotal+=pCards;
        
        cCards=rand()%10+MINCARD;  //random draw between the range of 2-11
        cTotal+=cCards;
        //User's two initial card
        cout<<name<<" drew a "<<pCards<<" Total of = "<<pTotal<<endl;
        //dealer's initial card
        cout<<"Dealer's first card is a "<<cCards<<" Total of = "<<cTotal<<endl;
        
        pTurn(name,pTotal,wins); //User's turn
        
        if(pTotal<MAXVAL) {     //Dealer/computer's turn if player hasn't busted
            dTurn(name,pTotal,cTotal,wins);
        }
        
        rounds++;               //counts the rounds
        stats(wins,rounds);     //calculate of win rate
        
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
        cout<<"Resume rounds."<<endl;
    }else{
        cout<<"New game."<<endl;
    }
}

int drwCard(int total) {               //draw cards depends on the current total
    if (total <=10)
        return rand() % 10 + MINCARD;  //draw between 2–11
    else 
        return rand() % 10 + 1;        //draw between 1–10
}

void pTurn(string name, int &pTotal, int &wins) { //User's turn
    int pCards;
    char move;
    do { //User's decision loop for hit or stand 
        cout<<"Hit(h) or Stand(s)? : ";   //Hit=another card or Stand=stay
        cin>>move;
        if (move=='h'||move=='H'){
            pCards=drwCard(pTotal);
            pTotal+=pCards;
            cout<<name<<" hit a "<<pCards<<" Total of = "<<pTotal<<endl;
        }
        if (pTotal>MAXVAL){               //if its over 21 game over
            cout<<name<<" Busted! :'{ (Over 21)"<<endl;
            move='s';                     //exit loop
        }
        if(pTotal==MAXVAL){ //player hits 21 
            cout<<name<<" Blackjack/WINNER "<<endl;
            wins++;                       //increment user's win count
            move='s';                     //exit loop
        }    
    } while (move=='h'||move=='H');
}

void dTurn(string name, int &pTotal, int &cTotal, int &wins) { //dealer's turn
    int cCards;
    cout<<"Dealer's turn"<<endl;
    
    while(cTotal<17){                 //Dealer hits until 17 or more
        cCards=drwCard(cTotal);
        cTotal+=cCards;
        cout<<"Dealer hit a "<<cCards<<" Total of = "<<cTotal<<endl;
    }

    if (cTotal>MAXVAL){             //Determine outcome
        cout<<"Dealer Busted! ;) (Over 21)"<<endl;
        cout<<name<<" is a WINNER! :)"<<endl;
        wins++;
    }else if(cTotal>pTotal){        //if dealer has more than the user
        cout<<"Dealer wins"<<endl;
    }else if(cTotal==pTotal){       //if dealer and user total are equal
        cout<<"DRAW!"<<endl;
    }else{
        cout<<name<<" is a WINNER! :)"<<endl;
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
