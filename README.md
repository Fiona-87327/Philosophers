The goal of this project is to simulate the classical Dining Philosophers problem using threads and mutexes.

Philosophers sit at a round table with a bowl of spaghetti.

They alternate between eating, thinking, and sleeping.

Philosophers need two forks (left and right) to eat.

Philosophers must not starve, and the simulation stops if a philosopher dies or all have eaten the required number of times.

Rules:

Each philosopher is represented as a separate thread.

There is one fork between each philosopher, protected by a mutex.

Philosophers do not communicate.

Philosophers must avoid dying from starvation.

Global variables are forbidden.
