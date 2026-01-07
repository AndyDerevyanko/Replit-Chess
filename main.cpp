/*                                                   *
 * Name: Andy Derevyanko                             *
 * Class: ICS3U1-04                                  *
 * Topic: Summative - Replit Console Chess           *
 *                                                   */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wshadow"

#include "chess.h"
#include <iostream>

using namespace std;

int main() {

  // Create a chess board object
  brd board('w');

  // Display program information
  cout << "Welcome to Andy's Console Chess Program!\n";
  cout << "This is a basic two-player chess program with the closest thing you "
    "will get to proper UI, in Replit's primitive console\n\n";

  while (true) {
    // Initialization
    string input;
    string choice;

    while (true) {
      bool isValidChoice = false;
      bool start = false;

      // Display menu options
      cout << "Enter:\n";
      cout << "1. To begin\n";
      cout << "2. For a tutorial link explaining how chess is played\n";
      cout << "3. For a tutorial on how to input your moves\n";
      cout << "4. Quit\n\n";
      cin >> choice;

      // Validate the user's choice
      if (choice.length() == 1 && choice[0] >= '1' && choice[0] <= '4')
        isValidChoice = true;

      while (!isValidChoice) {
        cout << "\nInvalid choice, your input must be between 1 and 4.\n";
        cin >> choice;
        if (choice.length() == 1 && choice[0] >= '1' && choice[0] <= '4') {
          isValidChoice = true;
        }
      }

      cout << endl;

      switch (choice[0]) {
      case '1':
        // start chess game
        start = true;
        cout << "Starting game...\n";
        sleep(2);
        system("clear");
        break;
      case '2':
        // give player tutorial on chess
        cout << "Find out how to play chess here:\n";
        cout << warn
          << "https://www.dicebreaker.com/games/chess/how-to/"
          "how-to-play-chess"
          << resetC << endl
          << endl;
        break;
      case '3':
        // give player movement input tutorial
        cout << "Proper Chess notation works as an input, go to:\n"
          << warn << "https://www.chess.com/terms/chess-notation\n"
          << resetC
          << "to find out how to write in proper chess notation. Otherwise, "
          "you can simply enter the square the piece is on and the "
          "square it will go to to move your pieces. ex. e2e4 (e2 to e4) "
          "\n\n";
        break;
      case '4':
        // exit
        cout << "Thanks for playing, goodbye!\n";
        return 0;
      }

      if (start)
        break;
    }

    // Reset the board and game state
    board.wipe();
    board.isRunning = true;
    board.recordPosition(board.pos);
    board.moves.push_back("[]");

    while (true) {
      // Render the board
      cout << bB << resetC;
      board.render();

    start:
      // Check for game-ending conditions
      board.endChecker();
      if (!board.isRunning) {
        break;
      }
      cout << bB << resetC;
      cin >> input;
      board.endChecker();
      if (!board.isRunning) {
        break;
      }
      try {
        // Process the player's move
        if (board.move(
          board.interpretMove(input, 0), board.interpretMove(input, 1),
          board.interpretMove(input, 2), board.interpretMove(input, 3))) {
          system("clear");
          cout << bB;
          // Switch the current player's turn
          board.team == 'w' ? board.team = 'b' : board.team = 'w';
          if (board.inCheck()) {
            cout << warn << warnB << "CHECK!" << endl << resetB;
            sleep(2);
          }
        }
        else {
          goto start;
        }
      }
      catch (genericError) {
        goto start;
      }
    }
    cout << endl;
  }

  // exit program
  return 0;
}
