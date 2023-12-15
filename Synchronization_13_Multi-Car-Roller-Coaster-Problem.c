/*
• Only one car can be boarding at a time.
• Multiple cars can be on the track concurrently.
• Since cars can’t pass each other, they have to unload in the same order
they boarded.
• All the threads from one carload must disembark before any of the threads
from subsequent carloads.
Puzzle: modify the previous solution to handle the additional constraints.
You can assume that there are m cars, and that each car has a local variable
named i that contains an identifier between 0 and m − 1.
I used two lists of semaphores to keep the cars in order. One represents the
loading area and one represents the unloading area. Each list contains one
semaphore for each car. At any time, only one semaphore in each list is unlocked,
so that enforces the order threads can load and unload. Initially, only the
semaphores for Car 0 are unlocked. As each car enters the loading (or unloading)
it waits on its own semaphore; as it leaves it signals the next car in line.
Multi-car Roller Coaster hint
1 loadingArea = [ Semaphore (0) for i in range (m )]
2 loadingArea [1]. signal ()
3 unloadingArea = [ Semaphore (0) for i in range ( m )]
4 unloadingArea [1]. signal ()
The function next computes the identifier of the next car in the sequence
(wrapping around from m − 1 to 0):
Implementation of next
1 def next (i ):
2 return (i + 1) % m
Multi-car Roller Coaster solution (car)
1 loadingArea [i ]. wait ()
2 load ()
3 boardQueue . signal (C )
4 allAboard . wait ()
5 loadingArea [ next (i )]. signal ()
6
7 run ()
8
9 unloadingArea [ i ]. wait ()
10 unload ()
11 unboardQueue . signal (C )
12 allAshore . wait ()
13 unloadingArea [ next ( i )]. signal ()
The code for the passengers is unchanged.
*/