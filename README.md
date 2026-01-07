<a name="chess-a-c++-console-experience"></a>

# 🕹️ CHESS: A C++ Console Experience ♟️

<p align="center">
  A compact, object-oriented C++ implementation of chess playable in the terminal. This project demonstrates OOP, inheritance, polymorphism, move-generation, board representation, and file I/O for saving/loading games. <br><br>
  The project goes above and beyond by supporting <b>all standard algebraic chess notation (SAN)</b>
  inputs, including captures, checks, checkmates, castling, promotions, and disambiguation.
  <br><br>
</p>
<p align="center">
<b>Example</b><br>
-<br>
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
  <img src="https://raw.githubusercontent.com/AndyDerevyanko/Replit-Chess/main/images/genericError_UML.png" alt="genericError UML" width="600">
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

If your chess pieces display **correctly on Replit but appear as garbled characters** in VS Code (e.g. `ΓÖ£`, `ΓÖƒ∩╕Ä`), this is **not a bug in the program**. It is caused by **character encoding and font differences**, especially on Windows.

### Why this happens

* Chess symbols (`♜ ♞ ♝ ♛ ♚ ♟`) are **Unicode characters**.
* Replit forces **UTF-8** encoding everywhere.
* VS Code on Windows may:

  * Open files as **Windows-1252 / ANSI** instead of UTF-8
  * Use a terminal font without Unicode support
  * Run the program in a console that is not set to UTF-8

<a name="fix-1-ensure-source-files-are-utf-8"></a>

### Fix 1 — Ensure source files are UTF-8

In VS Code:

1. Open the source file
2. Bottom-right → click the encoding label (e.g. `Windows 1252`)
3. Select **Reopen with Encoding → UTF-8**
4. Save the file

<a name="fix-2-force-utf-8-in-the-terminal-windows"></a>

### Fix 2 — Force UTF-8 in the terminal (Windows)

Run this **before executing the program**:

```bat
chcp 65001
```

Or add this to your VS Code `settings.json`:

```json
{
  "terminal.integrated.env.windows": {
    "CHCP": "65001"
  }
}
```

<a name="fix-3-use-a-unicode-capable-font"></a>

### Fix 3 — Use a Unicode-capable font

Recommended terminal fonts:

* Cascadia Mono
* Consolas
* Fira Code
* JetBrains Mono

<a name="fix-4-use-wide-characters-in-c++-recommended"></a>

### Fix 4 — Use wide characters in C++ (recommended)

For best portability, output chess pieces using wide characters:

```cpp
#include <iostream>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "");
    std::wcout << L"♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
";
}
```

Compile with UTF-8 support:

```bash
g++ -std=c++17 -finput-charset=UTF-8 -fexec-charset=UTF-8 main.cpp
```

<a name="fallback-ascii-mode"></a>

### Fallback (ASCII mode)

If Unicode is not supported, the board can be rendered using ASCII:

```
r n b q k b n r
p p p p p p p p
```

This ensures compatibility across all terminals.
