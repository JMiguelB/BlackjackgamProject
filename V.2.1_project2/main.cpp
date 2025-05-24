/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: J Miguel Belarmino
 * Created on May 24, 2025
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

//Execution begins here at main
int main(int argc, char** argv) {
    //Set random number seed
    srand(static_cast<unsigned int>(time(0))); //random number generator
    //Declare Variables
    //player's and computer's card value and total
    int pCards, cCards, pTotal, cTotal; 
    int wins=0, rounds=0;               //Track total wins and rounds
    float winRate;                      //win probability in % out of 100%
    char move;                          //for hit or stand
    bool play;                          //controls game loop
    string name, rWord;                 //USer's name & temporary file word
    fstream in, out;                    //Input/Output file streams
    bool found = false;                 //indicate if existing user found
    
    //Map/Process the Inputs -> Outputs
    cout<<"Enter player's name: ";
    cin>>name;                          //Prompt the user to enter their name
    
    /* in.open(name+"blackjack.dat",ios::in);   //Attempt to load previous progress
    if(in.is_open()){
        //read data     
        in>>wins>>rounds;
        in.close();
        found=true;
    } */
    
    if(found){ 
        cout<<"Resume rounds."<<endl;
    }else{
        cout<<"New game."<<endl;
    }
    
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
                wins++;                       //increment user's win count
                move='s';                     //exit loop
            }    
        } while (move=='h'||move=='H');
        
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
        rounds++; //counts the rounds
        winRate=(rounds>0)?(100.0*wins/rounds):0;   //calculate of win rate
        cout<<fixed<<setprecision(1);
        cout<<"Win rate= "<<winRate<<"% ("<<wins
                <<"/"<<rounds<<")"<<endl;
        
        char again;                       //Ask Useer if they want to play again
        cout<<"Do you wanna play again?(y/n): ";
        cin>>again;
        play=(again=='y'||again=='Y');
    } while (play);
    //Display Inputs/Outputs
    
    //Clean up memory and files
    
    /*out.open(name+"blackjack.dat",ios::out);  //Save game results to file  
    out<<wins<<" "<<rounds<<endl;
    out.close();*/
    
    //Exit the Program
    return 0;
}

