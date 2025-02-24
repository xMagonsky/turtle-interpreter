# Logo Interpreter in C++

## Overview
This project implements a simple Logo programming language interpreter in C++. The Logo language is an educational programming language primarily used for teaching programming concepts and creating geometric drawings, such as fractals and spirals, by controlling a virtual turtle. This interpreter reads Logo commands from a text file, processes them, and generates a visual output in the form of a BMP (binary image file) representing the turtle's path.

## Features
- Parses and interprets basic Logo commands: `przod` (forward), `tył` (back), `lewo` (left), `prawo` (right), `if`, and user-defined procedures.
- Supports arithmetic operations (`<`, `>`, `=`) with numerical parameters and variables.
- Generates a BMP image file visualizing the turtle's movement on a 100x100 pixel grid.
- Handles recursive procedures, such as drawing a fractal pattern (e.g., a tree-like structure).


## Usage
The program accepts command-line arguments to configure its operation. You can run the interpreter by specifying the following parameters: 
- `-i` for the input file containing Logo language code (e.g., `-i input.txt`), 
- `-o` for the output file where the turtle's path will be saved (e.g., `-o output.txt`), 
- `-s` for the board size (e.g., `-s 100`).

For example, you can run the program like this:
```
logo-zlow.exe -i input.txt -o output.txt -s 100
```

## Example Input
Here’s a sample Logo script (`input.txt`) to draw a simple fractal tree:
```
krzaczek ( x, n )
  if ( n > 0 )
      przod ( x );
      lewo ( 45 );
      krzaczek( x * 0.75 , n-1);
      prawo ( 90 );
      krzaczek( x * 0.75, n-1);
      lewo ( 45 );
      tyl( x );
  end if;
end krzaczek;
  
krzaczek( 20 , 15 );
```
- `krzaczek` is a user-defined procedure that draws a tree-like fractal.
- The first parameter (20) specifies the initial segment length.
- The second parameter (3) specifies the recursion depth.

## Output
The interpreter generates a BMP image file (`output.bmp`) visualizing the turtle's movement. For the example above, it will create a tree-like pattern on a 100x100 pixel grid (or the size specified with the `-s` parameter).
