/* Max Hailperin wrote this problem for his textbook Operating Systems and Middleware [5]. At a child care center, state regulations require that there is always
one adult present for every three children.
Puzzle: Write code for child threads and adult threads that enforces this
constraint in a critical section.

Hailperin suggests that you can almost solve this problem with one semaphore.
Child care hint
1 multiplex = Semaphore (0)
multiplex counts the number of tokens available, where each token allows
a child thread to enter. As adults enter, they signal multiplex three times; as
they leave, they wait three times. But there is a problem with this solution.
Puzzle: what is the problem?

Child care solution
Adding a mutex solves the problem:
Child care solution (adult)
1 multiplex . signal (3)
2
3 # critical section
4
5 mutex . wait ()
6 multiplex . wait ()
7 multiplex . wait ()
8 multiplex . wait ()
9 mutex . signal ()
Now the three wait operations are atomic. If there are three tokens available,
the thread that gets the mutex will get all three tokens and exit. If there are
fewer tokens available, the first thread will block in the mutex and subsequent
threads will queue on the mutex.

One feature of this solution is that an adult thread waiting to leave can prevent
child threads from entering.
Imagine that there are 4 children and two adults, so the value of the multiplex
is 2. If one of the adults tries to leave, she will take two tokens and then block
waiting for the third. If a child thread arrives, it will wait even though it would
be legal to enter. From the point of view of the adult trying to leave, that might
be just fine, but if you are trying to maximize the utilization of the child care
center, it’s not.
Puzzle: write a solution to this problem that avoids unnecessary waiting.
Hint: think about the dancers in Section 3.8.

 Extended child care hint
Here are the variables I used in my solution:
Extended child care hint
1 children = adults = waiting = leaving = 0
2 mutex = Semaphore (1)
3 childQueue = Semaphore (0)
4 adultQueue = Semaphore (0)
children, adults, waiting and leaving keep track of the number of children, adults, children waiting to enter, and adults waiting to leave; they are
protected by mutex.
Children wait on childQueue to enter, if necessary. Adults wait on
adultQueue to leave.

This solution is more complicated than Hailperin’s elegant solution, but it is
mostly a combination of patterns we have seen before: a scoreboard, two queues,
and “I’ll do it for you”.
Here is the child code:
Extended child care solution (child)
1 mutex . wait ()
2 if children < 3 * adults :
3 children ++
4 mutex . signal ()
5 else :
6 waiting ++
7 mutex . signal ()
8 childQueue . wait ()
9
10 # critical section
11
12 mutex . wait ()
13 children --
14 if leaving and children <= 3 * ( adults -1):
15 leaving --
16 adults --
17 adultQueue . signal ()
18 mutex . signal ()
As children enter, they check whether there are enough adults and either (1)
increment children and enter or (2) increment waiting and block. When they
exit, they check for an adult thread waiting to leave and signal it if possible.


Here is the code for adults:
Extended child care solution (adult)
1 mutex . wait ()
2 adults ++
3 if waiting :
4 n = min (3 , waiting )
5 childQueue . signal (n)
6 waiting -= n
7 children += n
8 mutex . signal ()
9
10 # critical section
11
12 mutex . wait ()
13 if children <= 3 * ( adults -1):
14 adults --
15 mutex . signal ()
16 else :
17 leaving ++
18 mutex . signal ()
19 adultQueue . wait ()
As adults enter, they signal waiting children, if any. Before they leave, they
check whether there are enough adults left. If so, they decrement adults and
exit. Otherwise they increment leaving and block. While an adult thread
is waiting to leave, it counts as one of the adults in the critical section, so
additional children can enter.


 */