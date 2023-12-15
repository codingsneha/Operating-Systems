/* Dining Hall problem
This problem was written by Jon Pollack during my Synchronization class at
Olin College.
Students in the dining hall invoke dine and then leave. After invoking dine
and before invoking leave a student is considered “ready to leave”.
The synchronization constraint that applies to students is that, in order to
maintain the illusion of social suave, a student may never sit at a table alone. A
student is considered to be sitting alone if everyone else who has invoked dine
invokes leave before she has finished dine.
Puzzle: write code that enforces this constraint.
 Dining Hall problem hint
Dining Hall problem hint
1 eating = 0
2 readyToLeave = 0
3 mutex = Semaphore (1)
4 okToLeave = Semaphore (0)
eating and readyToLeave are counters protected by mutex, so this is the
usual scoreboard pattern.
If a student is ready to leave, but another student would be left alone at the
table, she waits on okToLeave until another student changes the situation and
signals.

 Dining Hall problem solution
If you analyze the constraints, you will realize that there is only one situation
where a student has to wait, if there is one student eating and one student who
wants to leave. But there are two ways to get out of this situation: another
student might arrive to eat, or the dining student might finish.
In either case, the student who signals the waiting student updates the
counters, so the waiting student doesn’t have to get the mutex back. This
is another example of the the “I’ll do it for you” pattern.
Dining Hall problem solution
1 getFood ()
2
3 mutex . wait ()
4 eating ++
5 if eating == 2 and readyToLeave == 1:
6 okToLeave . signal ()
7 readyToLeave --
8 mutex . signal ()
9
10 dine ()
11
12 mutex . wait ()
13 eating --
14 readyToLeave ++
15
16 if eating == 1 and readyToLeave == 1:
17 mutex . signal ()
18 okToLeave . wait ()
19 elif eating == 0 and readyToLeave == 2:
20 okToLeave . signal ()
21 readyToLeave -= 2
22 mutex . signal ()
23 else :
24 readyToLeave --
25 mutex . signal ()
26
27 leave ()
When is student is checking in, if she sees one student eating and one waiting
to leave, she lets the waiter off the hook and decrements readyToLeave for him.

After dining, the student checks three cases:
• If there is only one student left eating, the departing student has to give
up the mutex and wait.
• If the departing student finds that someone is waiting for her, she signals
him and updates the counter for both of them.
• Otherwise, she just decrements readyToLeave and leaves.
7.6.3 Extended Dining Hall problem
The Dining Hall problem gets a little more challenging if we add another step.
As students come to lunch they invoke getFood, dine and then leave. After
invoking getFood and before invoking dine, a student is considered “ready to
eat”. Similarly, after invoking dine a student is considered “ready to leave”.
The same synchronization constraint applies: a student may never sit at a
table alone. A student is considered to be sitting alone if either
• She invokes dine while there is no one else at the table and no one ready
to eat, or
• everyone else who has invoked dine invokes leave before she has finished
dine.
Puzzle: write code that enforces these constraint
Extended Dining Hall problem hint
Here are the variables I used in my solution:
Extended Dining Hall problem hint
1 readyToEat = 0
2 eating = 0
3 readyToLeave = 0
4 mutex = Semaphore (1)
5 okToSit = Semaphore (0)
6 okToLeave = Semaphore (0)
readyToEat, eating and readyToLeave are counters, all protected by
mutex.
If a student is in a situation where she cannot proceed, she waits on okToSit
or okToLeave until another student changes the situation and signals.
I also used a per-thread variable named hasMutex to help keep track of
whether or not a thread holds the mutex


Extended Dining Hall problem solution
Again, if we analyze the constraints, we realize that there is only one situation
where a student who is ready to eat has to wait, if there is no one eating and
no one else ready to eat. And the only way out is if someone else arrives who is
ready to eat.
Extended Dining Hall problem solution
1 getFood ()
2
3 mutex . wait ()
4 readyToEat ++
5 if eating == 0 and readyToEat == 1:
6 mutex . signal ()
7 okToSit . wait ()
8 elif eating == 0 and readyToEat == 2:
9 okToSit . signal ()
10 readyToEat -= 2
11 eating += 2
12 mutex . signal ()
13 else :
14 readyToEat --
15 eating ++
16 if eating == 2 and readyToLeave == 1:
17 okToLeave . signal ()
18 readyToLeave --
19 mutex . signal ()
20
21 dine ()
22
23 mutex . wait ()
24 eating --
25 readyToLeave ++
26 if eating == 1 and readyToLeave == 1:
27 mutex . signal ()
28 okToLeave . wait ()
29 elif eating == 0 and readyToLeave == 2:
30 okToLeave . signal ()
31 readyToLeave -= 2
32 mutex . signal ()
33 else :
34 readyToLeave --
35 mutex . signal ()
36
37 leave ()

As in the previous solution, I used the “I’ll do it for you” pattern so that a
waiting student doesn’t have to get the mutex back.
The primary difference between this solution and the previous one is that
the first student who arrives at an empty table has to wait, and the second
student allows both students to proceed. It either case, we don’t have to check
for students waiting to leave, since no one can leave an empty table!
 */