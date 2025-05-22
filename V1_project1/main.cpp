/* 
 * File:   main.cpp
 * Author: J Miguel Belarmino
 * Created on May 6, 2025, 4:05 PM
 * Purpose:  Blackjack(21) Project
 */

//System Libraries
#include <iostream>  // Input/Output operations
#include <ctime>     // Time functions for random seed
#include <cstdlib>   // Random number generation
using namespace std;

//Global Constants not Variables
const int MINCARD=2;  //minimum card value
const int MAXCARD=11; //maximum card value, Ace=11
const int MAXVAL=21;  //Highest value allowed in Blackjack

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed

    // Declare variables
    int pCards ,cCards ,pTotal , cTotal;   // Player and dealer card and total values
    char move;                         // Player choice: hit or stand
    bool play;                         // Continue playing flag

    play=true;
    do {
        pTotal=0; 
        cTotal=0;

        // Initial card draws
        pCards=rand()%20+MINCARD;  //random draw between the range of 2-21
        pTotal+=pCards;
        
        cCards=rand()%10+MINCARD;  //random draw between the range of 2-11
        cTotal+=cCards;

        // Show starting hands
        cout << "Player drew a " << pCards << " Total of = " << pTotal << endl;
        cout << "Dealer's first card is a " << cCards << " Total of = " << cTotal << endl;

        // Player's turn
        do {
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
                cout<<"Player hit a "<<pCards<<" Total of = "<<pTotal<<endl;
            }
            // Evaluate outcome
            if (pTotal > MAXVAL) {
                cout<<"Player Busted! :'{ (Over 21)"<<endl;
                move='s'; // Exit loop
            }
            if (pTotal == MAXVAL) {
                cout <<"Player Blackjack/WINNER "<<endl;
                move='s'; // Exit loop
            }    
        } while (move == 'h' || move == 'H');
        // Dealer plays if player is still in
        if (pTotal <MAXVAL) {
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
            if(cTotal>MAXVAL) {
                cout<< "Dealer Busted! ;) (Over 21)" <<endl;
                cout<< "Player is a WINNER! :)" <<endl;
            } else if(cTotal>pTotal) {
                cout << "Dealer wins" << endl;
            } else if(cTotal==pTotal) {
                cout << "DRAW!" << endl;
            } else {
                cout<<"Player is a WINNER! :)" <<endl;
            }
        }

        // Ask to continue
        char again;
        cout<< "Do you wanna play again?(y/n): ";
        cin>>again;
        play=(again == 'y' || again == 'Y');

    } while(play);
    
    return 0;
}
