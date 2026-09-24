# Minesweeper
A simple generic console minesweeper game that starts by default with a $9 \times 9$ field with $10$ mines.
### Game controls
Game supports two types of commands:
1. ``o x y``  Open the cell in column x, row y
2. ``f x y``  Place or remove a flag
### Example output
```text
Minesweeper (9 rows, 9 columns, 10 mines)
Commands:
  o x y  Open the cell in column x, row y
  f x y  Place or remove a flag
Coordinates start at 1.
     1 2 3 4 5 6 7 8 9
1 |  . . . . . . . . .
2 |  . . . . . . . . .
3 |  . . . . . . . . .
4 |  . . . . . . . . .
5 |  . . . . . . . . .
6 |  . . . . . . . . .
7 |  . . . . . . . . .
8 |  . . . . . . . . .
9 |  . . . . . . . . .
Enter command: 
```
It'll wait for you to make a move and then provide an updated filed. Enjoy!