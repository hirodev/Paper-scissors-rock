#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <map>
#include <time.h>

using namespace std;

enum hand_gesture{
  ROCK =0,
  PAPER,
  SCISSORS,
  NONE,
  QUIT
};

// get the player's choice
int menuChoice();
// get the computer's choice
int computerChoice();
// build out the gesture beats mapping
void buildBeats(map< hand_gesture, hand_gesture > &beats);
// interpret the character choice as a hand_gesture enum
hand_gesture getGesture( int choice );

void args(){
  cerr << "usage: rps" << endl;
}

int main(int argc, char **argv){
  
  if( argc != 1 ){
    args();
    return EXIT_FAILURE;
  }
  
  cout << "Welcome to Rock, Paper, Scissors!" << endl;

  // initalize random seed
  srand( time(NULL) );

  map< hand_gesture, hand_gesture > beats;
  buildBeats( beats );
  
  int won = 0;
  int lost = 0;
  
  while( 1 ){
   
    hand_gesture player_gesture = NONE;
    hand_gesture computer_gesture = NONE;

    int player = menuChoice();
    cout << "You chose " << endl;
    player_gesture = getGesture( player );

    if( player_gesture == QUIT ){
      cout << "You won " << won << " and lost " << lost << endl;
    
      if(won > lost){
        cerr << "Wow, congratulations." << endl;
      }else if(won < lost){
        cout << "I see you have had enough losing! Quitter..." << endl;
      }else{
	cout << "Average." << endl;
      }
      cout << "Good bye." << endl;

      break;
    }

    int computer = computerChoice();
    cout << "The computer chose " << endl;
    computer_gesture = getGesture( computer );
    
    if( player_gesture == NONE ){
      cout << "Invalid Choice" << endl;
    }else if( player_gesture == computer_gesture ){
      cout << "It's a tie" << endl;
    }else if( beats[ player_gesture ] == computer_gesture ){
      cout << "You Win!" << endl;
      ++won;
    }else{
      cout << "You Lost" << endl;
      ++lost;
    }

  }

  return EXIT_SUCCESS;
}

hand_gesture getGesture( int choice ){
  hand_gesture gesture= NONE; 
  
  switch( choice ){
  case 'R':
  case 'r': // Rock
    cout << "Rock" << endl;
    gesture = ROCK;  
  break;
  case 'P':
  case 'p': // Paper
    cout << "Paper" << endl;
    gesture = PAPER;
  break;
  case 'S':
  case 's': // Scissors   
    cout << "Scissors" << endl;
    gesture = SCISSORS;
  break;
  case 'Q':
  case 'q':        
    cout << "to Quit" << endl;
    gesture = QUIT;
  break;
  default:
    cout << "an unkown gesture" << endl;
    gesture = NONE;    
  break;
  }
  
  return gesture;
}

void buildBeats( map< hand_gesture, hand_gesture > & beats ){
  beats[ ROCK ] = SCISSORS;
  beats[ PAPER ] = ROCK;
  beats[ SCISSORS ]= PAPER;
}

int menuChoice(){
  cout << endl;
  cout << "Menu" << endl;
  cout << "choose one:" << endl;
  
  cout << "R for Rock" << endl;
  cout << "P for Paper" << endl;
  cout << "S for Scissors" << endl;
  cout << "Q to quit" << endl;

  cout << endl;
  cout << "Your choice? ";
  
  int choice = getc( stdin );

  // throw away the enter key
  getc( stdin );
  
  cout << endl;

  return choice;
}

int computerChoice(){
  int choice = rand() % 3;
  if(0 == choice){
    choice = 'r';
  }else if(1 == choice){
    choice = 'p';
  }else if(2 == choice){
    choice = 's';
  }else{
    // should not get here 
    choice = 'r';
  }
  return choice;
}
