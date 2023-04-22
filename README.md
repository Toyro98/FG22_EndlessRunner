# FG22_EndlessRunner
This project uses no BluePrints and they are only used as prefabs, the rest is made in cpp.

# How It Works
We first create x amount of empty platforms. When player touches a platform's trigger, the platform are moved further ahead and picks one random obstacle from an array of obstacles. 
The player moves at a constant speed and after a platform moves, the speed increases by a set amount. Touching an obstacle removes one live from player and if player has 0 lives left, it calls 2 functions to reset the platform manager and the player using the AActor's virtual Reset().

# Known issues in Part 1
- Holding down space to jump carries over the speed after a reset
- Pressing A then D then A repetelty makes the characther slow down

# Todo in Part 2
- Fix the issues in Part 1
- Add a score system
- Add UI showing your health and the score
- Add a main menu explaining the controls and a button to start
- Add a pause menu
