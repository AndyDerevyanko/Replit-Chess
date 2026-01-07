#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wshadow"


// include all necessary libraries
#include <cmath>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

// Declaration of a custom exception class
class genericError {};

// Color codes for black pieces
string black = "\033[31m";
// Color codes for white pieces
string white = "\033[33m";
// Color code to reset color
string resetC = "\033[37m";
// Color code for green
string green = "\033[92m";
// Background color code for black
string bB = "\033[40m";
// Background color code for white
string bW = "\033[107m";
// Background color code to reset color
string resetB = "\033[40m";
// Color code for warning messages
string warn = "\033[35m";
// Color background code for checkmate message
string warnB = "\033[104m";

// Enumeration for horizontal positions on the chessboard
enum boardHorizontal { h, g, f, e, d, c, b, a };

// Enumeration for vertical positions on the chessboard
enum boardVertical { one, two, three, four, five, six, seven, eight };

// Structure defining black chess pieces
struct bl {
  // Pawn
  string p = black + "♟︎";
  // Knight
  string n = black + "♞";
  // Bishop
  string b = black + "♝";
  // Rook
  string r = black + "♜";
  // Queen
  string q = black + "♛";
  // King
  string k = black + "♚";
};

// Structure defining white chess pieces
struct wh {
  // Pawn
  string p = white + "♙";
  // Knight
  string n = white + "♘";
  // Bishop
  string b = white + "♗";
  // Rook
  string r = white + "♖";
  // Queen
  string q = white + "♕";
  // King
  string k = white + "♔";
};

// chess board class
class brd {
private:
  // Object representing the white chess pieces
  wh W;
  // Object representing the black chess pieces
  bl B;

  // Flag indicating whether the program is running
public:
  bool isRunning = true;

  // Current team ('w' for white, 'b' for black)
  char team;

  // Flag indicating whether the white right rook has moved
  bool wRookRMoved = false;

  // Flag indicating whether the white left rook has moved
  bool wRookLMoved = false;

  // Flag indicating whether the black right rook has moved
  bool bRookRMoved = false;

  // Flag indicating whether the black left rook has moved
  bool bRookLMoved = false;

  // Flag indicating whether the white king has moved
  bool wKingMoved = false;

  // Flag indicating whether the black king has moved
  bool bKingMoved = false;

  // 2D array representing the positions on the chessboard
  string pos[8][8];

  // Vector to store moves made
  vector<string> moves;

  // Vector to store the corresponding pieces involved in moves
  vector<char> movesPiece;

  // Vector to store previous positions on the chessboard
  vector<vector<string>> positions;

  // Function to reset the board and storage altogether
  void wipe() {
    reset();
    // Reset the board

    moves.clear();
    // Clear the moves vector

    movesPiece.clear();
    // Clear the movesPiece vector

    positions.clear();
    // Clear the positions vector

    isRunning = true;
    // Reset the isRunning flag

    wRookRMoved = false;
    // Reset the flag for white kingside rook

    wRookLMoved = false;
    // Reset the flag for white queenside rook

    bRookRMoved = false;
    // Reset the flag for black kingside rook

    bRookLMoved = false;
    // Reset the flag for black queenside rook

    wKingMoved = false;
    // Reset the flag for white king

    bKingMoved = false;
    // Reset the flag for black king
  }

  bool isWhite(string input) {
    // Check if the input represents a white piece
    if (input == W.p || input == W.n || input == W.b || input == W.r ||
      input == W.q || input == W.k)
      return true;
    else
      return false;
  }

  bool isBlack(string input) {
    // Check if the input represents a black piece
    if (input == B.p || input == B.n || input == B.b || input == B.r ||
      input == B.q || input == B.k)
      return true;
    else
      return false;
  }

  void setup() {
    // Set up the initial positions of white pieces
    pos[a][one] = W.r;
    // Rook
    pos[b][one] = W.n;
    // Knight
    pos[c][one] = W.b;
    // Bishop
    pos[d][one] = W.q;
    // Queen
    pos[e][one] = W.k;
    // King
    pos[f][one] = W.b;
    // Bishop
    pos[g][one] = W.n;
    // Knight
    pos[h][one] = W.r;
    // Rook

    for (int i = h; i <= a; i++)
      pos[i][two] = W.p;
    // Pawns

    // Set up the initial positions of black pieces
    pos[a][eight] = B.r;
    // Rook
    pos[b][eight] = B.n;
    // Knight
    pos[c][eight] = B.b;
    // Bishop
    pos[d][eight] = B.q;
    // Queen
    pos[e][eight] = B.k;
    // King
    pos[f][eight] = B.b;
    // Bishop
    pos[g][eight] = B.n;
    // Knight
    pos[h][eight] = B.r;
    // Rook

    for (int i = h; i <= a; i++)
      pos[i][seven] = B.p;
    // Pawns
  }

  void clear() {
    // Clear the chessboard by setting all positions to empty
    for (int i = h; i <= a; i++)
      for (int j = one; j <= eight; j++)
        pos[i][j] = " ";
  }

  void reset() {
    // Reset the chessboard to the initial setup
    clear();
    setup();
  }

  brd(char team) {
    reset();
    this->team = team; // Set the team (black or white) for the chessboard
  }

  void drawBoard() {
    // Draw the chessboard with the current piece positions
    for (int i = 23; i >= 0; i--) {
      for (int j = a; j >= h; j--) {
        // Determine the color of the square based on row and column indices
        if ((j % 2 == 0 && (i - i % 3) % 2 == 0) ||
          (j % 2 == 1 && (i - i % 3) % 2 == 1)) {
          if ((i - 1) % 3 == 0)
            cout << bW << "  " << pos[j][(i - 1) / 3] << "  " << resetB
            << resetC; // Print the piece at the position
          else if (i == 0)
            cout << bW << green << "    "
            << static_cast<char>(a - j + 97); // Print the column labels
          else if (i % 3 == 2 && j == a)
            cout << bW << green << (i - i % 3) / 3 + 1
            << "    "; // Print the row labels
          else
            cout << bW << "     "; // Print an empty square
        }
        else {
          if ((i - 1) % 3 == 0)
            cout << bB << "  " << pos[j][(i - 1) / 3]
            << "  "; // Print the piece at the position
          else if (i == 0)
            cout << bB << green << "    "
            << static_cast<char>(a - j + 97); // Print the column labels
          else if (i % 3 == 2 && j == a)
            cout << bB << green << (i - i % 3) / 3 + 1
            << "    "; // Print the row labels
          else
            cout << bB << "     "; // Print an empty square
        }
      }
      cout << endl << resetC << resetB; // Reset the color after each row
    }
  }

