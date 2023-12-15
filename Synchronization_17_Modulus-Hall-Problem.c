/*
After a particularly heavy snowfall this winter, the denizens of
Modus Hall created a trench-like path between their cardboard shantytown and the rest of campus. Every day some of the residents walk
to and from class, food and civilization via the path; we will ignore
the indolent students who chose daily to drive to Tier 3. We will also
ignore the direction in which pedestrians are traveling. For some unknown reason, students living in West Hall would occasionally find
it necessary to venture to the Mods.
Unfortunately, the path is not wide enough to allow two people to
walk side-by-side. If two Mods persons meet at some point on the
path, one will gladly step aside into the neck high drift to accommodate the other. A similar situation will occur if two ResHall
inhabitants cross paths. If a Mods heathen and a ResHall prude
meet, however, a violent skirmish will ensue with the victors determined solely by strength of numbers; that is, the faction with the
larger population will force the other to wait.


Modus Hall problem hint
Here are the variables I used in my solution.
Modus problem hint
1 heathens = 0
2 prudes = 0
3 status = ’ neutral ’
4 mutex = Semaphore (1)
5 heathenTurn = Semaphore (1)
6 prudeTurn = Semaphore (1)
7 heathenQueue = Semaphore (0)
8 prudeQueue = Semaphore (0)
heathens and prudes are counters, and status records the status of the
field, which can be ‘neutral’, ‘heathens rule’, ‘prudes rule’, ‘transition to heathens’ or ‘transition to prudes’. All three are protected by mutex in the usual
scoreboard pattern.
heathenTurn and prudeTurn control access to the field so that we can bar
one side or the other during a transition.
heathenQueue and prudeQueue are where threads wait after checking in and
before taking the field.

Here is the code for heathens:
Modus problem solution
1 heathenTurn . wait ()
2 heathenTurn . signal ()
3
4 mutex . wait ()
5 heathens ++
6
7 if status == ’ neutral ’:
8 status = ’ heathens rule ’
9 mutex . signal ()
10 elif status == ’ prudes rule ’:
11 if heathens > prudes :
12 status = ’ transition to heathens ’
13 prudeTurn . wait ()
14 mutex . signal ()
15 heathenQueue . wait ()
16 elif status == ’ transition to heathens ’:
17 mutex . signal ()
18 heathenQueue . wait ()
19 else
20 mutex . signal ()
21
22 # cross the field
23
24 mutex . wait ()
25 heathens --
26
27 if heathens == 0:
28 if status == ’ transition to prudes ’:
29 prudeTurn . signal ()
30 if prudes :
31 prudeQueue . signal ( prudes )
32 status = ’ prudes rule ’
33 else :
34 status = ’ neutral ’
35
36 if status == ’ heathens rule ’:
37 if prudes > heathens :
38 status = ’ transition to prudes ’
39 heathenTurn . wait ()
40
41 mutex . signal ()

As each student checks in, he has to consider the following cases:
• If the field is empty, the student lays claim for the heathens.
• If the heathens currently in charge, but the new arrival has tipped the
balance, he locks the prude turnstile and the system switches to transition
mode.
• If the prudes in charge, but the new arrival doesn’t tip the balance, he
joins the queue.
• If the system is transitioning to heathen control, the new arrival joins the
queue.
• Otherwise we conclude that either the heathens are in charge, or the system is transitioning to prude control. In either case, this thread can
proceed.
Similarly, as each student checks out, she has to consider several cases.
• If she is the last heathen to check out, she has to consider the following:
– If the system is in transition, that means that the prude turnstile is
locked, so she has to open it.
– If there are prudes waiting, she signals them and updates status so
the prudes are in charge. If not, the new status is ’neutral’.
• If she is not the last heathen to check out, she still has to check the
possibility that her departure will tip the balance. In that case, she closes
the heathen turnstile and starts the transition.
*/