# Lab Assignment for CS 2B Intermediate Software Design in C++  

The elements of our system include
  - One dimensional grid or a line of cells.  
(Initiated with *(asterisks) in the centre of display for the output line).
  - A cell and its value (* or space characters) will be called its state
( a 2-state system so will be using binary 0 for space, and 1 for asterisk).
  - The cell itself and its two adjacent neighbors: one to the left and one to the right. We have three cells, each with a state of 0(space) or 1(asterisk). 
Possible ways to configure the states comes from three cells defined as a 3-bit number 
000 -> 0 001 -> 1 010 -> 2  011 -> 3 100 -> 4 101 -> 5 110 -> 6 111 ->7
  - Input to our program will be a number (0-255) and can be represented as an 8-bit binary number, which helps to set the rule to configure state for next gen.

# CPP Code file Automaton.cpp, and Output Run with Rule 131 and Rule 77)
# Conclusion 
Even with the simplest CA imaginable, we see the properties of complex systems at work. 
“The vast majority of elementary CA rulesets produce uninspiring results, while some result in wondrously
complex patterns like those found in nature”.(Serpienski’s triangle etc.)
