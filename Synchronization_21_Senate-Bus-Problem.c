/*
This problem was originally based on the Senate bus at Wellesley College. Riders
come to a bus stop and wait for a bus. When the bus arrives, all the waiting
riders invoke boardBus, but anyone who arrives while the bus is boarding has
to wait for the next bus. The capacity of the bus is 50 people; if there are more
than 50 people waiting, some will have to wait for the next bus.
When all the waiting riders have boarded, the bus can invoke depart. If the
bus arrives when there are no riders, it should depart immediately.
Puzzle: Write synchronization code that enforces all of these constraints.


Bus problem hint
Here are the variables I used in my solution:
Bus problem hint
1 riders = 0
2 mutex = Semaphore (1)
3 multiplex = Semaphore (50)
4 bus = Semaphore (0)
5 allAboard = Semaphore (0)
mutex protects riders, which keeps track of how many riders are waiting;
multiplex makes sure there are no more than 50 riders in the boarding area.
Riders wait on bus, which gets signaled when the bus arrives. The bus waits
on allAboard, which gets signaled by the last student to board.

 Bus problem solution #1
Here is the code for the bus. Again, we are using the “Pass the baton” pattern.
Bus problem solution (bus)
1 mutex . wait ()
2 if riders > 0:
3 bus . signal () # and pass the mutex
4 allAboard . wait () # and get the mutex back
5 mutex . signal ()
6
7 depart ()
When the bus arrives, it gets mutex, which prevents late arrivals from entering the boarding area. If there are no riders, it departs immediately. Otherwise,
it signals bus and waits for the riders to board.
Here is the code for the riders:
Bus problem solution (riders)
1 multiplex . wait ()
2 mutex . wait ()
3 riders += 1
4 mutex . signal ()
5
6 bus . wait () # and get the mutex
7 multiplex . signal ()
8
9 boardBus ()
10
11 riders -= 1
12 if riders == 0:
13 allAboard . signal ()
14 else :
15 bus . signal () # and pass the mutex
The multiplex controls the number of riders in the waiting area, although
strictly speaking, a rider doesn’t enter the waiting area until she increments
riders.
Riders wait on bus until the bus arrives. When a rider wakes up, it is
understood that she has the mutex. After boarding, each rider decrements
riders. If there are more riders waiting, the boarding rider signals bus and
pass the mutex to the next rider. The last rider signals allAboard and passes
the mutex back to the bus.
Finally, the bus releases the mutex and departs.
Puzzle: can you find a solution to this problem using the “I’ll do it for you”
pattern?
*/