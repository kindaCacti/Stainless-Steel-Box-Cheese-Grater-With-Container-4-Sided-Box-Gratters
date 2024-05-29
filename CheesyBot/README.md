# functions to talk with the CheesyBot api
`getMove()`

# how does the bot works?
We use the so called minimax tree with alpha-beta pruning optimisation. 
To evaluate the position at each step we use piece-sqare tables. The default depth of the engine is 5 moves forward, but can be adjusted depending on the given difficulty of the engine.