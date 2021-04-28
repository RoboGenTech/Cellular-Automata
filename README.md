# Cellular-Automata
  - John von Neumann: The Father of the Modern Computer is attributed to developing the cellular automata systems.
  - Illustrates the properties of complex systems at work.  
  - In two of my CS courses, I Investigated the program code for Cellular Automata

### 2d Cellular Automata : 
 I learned Conway's GameOfLife in the introductory Computer Science class called FOOP.
 Java with Swing program code exercises provided a good opportunity to practice skills with arrays, and object orientation in Java. 
 The project introduced with one of the exciting aspects of the Game of Life that there are initial patterns that yield intriguing results. 
 We were graded to showcase output for intriguing patterns. For example 
 - patterns such as block, beehive, loaf, and boat would remain a stable, finite, and non empty.
 - patterns that oscillate periodically such as blinker, toad, and beacon, have a Period 2.
 - patterns that repeats itself every nth generations such as glider(5-cell pattern occuring every 4th gen), and spaceship.
 
 However here, I am publishing a jupyter notebooks demonstrating the convolude2d scipy library to show my experientation with 2d cellular automata and Conway's Game of Life.
  
### One dimensional cellular automaton with Wolfram's elementary CA: 
 Simulate cellular automaton in C++ by defining the outcome for every possible neighborhood configuration as a series of 8 bits ruleset.
 The standard Wolfram model is to start generation 0 with all cells having a state of 0 except for the middle cell. 
 The ruleset is obtained as eight 0s and 1s is an 8-bit number with possible 256 combinations. For example binary sequence for 222 is 11011110. 
 Thus it is considered Rule 222.
 One of the interesting aspect of this lab was to study the Wolfram's classification after completing all modules of code:
 Class 1: Uniformity e.g. #222, Class 2: Repetition e.g. #190, Class 3: Random e.g. #30, Class 4: Complexity that have a mix of repetitive, oscillating patterns. e.g. #110. 
 
