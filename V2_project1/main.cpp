/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: J Miguel Belarmino
 * Created on May 9, 2025
 * Purpose:  Blackjack(21) Project
 */

//System Libraries
#include <iostream>  // Input/Output operations
#include <ctime>     // Time functions for random seed
#include <cstdlib>   // Random number generation
#include <string>    // For using strings
using namespace std;

//Global Constants not Variables
const int MINCARD=2;  //minimum card value
const int MAXCARD=11; //maximum card value, Ace=11
const int MAXVAL=21;  //Highest value allowed in Blackjack

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed

    // Declare variables
    int pCards, cCards, pTotal, cTotal; // Player and dealer card and total values
    char move;                         // Player choice: hit or stand
    bool play;                         // Continue playing flag
    string name;                       // Player's name

    // Ask for and store player name
    cout<<"Enter player's name: ";
    cin>>name;                          //Prompt the user to enter their name

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
        
        do { //User's decision loop for hit or stand 
            cout<<"Hit(h) or Stand(s)? : ";   //Hit=another card or Stand=stay
            cin>>move;
            if (move=='h'||move=='H'){
                if (pTotal<=10){              //if Userr has 10 under
                    //User can draw between 2–11
                    pCards=rand()%10+MINCARD;
                }else{ //11 and up
                    //User can draw between 1–10 only
                    pCards=rand()%10+1;
                }
                pTotal+=pCards;
                cout<<name<<" hit a "<<pCards<<" Total of = "<<pTotal<<endl;
            }
            if (pTotal>MAXVAL){               //if its over 21 game over
                cout<<name<<" Busted! :'{ (Over 21)"<<endl;
                move='s';                     //exit loop
            }
            if(pTotal==MAXVAL){ //player hits 21 
                cout<<name<<" Blackjack/WINNER "<<endl;
                move='s';                     //exit loop
            }    
        } while (move == 'h' || move == 'H');
        // Dealer plays if player is still in
        if(pTotal<MAXVAL) {   //Dealer/computer's turn if player hasn't busted
            cout<<"Dealer's turn"<<endl;
            
            while(cTotal<17){                 //Dealer hits until 17 or more
                if (cTotal<=10){              //if dealer has 10 under
                    cCards=rand()%10+MINCARD; //Dealer can draw between 2–11
                }else{                        //if dealer has 11 and up
                    cCards=rand()%10+1;       //Dealer can draw between 1–10
                }
                cTotal+=cCards;
                cout<<"Dealer hit a "<<cCards<<" Total of = "<<cTotal<<endl;
            }

            // Determine winner
            if (cTotal>MAXVAL){             //Determine outcome
                cout<<"Dealer Busted! ;) (Over 21)"<<endl;
                cout<<name<<" is a WINNER! :)"<<endl;
            }else if(cTotal>pTotal){        //if dealer has more than the user
                cout<<"Dealer wins"<<endl;
            }else if(cTotal==pTotal){       //if dealer and user total are equal
                cout<<"DRAW!"<<endl;
            }else{
                cout<<name<<" is a WINNER! :)"<<endl;
            }
        }

        // Ask to continue
        char again;                       //Ask Useer if they want to play again
        cout<<"Do you wanna play again?(y/n): ";
        cin>>again;
        play=(again=='y'||again=='Y');

    } while (play);
    
    return 0;
}
