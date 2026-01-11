Project Overview
The Philosophers project solves Edsger Dijkstra's classic Dining Philosophers synchronization problem. Philosophers sit around a table with forks (mutexes), alternating between thinking, eating (needing two forks), and sleeping, without deadlock or starvation. Use threads for philosophers and mutexes for forks; output timestamps for actions like "timestamp X has taken a fork" or "X died".
​

Build Instructions
Navigate to the project directory and compile with the Makefile:

text
make