  void drawBoardFlip() {
    // Draw the flipped version of the chessboard with the current piece
    // positions
    for (int i = 0; i < 24; i++) {
      for (int j = h; j <= a; j++) {
        // Determine the color of the square based on row and column indices
        if ((j % 2 == 0 && (i - i % 3) % 2 == 0) ||
          (j % 2 == 1 && (i - i % 3) % 2 == 1)) {
          if ((i - 1) % 3 == 0)
            cout << bW << "  " << pos[j][(i - 1) / 3] << "  ";
          // Print the piece at the position
          else if (i == 23)
            cout << bW << green << "    " << static_cast<char>(a - j + 97);
          // Print the column labels
          else if (i % 3 == 0 && j == h)
            cout << bW << green << (i - i % 3) / 3 + 1
            << "    "; // Print the row labels
          else
            cout << bW << "     "; // Print an empty square
        }
        else {
          if ((i - 1) % 3 == 0)
            cout << bB << "  " << pos[j][(i - 1) / 3]
            << "  "; // Print the piece at the position
          else if (i == 23)
            cout << bB << green << "    " << static_cast<char>(a - j + 97);
          // Print the column labels
          else if (i % 3 == 0 && j == h)
            cout << bB << green << (i - i % 3) / 3 + 1
            << "    "; // Print the row labels
          else
            cout << bB << "     ";
          // Print an empty square
        }
      }
      cout << endl << resetC;
      // Reset the color after each row
    }
  }

  void render() {
    // Render the chessboard based on the team's perspective
    if (team == 'w')
      drawBoard();
    // Draw the board as it is (white's perspective)

    if (team == 'b')
      drawBoardFlip();
    // Draw the board flipped (black's perspective)
  }

  bool checkTeamvalidity(int x, int y) {
    // Check if the piece at position (x, y) belongs to the current team
    if (team == 'b')
      if (isBlack(pos[x][y]))
        return true;
    if (team == 'w')
      if (isWhite(pos[x][y]))
        return true;

    return false;
  }

