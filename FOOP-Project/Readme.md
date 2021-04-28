#  2 dimensional Cellulla Automata - Jupyter Notebooks
### Iteration1: Visualization of 3 generations on a square grid
Using mesh-grid coded with matplotlib and modifying properties of a scatterplot. Generations are shown as a scatter plot on the 2d game-board.
Using a python scipy.convolve2d library. New generation is a 'Convolution' with a rules signal to change state of neighbor cells.

### Iteration2: 2 dimensional Cellular Automata (Conway's Game of Life Rules)
2d Cellular Automata based on Conway's Game of Life Rules is starting fro the initial configuration; and for every generation when the rules are applied, the game-board evolves, playing the gae by itself!. We can see visualization of N generations on a square grid game-board. New generation is a 'Convolution' with signals of neighboring life and then the game-board is updated by applying Conway's rule for -
Survival/Stasis: A live cell continues to live from gen t to gen t+1, 
Death: Cell dies by overcrowding or exposure from gen t to gen t+1, and 
Birth: A cell that is dead in generation t will be alive for gen t+1.

### Iteration3: 2 dimensional Cellular Automata (Conway's Game of Life Rules and Intriguing Patterns)
Visualization of N generations on a square grid game-board. It is usually not easy to tell from looking at an initial configuration how exactly it will evolve. In this configuration we are looking at what happens to a straight line of live cells as a start configuration.
Many different types of patterns can be seen as the game-board evolves from gen1 to gen 16. 

# Functional and Object-oriented Programming -final Project
This final project produced a graphically interesting program (Conway’s Game of Life) using Java libraries. This project-based course introduced the foop paradigms including concepts such as functions, conditionals, data abstraction, recursion, lambda, higher-order functions, lists, loops, arrays, interfaces, inheritance, and polymorphism. The elements for Conway’s Game of Life included: 
- two-dimensional matrix of cells with possible states of 0 (meaning dead) and 1 (meaning alive)
- neighbor is an adjacent cell, and so a neighborhood is nine cells

