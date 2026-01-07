<a name="chess-a-c++-console-experience"></a>

# 🕹️ CHESS: A C++ Console Experience ♟️

<p align="center">
  A compact, object-oriented C++ implementation of chess playable in the terminal. This project demonstrates OOP, inheritance, polymorphism, move-generation, board representation, and file I/O for saving/loading games. <br><br>
  The project goes above and beyond by supporting <b>all standard algebraic chess notation (SAN)</b>
  inputs, including captures, checks, checkmates, castling, promotions, and disambiguation.
  <br>
</p>
<p align="center">
<b>Example</b><br>
e4<br>
Nf3<br>
Bxe6+<br>
O-O<br>
c8=Q# <br> <a href="https://github.com/AndyDerevyanko/Replit-Chess/issues">Report Bug/Request Feature</a>
</p>

## 📚 Table of Contents

* [What is CHESS?](#-what-is-chess)
* [Controls](#-controls)
* [Working Demo](#-working-demo)
* [Features](#-features)
* [Implementation](#-implementation)
* [UML Diagrams](#-uml-diagrams)
* [PERT Chart](#-pert-chart)
* [Flowchart](#-flowchart)
* [Unicode & Console Compatibility (Important)](#-unicode-&-console-compatibility-important)

<a name="-what-is-chess"></a>

## ❓ What is CHESS?

<img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/logo.jpg" width="200" align="left">

Chess is a two-player strategy board game played on an 8×8 grid. Each side (White and Black) commands sixteen pieces with different movement rules. The objective is to checkmate the opponent's king — put the king into a position from which it cannot escape capture.

My Chess program focuses on clean object-oriented design, readable code, and all proper rule implementation (castling, en passant, promotion, stalemate/checkmate detection, and move legality checks).

<br>
<a name="-controls"></a>

## 🌟 Controls (default)

This project uses a keyboard-driven console UI.

* square x square or square square (capture second square using the first or move)
* piece square x square or piece square square
* Classical move notation: Nd3, Kf4, etc. **with** two different ways to enter pawn moves: xe4, d5 **or** pxe2, pxe5

In the event classical move notation is used, the program can intelligently determine if the move is ambiguous (ex. Rd8, but two different rooks can move to that square), and prompts the user to be more specific with their move:
ex. Rd8 -> Rh8d8

<a name="-working-demo"></a>

## 🎮 Working Demo

Try out a working demo [here](https://onlinegdb.com/1PPKiWy2tA)

<p align="left" style="">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/demo1.png" alt="demo" width="300">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/demo2.png" alt="demo" width="300">
</p>

<a name="-features"></a>

## 🧩 Features

* Full legal move generation for all pieces (King, Queen, Rook, Bishop, Knight, Pawn)
* Special rules: castling, en passant, promotion (to Q/R/B/N)
* Check, checkmate, and stalemate detection
* Move validation to prevent illegal moves that leave the king in check
* Command-line interface for human vs human
* Support for ALL recognized chess notation
* Support for chess notation requires complex reverse-piece search and move disambiguation, which this program implements
  ex. with a move like Bd4, the program has to search for a square with a valid bishop, if two pieces selected can move to the same square the program prompts user to specify which piece they intend to move, etc.

<a name="-implementation"></a>

## 👨‍💻 Implementation

This project emphasizes modular, testable OOP design that centers on a primary class and organizational structures for the game state.

The "Board" Object (brd):
The brd object is the central hub of the program, that manages data and all the rules

The Piece Representations (wh and bl):
Instead of having a separate class for every individual piece on the board, my program organizes them into two primary structures based on their "Team." These structures act as the "blueprints" for how pieces look in the console

Coordinate Mappers:
My program utilizes boardHorizontal and boardVertical enumerations to bridge the gap between human chess coordinates (like "e4") and the program's array indices (like [4][4]).

Exception Handling:
The genericError class is used as a lightweight object to catch and handle invalid inputs or illegal game states without crashing the program

<a name="-uml-diagrams"></a>

## 👨‍👩‍👧‍👦 UML Diagrams

UML Diagrams for each object are available below:

<a name="brd-uml-diagram"></a>

### Brd UML Diagram

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/brd_uml.png" alt="brd uml" width="600">
</p>

<a name="wh-uml-diagram"></a>

### wh UML Diagram

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/wh_uml.png" alt="wh UML" width="600">
</p>

<a name="bl-uml-diagram"></a>

### bl UML Diagram

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/bl_uml.png" alt="bl UML" width="600">
</p>

<a name="genericerror-uml-diagram"></a>

### genericError UML Diagram

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/genericError_uml.png" alt="genericError UML" width="600">
</p>

<a name="interested-in-how-this-project-was-developed"></a>

## 📊 PERT Chart

### Interested in how this project was developed?

A PERT chart is shown below. Keep in mind this project was created on REPLIT before being integrated into Github.

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/pert_chart.png" alt="pert chart" width="600">
</p>

<a name="-flowchart"></a>

## 📈 Flowchart

A basic rundown of how this program functions:

<p align="left">
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/flowchart.png" alt="flow chart" width="600">
</p>

<a name="-unicode-&-console-compatibility-important"></a>

## 🖥️ Unicode & Console Compatibility (Important)

If the chess pieces appear as garbled characters (e.g., `ΓÖ£`, `ΓÖƒ∩╕Ä`) instead of symbols (`♜ ♞ ♝`), this is usually due to **Terminal Encoding** or **Font Limitations**, particularly on Windows systems.

### Why is this happening?
Most modern environments (Linux, macOS, Replit) use **UTF-8** encoding by default. However, the legacy Windows Command Prompt often defaults to **ANSI**, which cannot interpret high-quality Unicode chess symbols.


### 🔧 Solutions for Windows Users

#### 1. Change the Terminal Code Page
Before running the game, you need to tell your terminal to use UTF-8. Run this command in your command prompt or PowerShell:

```bat
chcp 65001
```

Note: This change only lasts for the current terminal session.
#### 2. Use a Unicode-Compatible Font

Even with the right encoding, your terminal needs a font that actually contains the chess glyphs. If you see empty boxes or question marks, switch your terminal font to one of these:

    Cascadia Code / Cascadia Mono (Recommended)

    JetBrains Mono

    Fira Code

    MS Gothic (Standard on most Windows systems)

#### 3. Recommended: Use Windows Terminal

If you are using the old cmd.exe, I highly recommend downloading the modern Windows Terminal from the Microsoft Store. It handles Unicode, emojis, and UTF-8 natively without extra configuration.

#### 💻 VS Code Specific Setup

If you are running the project directly inside the VS Code integrated terminal:

- Check Encoding: Ensure the status bar at the bottom right of VS Code says UTF-8. If it says Windows 1252, click it and select "Reopen with Encoding" → "UTF-8".
- Update Settings: To make the UTF-8 fix permanent in VS Code, add this to your settings.json:

```json
{
  "terminal.integrated.env.windows": {
    "CHCP": "65001"
  }
}

####  🏳️ Fallback Mode

If your environment simply cannot support Unicode symbols, you can replace the pieces with letters in the *chess.h* file:

```struct bl {
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
```

Replace the pieces like: 
Rook	♜-> R
Knight	♞-> N
Bishop	♝-> B
Queen	♛-> Q
King	♚-> K
Pawn	♟-> p
