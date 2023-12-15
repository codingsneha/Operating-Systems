/*
Suppose there are n passenger threads and a car thread. The
passengers repeatedly wait to take rides in the car, which can hold
C passengers, where C < n. The car can go around the tracks only
when it is full.
Here are some additional details:
• Passengers should invoke board and unboard.
• The car should invoke load, run and unload.
• Passengers cannot board until the car has invoked load
• The car cannot depart until C passengers have boarded.
• Passengers cannot unboard until the car has invoked unload.


Roller Coaster hint
1 mutex = Semaphore (1)
2 mutex2 = Semaphore (1)
3 boarders = 0
4 unboarders = 0
5 boardQueue = Semaphore (0)
6 unboardQueue = Semaphore (0)
7 allAboard = Semaphore (0)
8 allAshore = Semaphore (0)
mutex protects passengers, which counts the number of passengers that
have invoked boardCar.
Passengers wait on boardQueue before boarding and unboardQueue before
unboarding. allAboard indicates that the car is full.

Roller Coaster solution (car)
1 load ()
2 boardQueue . signal (C )
3 allAboard . wait ()
4
5 run ()
6
7 unload ()
8 unboardQueue . signal (C )
9 allAshore . wait ()
When the car arrives, it signals C passengers, then waits for the last one to
signal allAboard. After it departs, it allows C passengers to disembark, then
waits for allAshore.
Roller Coaster solution (passenger)
1 boardQueue . wait ()
2 board ()
3
4 mutex . wait ()
5 boarders += 1
6 if boarders == C :
7 allAboard . signal ()
8 boarders = 0
9 mutex . signal ()
10
11 unboardQueue . wait ()
12 unboard ()
13
14 mutex2 . wait ()
15 unboarders += 1
16 if unboarders == C :
17 allAshore . signal ()
18 unboarders = 0
19 mutex2 . signal ()
Passengers wait for the car before boarding, naturally, and wait for the car
to stop before leaving. The last passenger to board signals the car and resets
the passenger counter.



*/