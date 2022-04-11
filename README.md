# Hybrid informed search Q-Learning for solving Sokoban puzzles
### A* and RL-based Sokoban solvers 🥊

In this repository we present our hybrid Reinforcement Learning (RL) Sokoban solver with informed search subroutines. 
In the report, we introduce the game rules and we translate the solving logic into mathematical and algorithmic definitions to define our AI agent. 
We benchmark A* with our hybrid RL agent, we describe the core algorithm pseudo-codes, data structures and heuristics used in the solvers and provide the time and space complexity of the proposed methods.

### What is Sokoban?
In 1980, Sokoban was created. This Japanese single player game consists on an agent that has to push boxes around a grid and carry them to storage locations. Human beings can solve the levels in minutes, but it is not that easy to solve these puzzles with linear programming algorithms. This fact makes the game a good case of study for the Artificial Intelligence field.

### TL;DR
Solving sokoban puzzles is a NP-complete problem that requires a big computational effort. Simplifications of the problem, good heuristics, well-aimed hyperparameters and state pruning are crucial in order to get to a solution. Our approach has some flaws, and further work is needed in order to solve most of the problems, but in this project we have introduced a novel approach that combines both, reinforcement learning and informed search methods. 

We believe that a reinforcement learning approach that starts from the end of the problem (inverse exploration) combined with other Artificial Intelligence techniques, such as constraint satisfaction, heuristic search, local search or loop detection; has the potential to improve the current state of our solver.
