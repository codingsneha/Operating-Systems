/*
This problem was inspired by a problem proposed by Kenneth Reek [9]. Imagine
a sushi bar with 5 seats. If you arrive while there is an empty seat, you can take
a seat immediately. But if you arrive when all 5 seats are full, that means that
all of them are dining together, and you will have to wait for the entire party
to leave before you sit down.
Puzzle: write code for customers entering and leaving the sushi bar that
enforces these requirements.

Here are the variables I used:
Sushi bar hint
1 eating = waiting = 0
2 mutex = Semaphore (1)
3 block = Semaphore (0)
4 must_wait = False
eating and waiting keep track of the number of threads sitting at the bar
and waiting. mutex protects both counters. must wait indicates that the bar is
(or has been) full, som incoming customers have to block on block.

The only reason a waiting customer has to reacquire the mutex is to update the
state of eating and waiting, so one way to solve the problem is to make the
departing customer, who already has the mutex, do the updating.
Sushi bar solution #1
1 mutex . wait ()
2 if must_wait :
3 waiting += 1
4 mutex . signal ()
5 block . wait ()
6 else :
7 eating += 1
8 must_wait = ( eating == 5)
9 mutex . signal ()
10
11 # eat sushi
12
13 mutex . wait ()
14 eating -= 1
15 if eating == 0:
16 n = min (5 , waiting )
17 waiting -= n
18 eating += n
19 must_wait = ( eating == 5)
20 block . signal (n)
21 mutex . signal ()
When the last departing customer releases the mutex, eating has already
been updated, so newly arriving customers see the right state and block if
necessary. Reek calls this pattern “I’ll do it for you,” because the departing
thread is doing work that seems, logically, to belong to the waiting threads.
A drawback of this approach is that is it a little more difficult to confirm
that the state is being updated correctly
*/