# Minesweeper
This is one of the projects in Fundamentals of Programming II at University of FLorida. I did this project for fun because I implemented the game logic without a UI during my sophomore year and one of my friend show me this and I just want to complete my skills.

---

## Building and Running Process, under Linux(Ubantu) OS, C++11
- Install Simple Fast Multimedia Library: https://www.sfml-dev.org/download/sfml/2.5.1/
- Compile and link resource code: g++ -c main.cpp Board.cpp Helper.cpp Tile.cpp
- Translate to object code in one executable file: g++ main.o Helper.o Tile.o Board.o -o Minesweeper-app -lsfml-graphics -lsfml-window -lsfml-system
- Run: ./Minesweeper-app

---

### See Project Descriptions in details on PDF