  vector<string> compress(string arg[8][8]) {
    vector<string> output;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        output.push_back(arg[i][j]);
        // Add each cell value to the output vector
      }
    }
    return output;
    // Return the compressed vector
  }

  void decompress(vector<string> arg, string output[8][8]) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        output[i][j] = arg[8 * i + j];
        // Assign each vector element to the corresponding position in the 2D
        // array
      }
    }
  }

  bool CaptureCheck(int x, int y) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (team == 'w') { // If the team is white
          if (isBlack(pos[i][j]) && pos[i][j] != B.k)
            // If the current position contains a black piece that is not the
            // black king
            if (checkMovevalidity(i, j, x, y, 'b'))
              // Check if the move from the black piece to the target position
              // is valid
              return false;
          // If valid, return false (capture move is possible)
          if (pos[i][j] ==
            B.k) { // If the current position contains the black king
            if ((i - x == 0 || abs(i - x) == 1) &&
              (j - y == 0 ||
                abs(j - y) ==
                1)) // Check if the target position is adjacent to the king
              return false; // If adjacent, return false (capture move is
            // possible)
          }
        }
        if (team == 'b') { // If the team is black
          if (isWhite(pos[i][j]) &&
            pos[i][j] != W.k) // If the current position contains a white
            // piece that is not the white king
            if (checkMovevalidity(i, j, x, y,
              'w')) // Check if the move from the white
              // piece to the target position is valid
              return false; // If valid, return false (capture move is possible)
          if (pos[i][j] ==
            W.k) { // If the current position contains the white king
            if ((i - x == 0 || abs(i - x) == 1) &&
              (j - y == 0 ||
                abs(j - y) ==
                1)) // Check if the target position is adjacent to the king
              return false; // If adjacent, return false (capture move is
            // possible)
          }
        }
      }
    }
    return true; // Return true (capture move is not possible)
  }

  bool CaptureCheck(int x, int y, string arg[8][8]) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (team == 'w') { // If the team is white
          if (isBlack(arg[i][j]) &&
            arg[i][j] !=
            B.k) // If the current position in the modified board contains
            // a black piece that is not the black king
            if (checkMovevalidity(
              i, j, x, y, 'b',
              arg)) { // Check if the move from the black piece to the
              // target position is valid
              return false; // If valid, return false (capture move is possible)
            }
          if (arg[i][j] == B.k) { // If the current position in the modified
            // board contains the black king
            if ((i - x == 0 || abs(i - x) == 1) &&
              (j - y == 0 || abs(j - y) == 1))
              // Check if the target position is adjacent to the king
              return false;
            // If adjacent, return false (capture move is possible)
          }
        }
        if (team == 'b') { // If the team is black
          if (isWhite(arg[i][j]) && arg[i][j] != W.k)
            // If the current position in the modified board contains a white
            // piece that is not the white king
            if (checkMovevalidity(i, j, x, y, 'w', arg))
              // Check if the move from the white piece to the target position
              // is valid
              return false; // If valid, return false (capture move is possible)
          if (arg[i][j] == W.k) {
            // If the current position in the modified board contains the white
            // king
            if ((i - x == 0 || abs(i - x) == 1) &&
              (j - y == 0 ||
                abs(j - y) ==
                1)) // Check if the target position is adjacent to the king
              return false;
            // If adjacent, return false (capture move is possible)
          }
        }
      }
    }
    return true; // Return true (capture move is not possible)
  }

  bool checkMovevalidity(int x1, int y1, int x2, int y2, char team) {
    // Check for castling kingside for white
    if (x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1) {
      if (team == 'w') {
        // Check if conditions for castling kingside are met
        if (!wKingMoved && !wRookRMoved && pos[f][one] == " " &&
          pos[g][one] == " " && pos[h][one] == W.r && pos[e][one] == W.k &&
          CaptureCheck(e, one) && CaptureCheck(f, one) &&
          CaptureCheck(g, one))
          return true;
      }
      // Check for castling kingside for black
      else {
        // Check if conditions for castling kingside are met
        if (!bKingMoved && !bRookRMoved && pos[f][eight] == " " &&
          pos[g][eight] == " " && pos[h][eight] == B.r &&
          pos[e][eight] == B.k && CaptureCheck(e, eight) &&
          CaptureCheck(f, eight) && CaptureCheck(g, eight))
          return true;
      }
      return false;
    }
    // Check for castling queenside for white
    else if (x1 == -2 && y1 == -2 && x2 == -2 && y2 == -2) {
      if (team == 'w') {
        // Check if conditions for castling queenside are met
        if (!wKingMoved && !wRookLMoved && pos[b][one] == " " &&
          pos[c][one] == " " && pos[d][one] == " " && pos[a][one] == W.r &&
          pos[e][one] == W.k && CaptureCheck(c, one) &&
          CaptureCheck(d, one) && CaptureCheck(e, one))
          return true;
      }
      // Check for castling queenside for black
      else {
        // Check if conditions for castling queenside are met
        if (!bKingMoved && !bRookLMoved && pos[b][eight] == " " &&
          pos[c][eight] == " " && pos[d][eight] == " " &&
          pos[a][eight] == B.r && pos[e][eight] == B.k &&
          CaptureCheck(c, eight) && CaptureCheck(d, one) &&
          CaptureCheck(e, one))
          return true;
      }
      return false;
    }
    // Check if coordinates are out of bounds
    else if (x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0 || x1 > 7 || x1 < 0 ||
      y1 > 7 || y1 < 0)
      return false;

    // Check if moving opponent's piece
    if (team == 'w' && isBlack(pos[x1][y1]))
      return false;
    if (team == 'b' && isWhite(pos[x1][y1]))
      return false;

    // Check if capturing own piece
    if (isWhite(pos[x1][y1])) {
      if (isWhite(pos[x2][y2]))
        return false;
    }
    else if (isBlack(pos[x1][y1])) {
      if (isBlack(pos[x2][y2]))
        return false;
    }

    // Check if moving a black pawn
    if (pos[x1][y1] == B.p) {
      // Check regular pawn move
      if (x1 == x2 && y2 == y1 - 1) {
        if (pos[x2][y2] != " ")
          return false;
      }
      // Check initial pawn move (two squares)
      else if (x1 == x2 && y2 == y1 - 2) {
        if (pos[x2][y2] != " ")
          return false;
        if (y1 != seven)
          return false;
      }

      else if ((x2 == x1 - 1 && y2 == y1 - 1) ||
        (x2 == x1 + 1 && y2 == y1 - 1)) {
        // Check for en passant move
        if (!(y1 == four &&
          moves[moves.size() - 1] ==
          (unConvertMove(x2, two) + "t" + unConvertMove(x2, four)) &&
          pos[x2][y2] == " " && pos[x2][four] == W.p)) {
          if (pos[x2][y2] == " ")
            return false;
        }
        if (isBlack(pos[x2][y2]))
          return false;
      }
      else
        return false;
    }

    if (pos[x1][y1] == B.n || pos[x1][y1] == W.n) {
      // Check for knight moves
      if (!((abs(x1 - x2) == 2 && abs(y1 - y2) == 1) ||
        (abs(x1 - x2) == 1 && abs(y1 - y2) == 2)))
        return false;
    }

    if (pos[x1][y1] == B.b || pos[x1][y1] == W.b) {
      // Check for bishop moves
      if (abs(x1 - x2) == abs(y1 - y2)) {
        if (x2 - x1 > 0) {
          if (y2 - y1 > 0) {
            // Check diagonal moves in the positive direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 + i][y1 + i] != " ")
                return false;
            }
          }
          else {
            // Check diagonal moves in the negative direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 + i][y1 - i] != " ")
                return false;
            }
          }
        }
        else {
          if (y2 - y1 > 0) {
            // Check diagonal moves in the positive direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 - i][y1 + i] != " ")
                return false;
            }
          }
          else {
            // Check diagonal moves in the negative direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 - i][y1 - i] != " ")
                return false;
            }
          }
        }
      }
      else
        return false; // if none of the criteria are met, return false because
      // move is invalid
    }

    if (pos[x1][y1] == B.r || pos[x1][y1] == W.r) {
      // Check for rook moves
      if (x1 == x2) {
        // Vertical move
        if (y2 - y1 > 0) {
          // Check for obstruction in the positive direction
          for (int i = y2 - 1; i > y1; i--) {
            if (pos[x1][i] != " ")
              return false;
          }
        }
        else {
          // Check for obstruction in the negative direction
          for (int i = y2 + 1; i < y1; i++) {
            if (pos[x1][i] != " ")
              return false;
          }
        }
      }
      else if (y1 == y2) {
        // Horizontal move
        if (x2 - x1 > 0) {
          // Check for obstruction in the positive direction
          for (int i = x2 - 1; i > x1; i--) {
            if (pos[i][y1] != " ")
              return false;
          }
        }
        else {
          // Check for obstruction in the negative direction
          for (int i = x2 + 1; i < x1; i++) {
            if (pos[i][y1] != " ")
              return false;
          }
        }
      }
      else
        return false;
    }

    if (pos[x1][y1] == B.q || pos[x1][y1] == W.q) {
      // Check for queen moves (combining bishop and rook moves)
      if (abs(x1 - x2) == abs(y1 - y2)) {
        // Diagonal move
        if (x2 - x1 > 0) {
          if (y2 - y1 > 0) {
            // Check diagonal moves in the positive direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 + i][y1 + i] != " ")
                return false;
            }
          }
          else {
            // Check diagonal moves in the negative direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 + i][y1 - i] != " ")
                return false;
            }
          }
        }
        else {
          if (y2 - y1 > 0) {
            // Check diagonal moves in the positive direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 - i][y1 + i] != " ")
                return false;
            }
          }
          else {
            // Check diagonal moves in the negative direction
            for (int i = abs(x1 - x2) - 1; i > 0; i--) {
              if (pos[x1 - i][y1 - i] != " ")
                return false;
            }
          }
        }
      }
      else if (x1 == x2) {
        // Vertical move
        if (y2 - y1 > 0) {
          // Check for obstruction in the positive direction
          for (int i = y2 - 1; i > y1; i--) {
            if (pos[x1][i] != " ")
              return false;
          }
        }
        else {
          // Check for obstruction in the negative direction
          for (int i = y2 + 1; i < y1; i++) {
            if (pos[x1][i] != " ")
              return false;
          }
        }
      }
      else if (y1 == y2) {
        // Horizontal move
        if (x2 - x1 > 0) {
          // Check for obstruction in the positive direction
          for (int i = x2 - 1; i > x1; i--) {
            if (pos[i][y1] != " ")
              return false;
          }
        }
        else {
          // Check for obstruction in the negative direction
          for (int i = x2 + 1; i < x1; i++) {
            if (pos[i][y1] != " ")
              return false;
          }
        }
      }
      else
        return false;
    }

    if (pos[x1][y1] == B.k) {
      // Check for king moves
      if ((x1 - x2 == 0 || abs(x1 - x2) == 1) &&
        (y1 - y2 == 0 || abs(y1 - y2) == 1)) {
        if (!CaptureCheck(x2, y2))
          return false;
      }
      else
        return false;
    }

    if (pos[x1][y1] == W.p) {
      // Check for white pawn moves
      if (x1 == x2 && y2 == y1 + 1) {
        // Move one step forward
        if (pos[x2][y2] != " ")
          return false;
      }
      else if (x1 == x2 && y2 == y1 + 2) {
        // Move two steps forward from the initial position
        if (pos[x2][y2] != " ")
          return false;
        if (y1 != two)
          return false;
      }
      else if ((x2 == x1 - 1 && y2 == y1 + 1) ||
        (x2 == x1 + 1 && y2 == y1 + 1)) {
        // Capture diagonally
        if (!(y1 == five &&
          moves[moves.size() - 1] ==
          (unConvertMove(x2, seven) + "t" + unConvertMove(x2, five)) &&
          pos[x2][y2] == " " && pos[x2][five] == B.p)) {
          if (pos[x2][y2] == " ") {
            return false;
          }
        }
        if (isWhite(pos[x2][y2]))
          return false;
      }
      else
        return false;
    }

    if (pos[x1][y1] == W.k) {
      // Check for king moves
      if ((x1 - x2 == 0 || abs(x1 - x2) == 1) &&
        (y1 - y2 == 0 || abs(y1 - y2) == 1)) {
        if (!CaptureCheck(x2, y2))
          return false;
      }
      else
        return false;
    }

    // if the move checks out, return that the move is valid (true)
    return true;
  }

  bool checkMovevalidity(int x1, int y1, int x2, int y2, char team,
    string arg[8][8]) {
    // Create a new instance of the 'brd' class with the specified team
    brd temp(team);

    // Copy the board state from the 'arg' parameter to the 'temp' object
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        temp.pos[i][j] = arg[i][j];
      }
    }

    // Call the 'checkMovevalidity' method of the 'temp' object with the
    // provided coordinates and team
    // and return what it outputs
    return temp.checkMovevalidity(x1, y1, x2, y2, team);
  }

  bool inCheck() {
    int x, y;

    // Check if the team is white ('w')
    if (team == 'w') {
      // Iterate over the board to find the white king's position
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          // If a white king is found, store its coordinates and exit the loop
          // using 'goto'
          if (pos[i][j] == W.k) {
            x = i;
            y = j;
            goto stop;
          }
        }
      }
    }

    // Check if the team is black ('b')
    if (team == 'b') {
      // Iterate over the board to find the black king's position
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          // If a black king is found, store its coordinates and exit the loop
          // using 'goto'
          if (pos[i][j] == B.k) {
            x = i;
            y = j;
            goto stop;
          }
        }
      }
    }

  stop:
    // Call the 'CaptureCheck' function with the coordinates of the king and
    // return the opposite of its result
    return !CaptureCheck(x, y);
  }

  bool inCheck(string arg[8][8]) {
    int x, y;

    // Check if the team is white ('w')
    if (team == 'w') {
      // Iterate over the board to find the white king's position in the
      // provided argument array
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          // If a white king is found, store its coordinates and exit the loop
          // using 'goto'
          if (arg[i][j] == W.k) {
            x = i;
            y = j;
            goto stop;
          }
        }
      }
    }

    // Check if the team is black ('b')
    if (team == 'b') {
      // Iterate over the board to find the black king's position in the
      // provided argument array
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          // If a black king is found, store its coordinates and exit the loop
          // using 'goto'
          if (arg[i][j] == B.k) {
            x = i;
            y = j;
            goto stop;
          }
        }
      }
    }

  stop:
    // Call the 'CaptureCheck' function with the coordinates of the king and the
    // provided argument array, and return the opposite of its result
    return !CaptureCheck(x, y, arg);
  }

  bool move(int x1, int y1, int x2, int y2) {
    // Check if the piece is trying to move to its current position
    if (x2 == x1 && y2 == y1 && !(x1 < 0)) {
      cout << warn
        << "Invalid move: piece cannot move to its current position!\n";
      return false;
    }

    // Check the validity of the move based on chess rules
    if (!checkMovevalidity(x1, y1, x2, y2, team)) {
      // Check if the move is a castle move (special case)
      if (x1 < 0 && y1 < 0 && x2 < 0 && y2 < 0) {
        cout << warn << "Invalid move: Unable to castle at the moment!\n";
        return false;
      }
      else {
        cout << warn << "Invalid move: " << pos[x1][y1] << warn
          << " cannot move to that square!\n";
        return false;
        // The move is not valid according to chess rules
        // Display an error message
      }
    }

    // Process the move and update the chess board state (castling)
    if (x1 < 0 && y1 < 0 && x2 < 0 && y2 < 0) {
      if (team == 'w') {
        wKingMoved = true;
        wRookRMoved = true;
        wRookLMoved = true;
      }
      else {
        bKingMoved = true;
        bRookRMoved = true;
        bRookLMoved = true;
      }
      goto skip;
    }

    // if not castling, check if square is valid piece or if it is blank
    if (pos[x1][y1] == " ") {
      cout << warn << "Invalid move: square selected is blank!\n";
      return false;
    }

    // Check if the white king is moved
    if (pos[x1][y1] == W.k) {
      wKingMoved = true;
    }

    // Check if the black king is moved
    if (pos[x1][y1] == B.k) {
      bKingMoved = true;
    }

    // Check if the white rook on the h-file is moved
    if (pos[h][one] != W.r) {
      wRookRMoved = true;
    }

    // Check if the white rook on the a-file is moved
    if (pos[a][one] != W.r) {
      wRookLMoved = true;
    }

    // Check if the black rook on the h-file is moved
    if (pos[h][eight] != B.r) {
      bRookRMoved = true;
    }

    // Check if the black rook on the a-file is moved
    if (pos[a][eight] != B.r) {
      bRookLMoved = true;
    }

  skip:

    // Check if the move puts the king in check
    if (inCheck()) {
      if (x1 < 0 && y1 < 0 && x2 < 0 && y2 < 0) {
        cout << warn << "Invalid move: Unable to castle in check!\n";
        return false;
      }

      // Check for the white team
      else if (team == 'w') {
        string posNew[8][8];

        // Create a copy of the current board position
        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
            posNew[i][j] = pos[i][j];

        // Move the piece and check if the king is still in check
        if (!(posNew[x1][y1] == W.p && abs(x1 - x2) == 1 && abs(y1 - y2) == 1 &&
          posNew[x2][y2] == " ")) {
          posNew[x2][y2] = posNew[x1][y1];
          posNew[x1][y1] = " ";
          if (inCheck(posNew)) {
            cout << warn << "Invalid move: King is in check!\n";
            return false;
          }
        }
        else {
          posNew[x2][y2] = posNew[x1][y1];
          posNew[x1][y1] = " ";
          posNew[x2][y1] = " ";

          if (inCheck(posNew)) {
            cout << warn << "Invalid move: King is in check!\n";
            return false;
          }
        }
      }

      // Check for the black team
      else if (team == 'b') {
        string posNew[8][8];

        // Create a copy of the current board position
        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
            posNew[i][j] = pos[i][j];

        // Move the piece and check if the king is still in check
        if (!(posNew[x1][y1] == B.p && abs(x1 - x2) == 1 && abs(y1 - y2) == 1 &&
          posNew[x2][y2] == " ")) {
          posNew[x2][y2] = posNew[x1][y1];
          posNew[x1][y1] = " ";
          if (inCheck(posNew)) {
            cout << warn << "Invalid move: King is in check!\n";
            return false;
          }
        }
        else {
          // perform en passant
          posNew[x2][y2] = posNew[x1][y1];
          posNew[x1][y1] = " ";
          posNew[x2][y1] = " ";

          // if king is in check and move is invalid, stop
          if (inCheck(posNew)) {
            cout << warn << "Invalid move: King is in check!\n";
            return false;
          }
        }
      }
    }

    if (x1 == -1 && y1 < 0 && x2 < 0 && y2 < 0) {
      // Perform castling kingside
      recordMove(x1, y1, x2, y2);
      recordPosPiece(x1, y1);
      recordPosition(pos);

      if (team == 'w') {
        // Update the positions for white kingside castling
        pos[e][one] = " ";
        pos[h][one] = " ";
        pos[g][one] = W.k;
        pos[f][one] = W.r;
        return true;
      }
      else {
        // Update the positions for black kingside castling
        pos[e][eight] = " ";
        pos[h][eight] = " ";
        pos[g][eight] = B.k;
        pos[f][eight] = B.r;
        return true;
      }
    }
    else if (x1 == -2 && y1 < 0 && x2 < 0 && y2 < 0) {
      // Perform castling queenside
      recordMove(x1, y1, x2, y2);
      recordPosPiece(x1, y1);
      recordPosition(pos);

      if (team == 'w') {
        // Update the positions for white queenside castling
        pos[e][one] = " ";
        pos[a][one] = " ";
        pos[c][one] = W.k;
        pos[d][one] = W.r;
        return true;
      }
      else {
        // Update the positions for black queenside castling
        pos[e][eight] = " ";
        pos[a][eight] = " ";
        pos[c][eight] = W.k;
        pos[d][eight] = W.r;
        return true;
      }
    }
    else {
      // Regular move
      string posNew[8][8];

      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
          posNew[i][j] = pos[i][j];

      if (!((pos[x1][y1] == B.p || pos[x1][y1] == W.p) && abs(x1 - x2) == 1 &&
        abs(y1 - y2) == 1 && pos[x2][y2] == " ")) {
        // Move the piece to the new position
        posNew[x2][y2] = posNew[x1][y1];
        posNew[x1][y1] = " ";
      }
      else {
        // Move the piece and perform en passant capture
        posNew[x2][y2] = posNew[x1][y1];
        posNew[x1][y1] = " ";
        posNew[x2][y1] = " ";
      }

      if (inCheck(posNew)) {
        cout << warn << "Unable to move piece: It is pinned!\n";
        return false;
      }

      // Check for pawn promotion
      if (!((pos[x1][y1] == B.p || pos[x1][y1] == W.p) && abs(x1 - x2) == 1 &&
        abs(y1 - y2) == 1 && pos[x2][y2] == " ")) {
        recordMove(x1, y1, x2, y2);
        recordPosPiece(x1, y1);
        pos[x2][y2] = pos[x1][y1];
        pos[x1][y1] = " ";

        // give promotion menu
        if ((y2 == eight || y2 == one) &&
          (pos[x2][y2] == W.p || pos[x2][y2] == B.p)) {
          cout << resetC
            << "PROMOTION! Select a piece you want your pawn to be promoted "
            "to:"
            << endl;
          cout << "1. Queen" << endl;
          cout << "2. Rook" << endl;
          cout << "3. Bishop" << endl;
          cout << "4. Knight" << endl;
          string input;
          cin >> input;

          // if selected piece is invalid, give error message and loop
          while (input.length() <= 1 && !(input[0] >= '1') &&
            !(input[0] <= '4')) {
            cout << warn
              << "\nInvalid Input! Please re-enter a valid number: (1-4)\n"
              << resetC;
          }

          string piece;

          // select piece based on user selection (white)
          if (team == 'w') {
            switch (stoi(input)) {
            case 1:
              piece = W.q;
              break;
            case 2:
              piece = W.r;
              break;
            case 3:
              piece = W.b;
              break;
            case 4:
              piece = W.n;
            }
            // select piece based on user selection (black)
          }
          else {
            switch (stoi(input)) {
            case 1:
              piece = B.q;
              break;
            case 2:
              piece = B.r;
              break;
            case 3:
              piece = B.b;
              break;
            case 4:
              piece = B.n;
            }
          }
          pos[x2][y2] = piece;
        }
        return true;
        recordPosition(pos);
        return true;
        // finish promotion and record position
      }
      else {
        // if promotion not happening, check for en passant
        recordMove(x1, y1, x2, y2);
        recordPosPiece(x1, y1);
        pos[x2][y2] = pos[x1][y1];
        pos[x1][y1] = " ";
        pos[x2][y1] = " ";
        recordPosition(pos);
        return true;
      }
    }
    return false;
  }

  void endChecker() {
    // Iterate over the positions on the board
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        // Iterate over the destination positions on the board
        for (int k = 0; k < 8; k++) {
          for (int l = 0; l < 8; l++) {
            // Check if the current position is not empty and is different from
            // the destination position
            if (pos[i][j] != " " && (i != k || j != l)) {
              // Check the move validity from the current position to the
              // destination position
              if (checkMovevalidity(i, j, k, l, team)) {
                // Create a copy of the board state
                string posNew[8][8];
                for (int m = 0; m < 8; m++) {
                  for (int n = 0; n < 8; n++) {
                    posNew[m][n] = pos[m][n];
                  }
                }
                // Perform the move on the copied board state
                posNew[k][l] = posNew[i][j];
                posNew[i][j] = " ";
                // Check if the move results in not being in check
                if (!inCheck(posNew)) {
                  // If not in check, exit the loop using 'goto'
                  goto end;
                }
              }
            }
          }
        }
      }
    }

    // Check if the current team is in check
    if (inCheck()) {
      // If in check, print the corresponding winning message based on the team
      cout << resetC << warnB << warn
        << "CHECKMATE! GAME OVER: " << (team == 'w' ? "Black " : "White ")
        << "wins!\n\n"
        << resetB << resetC;
      isRunning = false;
    }
    else {
      // If not in check, print the stalemate message
      cout << resetC << "STALEMATE! The game is a draw!\n\n";
      isRunning = false;
    }

  end:
    // Perform additional checks for the fifty-move rule and repetition
    fiftyMoveRuleCheck();
    repetitionCheck();
  }

  int convertMove(char input) {
    // Convert the input character to lowercase and check if it falls within the
    // valid file range
    if (tolower(input) <= 'h' && tolower(input) >= 'a')
      // Return the corresponding index by subtracting the character from 'a'
      // and reflecting it across the vertical axis (7 - ...)
      return 7 - (tolower(input) - 'a');
    // Check if the input character falls within the valid rank range
    else if (input >= '1' && input <= '8')
      // Return the corresponding index by subtracting '1' from the character
      return input - '1';
    else
      throw invalid_argument("convertMove");
  }

  int interpretMove(string input, int sel) {
    // create return arguments based on inputted move(coord 1, coord 2, coord 3,
    // coord 4)
    int* arg = new int[4];
    for (int i = 0; i < 4; i++) {
      arg[i] = 0;
    }

    // check move for kingside castle
    if (input == "O-O") {
      for (int i = 0; i < 4; i++)
        arg[i] = -1;
      return arg[sel];
    }

    // check move for queenside castle
    if (input == "O-O-O") {
      for (int i = 0; i < 4; i++)
        arg[i] = -2;
      return arg[sel];
    }

    // check if move is valid
    if (!(input.length() <= 6 && input.length() >= 2)) {
      cout << warn << "Invalid move input!\n";
      throw genericError();
    }

    // check for most basic input type (square 1 to square 2)
    if ((input.length() == 4 && tolower(input[0]) >= 'a' &&
      tolower(input[0]) <= 'h') &&
      (tolower(input[2]) >= 'a' && tolower(input[2]) <= 'h') &&
      (input[1] >= '1' && input[1] <= '8') &&
      (input[3] >= '1' && input[3] <= '8')) {
      arg[0] = convertMove(input[0]);
      arg[1] = convertMove(input[1]);
      arg[2] = convertMove(input[2]);
      arg[3] = convertMove(input[3]);
      return arg[sel];
      // return coord requested
    }

    // check for basic square 1 to square 2 move capture
    if ((input.length() == 5 && tolower(input[0]) >= 'a' &&
      tolower(input[0]) <= 'h') &&
      (tolower(input[3]) >= 'a' && tolower(input[3]) <= 'h') &&
      (input[1] >= '1' && input[1] <= '8') &&
      (input[4] >= '1' && input[4] <= '8') && tolower(input[2]) == 'x') {
      arg[0] = convertMove(input[0]);
      arg[1] = convertMove(input[1]);
      arg[2] = convertMove(input[3]);
      arg[3] = convertMove(input[4]);
      return arg[sel];
    }

    // check for basic move, but with piece name in front
    if (((input.length() == 6 && tolower(input[0]) == 'p') ||
      tolower(input[0]) == 'n' || tolower(input[0]) == 'b' ||
      tolower(input[0]) == 'r' || tolower(input[0]) == 'q' ||
      tolower(input[0]) == 'k') &&
      (tolower(input[1]) >= 'a' && tolower(input[1]) <= 'h') &&
      (tolower(input[4]) >= 'a' && tolower(input[4]) <= 'h') &&
      (input[2] >= '1' && input[2] <= '8') &&
      (input[5] >= '1' && input[5] <= '8') && tolower(input[3]) == 'x') {
      arg[0] = convertMove(input[1]);
      arg[1] = convertMove(input[2]);
      arg[2] = convertMove(input[4]);
      arg[3] = convertMove(input[5]);
      return arg[sel];
    }

    // check for pawn basic move
    if ((input.length() == 2 && tolower(input[0]) >= 'a' &&
      tolower(input[0]) <= 'h') &&
      input[0] != 'B' && (input[1] >= '1' && input[1] <= '8')) {
      arg[2] = convertMove(input[0]);
      arg[3] = convertMove(input[1]);
      // scroll through all possible pawn moves with user selected input
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == W.p || pos[i][j] == B.p)) {
            if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
              if (abs(arg[2] - i) == 1 && abs(arg[3] - j) == 1) {
                // if move is a capture, warn the user that they must have
                // capture notation present
                cout << warn
                  << "Invalid input: Move selected is a capture, correct "
                  "notation should have \"x\" within!\n";
                throw genericError();
              }
              // return move
              arg[0] = i;
              arg[1] = j;
              return arg[sel];
            }
          }
        }
      }
      // if no pawn can move there, throw error message
      cout << warn << "Invalid move: No " << (team == 'w' ? W.p : B.p) << warn
        << " able to move to that square!\n";
      throw genericError();
    }

    // do same as last function, but for captures (pawn capture)
    if ((input.length() == 3 && tolower(input[1]) >= 'a' &&
      tolower(input[1]) <= 'h') &&
      input[0] != 'B' && (input[2] >= '1' && input[2] <= '8') &&
      tolower(input[0]) == 'x') {

      arg[2] = convertMove(input[1]);
      arg[3] = convertMove(input[2]);
      int counter = 0;
      // scroll through all possible pawn captures
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == W.p || pos[i][j] == B.p)) {
            if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
              if (abs(arg[3] - j) == 1 && abs(arg[2] - i) == 1) {
                counter++;
              }
            }
          }
        }
      }

      if (counter > 1) {
        // if more than one possible captures exist with same notation, warn
        // user and throw error
        cout << warn
          << "Invalid input: More than one move fits this notation, please "
          "specify which square the piece is on to avoid ambiguity!\n";
        throw genericError();
      }
      // scroll through all possible moves once again, once determined only one
      // move can exist
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == W.p || pos[i][j] == B.p)) {
            if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
              if (abs(arg[3] - j) == 1 && arg[2] == i) {
                cout << warn
                  << "Invalid input: Move selected is not a capture, remove "
                  "the \"x\" within!\n";
                // if move is not a capture, return error message
                throw genericError();
              }
              arg[0] = i;
              arg[1] = j;
              return arg[sel];
              // return move argument
            }
          }
        }
      }
      cout << warn << "Invalid move: No " << (team == 'w' ? W.p : B.p) << warn
        << " able to capture that square!\n";
      // if no piece able to capture that square, return error message
      throw genericError();
    }

    // more specific pawn move, same logic applies but pawn move is more
    // specific
    if (input.length() == 4 &&
      (tolower(input[0]) >= 'a' && tolower(input[0]) <= 'h') &&
      input[0] != 'B' &&
      (tolower(input[2]) >= 'a' && tolower(input[2]) <= 'h') &&
      (input[3] >= '1' && input[3] <= '8') && tolower(input[1]) == 'x') {

      // set arguments
      arg[2] = convertMove(input[2]);
      arg[3] = convertMove(input[3]);
      int counter = 0;
      int i = convertMove(input[0]);

      // sroll through all possible moves
      for (int j = 0; j < 8; j++) {
        if (((arg[2] != i) || (arg[3] != j)) &&
          (pos[i][j] == W.p || pos[i][j] == B.p)) {
          if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
            if (abs(arg[3] - j) == 1 && abs(arg[2] - i) == 1) {
              counter++;
            }
          }
        }
      }

      if (counter > 1) {
        // if more than one moves fit this parameter, throw error
        cout << warn
          << "Invalid input: More than one move fits this notation, please "
          "specify which square the piece is on to avoid ambiguity!\n";
        throw genericError();
      }

      // once determined only one move exists, repeat process
      for (int j = 0; j < 8; j++) {
        if (((arg[2] != i) || (arg[3] != j)) &&
          (pos[i][j] == W.p || pos[i][j] == B.p)) {
          if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
            if (abs(arg[3] - j) == 1 && arg[2] == i) {
              // if move is not a capture, warn user
              cout << warn
                << "Invalid input: Move selected is not a capture, remove "
                "the \"x\" within!\n";
              throw genericError();
            }
            // return arguments
            arg[0] = i;
            arg[1] = j;
            return arg[sel];
          }
        }
      }

      // return error if no piece able to do this
      cout << warn << "Invalid move: No " << (team == 'w' ? W.p : B.p) << warn
        << " able to capture that square!\n";
      throw genericError();
    }

    // if move takes normal input parameter (not typical pawn move) check for
    // length validity
    if (input.length() >= 3 && input.length() <= 5) {
      string piece1;
      string piece2;

      // check piece type
      switch (tolower(input[0])) {
        // perform same exact checks as in previous function for pawns
      case 'p': {
        if (input.length() == 3 &&
          (tolower(input[1]) >= 'a' && tolower(input[1]) <= 'h') &&
          (input[2] >= '1' && input[2] <= '8')) {

          arg[2] = convertMove(input[1]);
          arg[3] = convertMove(input[2]);
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              if (((arg[2] != i) || (arg[3] != j)) &&
                (pos[i][j] == W.p || pos[i][j] == B.p)) {
                if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
                  if (abs(arg[2] - i) == 1 && abs(arg[3] - j) == 1 &&
                    pos[arg[2]][arg[3]] != " ") {
                    cout << warn
                      << "Invalid input: Move selected is a capture, "
                      "correct notation should have \"x\" within!\n";
                    throw genericError();
                  }
                  arg[0] = i;
                  arg[1] = j;
                  return arg[sel];
                }
              }
            }
          }
          cout << warn << "Invalid move: No " << (team == 'w' ? W.p : B.p)
            << warn << " able to move to that square!\n";
          throw genericError();
        }

        if (input.length() == 4 &&
          (tolower(input[2]) >= 'a' && tolower(input[2]) <= 'h') &&
          (input[3] >= '1' && input[3] <= '8') && tolower(input[1]) == 'x') {

          arg[2] = convertMove(input[2]);
          arg[3] = convertMove(input[3]);
          int counter = 0;
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              if (((arg[2] != i) || (arg[3] != j)) &&
                (pos[i][j] == W.p || pos[i][j] == B.p)) {
                if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
                  counter++;
                }
              }
            }
          }

          if (counter > 1) {
            cout << warn
              << "Invalid input: More than one move fits this notation, "
              "please specify which square the piece is on to avoid "
              "ambiguity!\n";
            throw genericError();
          }

          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              if (((arg[2] != i) || (arg[3] != j)) &&
                (pos[i][j] == W.p || pos[i][j] == B.p)) {
                if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
                  if (abs(arg[3] - j) == 1 && arg[2] == i &&
                    pos[arg[2]][arg[3]] == " ") {
                    cout << warn
                      << "Invalid input: Move selected is not a capture, "
                      "remove the \"x\" within!\n";
                    throw genericError();
                  }
                  arg[0] = i;
                  arg[1] = j;
                  return arg[sel];
                }
              }
            }
          }
          cout << warn << "Invalid move: No " << (team == 'w' ? W.p : B.p)
            << warn << " able to capture that square!\n";
          throw genericError();
        }
        break;
      }
      case 'n':
        // check for knight piece
        piece1 = W.n;
        piece2 = B.n;
        break;
      case 'b':
        // check for bishop piece
        if (input[0] == 'B') {
          piece1 = W.b;
          piece2 = B.b;
          break;
        }
        else {
          cout << "Invalid move: no pawn able to move to that square!\n";
          cout << "NOTE: the 'B' in your input must be capatilized if you "
            "want to move the Bishop!\n";
          throw genericError();
        }
      case 'r':
        // check for rook piece
        piece1 = W.r;
        piece2 = B.r;
        break;
      case 'q':
        // check for queen piece
        piece1 = W.q;
        piece2 = B.q;
        break;
      case 'k':
        // check for king piece
        piece1 = W.k;
        piece2 = B.k;
        break;
      }

      // check if piece exists, else throw error (goto end)
      if (piece1.length() == 0)
        goto end;

      // check for typical piece move
      if (input.length() == 3 &&
        (tolower(input[1]) >= 'a' && tolower(input[1]) <= 'h') &&
        (input[2] >= '1' && input[2] <= '8')) {

        // establish base arguments
        arg[2] = convertMove(input[1]);
        arg[3] = convertMove(input[2]);
        int counter = 0;

        // scroll through all moves with selected piece notation
        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
            if (((arg[2] != i) || (arg[3] != j)) &&
              (pos[i][j] == piece1 || pos[i][j] == piece2))
              if (checkMovevalidity(i, j, arg[2], arg[3], team))
                counter++;

        if (counter > 1) {
          // if more than one possible move exists fitting notation, return
          // error
          cout
            << warn
            << "Invalid input: More than one move fits this notation, please "
            "specify which square the piece is on to avoid ambiguity!\n";
          throw genericError();
        }

        // if only one possible move exists, scroll through moves again
        for (int i = 0; i < 8; i++) {
          for (int j = 0; j < 8; j++) {
            if (((arg[2] != i) || (arg[3] != j)) &&
              (pos[i][j] == piece1 || pos[i][j] == piece2)) {
              if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
                if (pos[arg[2]][arg[3]] != " ") {
                  // if selected mvoe isnt a capture, throw error
                  cout << warn
                    << "Invalid input: Move selected is a capture, correct "
                    "notation should have \"x\" within!\n";
                  throw genericError();
                }
                // return arguments and move
                arg[0] = i;
                arg[1] = j;
                return arg[sel];
              }
            }
          }
        }
        // if no piece able to move to these squares, return error message
        cout << warn << "Invalid move: No " << (team == 'w' ? piece1 : piece2)
          << warn << " able to move to that square!\n";
        throw genericError();
      }

      // if input is a capture perform same checks as previous function
      if (input.length() == 4 &&
        (tolower(input[2]) >= 'a' && tolower(input[2]) <= 'h') &&
        (input[3] >= '1' && input[3] <= '8') && tolower(input[1]) == 'x') {

        arg[2] = convertMove(input[2]);
        arg[3] = convertMove(input[3]);
        int counter = 0;
        // scroll through all possible moves
        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
            if (((arg[2] != i) || (arg[3] != j)) &&
              (pos[i][j] == piece1 || pos[i][j] == piece2))
              if (checkMovevalidity(i, j, arg[2], arg[3], team))
                counter++;

        if (counter > 1) {
          // if more than one move exists with these parameters, throw error
          cout
            << warn
            << "Invalid input: More than one move fits this notation, please "
            "specify which square the piece is on to avoid ambiguity!\n";
          throw genericError();
        }

        // if only one move exists, scroll through them
        for (int i = 0; i < 8; i++) {
          for (int j = 0; j < 8; j++) {
            if (((arg[2] != i) || (arg[3] != j)) &&
              (pos[i][j] == piece1 || pos[i][j] == piece2)) {
              if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
                if (pos[arg[2]][arg[3]] == " ") {
                  // if move is not a capture, return false and throw error
                  cout << warn
                    << "Invalid input: Move selected is not a capture, "
                    "remove the \"x\" within!\n";
                  throw genericError();
                }
                arg[0] = i;
                arg[1] = j;
                return arg[sel];
              }
            }
          }
        }
        cout << warn << "Invalid move: No " << (team == 'w' ? piece1 : piece2)
          << warn << " able to capture that square!\n";
        throw genericError();
      }

      // same logic as previous moves, except with added precision (extra
      // character/rank provided)
      if (input.length() == 4 &&
        (tolower(input[1]) >= 'a' && tolower(input[1]) <= 'h') &&
        (tolower(input[2]) >= 'a' && tolower(input[2]) <= 'h') &&
        (input[3] >= '1' && input[3] <= '8')) {

        arg[2] = convertMove(input[2]);
        arg[3] = convertMove(input[3]);
        int counter = 0;
        int i = convertMove(input[1]);

        for (int j = 0; j < 8; j++)
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == piece1 || pos[i][j] == piece2))
            if (checkMovevalidity(i, j, arg[2], arg[3], team))
              counter++;

        if (counter > 1) {
          cout
            << warn
            << "Invalid input: More than one move fits this notation, please "
            "specify which square the piece is on to avoid ambiguity!\n";
          throw genericError();
        }

        for (int j = 0; j < 8; j++) {
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == piece1 || pos[i][j] == piece2)) {
            if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
              if (pos[arg[2]][arg[3]] != " ") {
                cout << warn
                  << "Invalid input: Move selected is a capture, correct "
                  "notation should have \"x\" within!\n";
                throw genericError();
              }
              arg[0] = i;
              arg[1] = j;
              return arg[sel];
            }
          }
        }
        cout << warn << "Invalid move: No " << (team == 'w' ? piece1 : piece2)
          << warn << " able to move to that square!\n";
        throw genericError();
      }

      // same logic, but move is a capture this time
      if (input.length() == 5 &&
        (tolower(input[1]) >= 'a' && tolower(input[1]) <= 'h') &&
        (tolower(input[3]) >= 'a' && tolower(input[3]) <= 'h') &&
        (input[4] >= '1' && input[4] <= '8') && tolower(input[2]) == 'x') {

        arg[2] = convertMove(input[3]);
        arg[3] = convertMove(input[4]);
        int counter = 0;
        int i = convertMove(input[1]);

        for (int j = 0; j < 8; j++)
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == piece1 || pos[i][j] == piece2))
            if (checkMovevalidity(i, j, arg[2], arg[3], team))
              counter++;

        if (counter > 1) {
          cout
            << warn
            << "Invalid input: More than one move fits this notation, please "
            "specify which square the piece is on to avoid ambiguity!\n";
          throw genericError();
        }

        for (int j = 0; j < 8; j++) {
          if (((arg[2] != i) || (arg[3] != j)) &&
            (pos[i][j] == piece1 || pos[i][j] == piece2)) {
            if (checkMovevalidity(i, j, arg[2], arg[3], team)) {
              if (pos[arg[2]][arg[3]] == " ") {
                cout << warn
                  << "Invalid input: Move selected is not a capture, remove "
                  "the \"x\" within!\n";
                throw genericError();
              }
              arg[0] = i;
              arg[1] = j;
              return arg[sel];
            }
          }
        }
        cout << warn << "Invalid move: No " << (team == 'w' ? piece1 : piece2)
          << warn << " able to capture that square!\n";
        throw genericError();
      }
    }

    // the ending of the function
  end:
    // if move is still invalid after all this, throw an error and warn user of
    // invalid input
    cout << warn << "Invalid move input!\n";
    throw genericError();
  }

  string unConvertMove(int x, int y) {
    string output;
    // Append the converted file by pushing the character computed as 7 - x +
    // 'a'
    output.push_back(7 - x + 'a');
    // Append the converted rank by pushing the character computed as y + '1'
    output.push_back(y + '1');
    return output;
  }

  string unConvertMove(int x) {
    string output;
    // Append the converted file by pushing the character computed as 7 - x +
    // 'a'
    output.push_back(7 - x + 'a');
    return output;
  }

  void recordMove(int x1, int y1, int x2, int y2) {
    if (x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1) {
      // Special case: King-side castle
      moves.push_back("O-O");
      return;
    }
    else if (x1 == -2 && y1 == -2 && x2 == -2 && y2 == -2) {
      // Special case: Queen-side castle
      moves.push_back("O-O-O");
      return;
    }
    else
      moves.push_back(unConvertMove(x1, y1) + "t" + unConvertMove(x2, y2));
  }

  void recordPosPiece(int x, int y) {
    // Check if position is empty
    if (x < 0)
      movesPiece.push_back('+');

    char piece;

    // Determine the type of piece at the position
    if (pos[x][y] == W.k)
      piece = 'K';
    else if (pos[x][y] == W.q)
      piece = 'Q';
    else if (pos[x][y] == W.r)
      piece = 'R';
    else if (pos[x][y] == W.b)
      piece = 'B';
    else if (pos[x][y] == W.n)
      piece = 'N';
    else if (pos[x][y] == W.p)
      piece = 'P';

    // Record the piece in the movesPiece vector
    movesPiece.push_back(piece);
  }

  void recordPosition(string pos[8][8]) {
    // Create a vector to store the compressed positions
    vector<string> arg;

    // Iterate through each position on the chessboard
    for (int i = 0; i < 64; i++)
      arg.push_back(
        compress(pos)[i]); // Compress the position and add it to the vector

    // Add the compressed position vector to the positions vector
    positions.push_back(arg);
  }

  void fiftyMoveRuleCheck() {
    int first; // Variable to store the index of the first occurrence of 'P' in
    // movesPiece

// Find the index of the first occurrence of 'P' in movesPiece
    for (int i = movesPiece.size() - 1; i >= 0; i--)
      if (movesPiece[i] == 'P')
        first = i + 1;

    // Check if the number of half-moves since the last pawn move or capture
    // exceeds 50
    if (static_cast<int>(movesPiece.size() / 2 + movesPiece.size() % 2) -
      static_cast<int>(first) / 2 + first % 2 >=
      50) {
      cout << resetC << "50 move rule! The game is a draw!\n\n";
      isRunning = false;
    }
  }

  void repetitionCheck() {
    int max = 0; // Variable to store the maximum count of repeated positions

    // Iterate through each position in the positions vector
    for (int i = 0; i < positions.size(); i++) {
      int counter = 0; // Counter to keep track of the number of repetitions

      // Compare the current position with all other positions in the vector
      for (int j = 0; j < positions.size(); j++) {
        bool isSame = true; // Flag to indicate if the positions are the same

        // Compare each square of the positions
        for (int k = 0; k < 64; k++) {
          if (positions[j][k] != positions[i][k]) {
            isSame = false;
          }
        }

        // Increment the counter if the positions are the same (excluding the
        // current position)
        if (isSame && i != j) {
          counter++;
        }
      }

      // Update the maximum count of repetitions
      if (max < counter)
        max = counter;
    }

    // If the maximum count of same positions is 2 or more, declare a draw (>=
    // 2+1 equal positions)
    if (max >= 2) {
      cout << resetC << "Repetition! The game is a draw!\n\n";
      isRunning = false;
    }
  }
};