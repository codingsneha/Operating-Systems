/*
There are two kinds of threads, oxygen and hydrogen. In order to assemble
these threads into water molecules, we have to create a barrier that makes each
thread wait until a complete molecule is ready to proceed.
As each thread passes the barrier, it should invoke bond. You must guarantee
that all the threads from one molecule invoke bond before any of the threads
from the next molecule do.
In other words:
• If an oxygen thread arrives at the barrier when no hydrogen threads are
present, it has to wait for two hydrogen threads.
• If a hydrogen thread arrives at the barrier when no other threads are
present, it has to wait for an oxygen thread and another hydrogen thread.
We don’t have to worry about matching the threads up explicitly; that is,
the threads do not necessarily know which other threads they are paired up
with. The key is just that threads pass the barrier in complete sets; thus, if we
examine the sequence of threads that invoke bond and divide them into groups
of three, each group should contain one oxygen and two hydrogen threads.

Water building hint
1 mutex = Semaphore (1)
2 oxygen = 0
3 hydrogen = 0
4 barrier = Barrier (3)
5 oxyQueue = Semaphore (0)
6 hydroQueue = Semaphore (0)

 H2O solution
Initially hydroQueue and oxyQueue are locked. When an oxygen thread arrives
it signals hydroQueue twice, allowing two hydrogens to proceed. Then the
oxygen thread waits for the hydrogen threads to arrive.
Oxygen code
1 mutex . wait ()
2 oxygen += 1
3 if hydrogen >= 2:
4 hydroQueue . signal (2)
5 hydrogen -= 2
6 oxyQueue . signal ()
7 oxygen -= 1
8 else :
9 mutex . signal ()
10
11 oxyQueue . wait ()
12 bond ()
13
14 barrier . wait ()
15 mutex . signal ()
As each oxygen thread enters, it gets the mutex and checks the scoreboard.
If there are at least two hydrogen threads waiting, it signals two of them and
itself and then bonds. If not, it releases the mutex and waits.
After bonding, threads wait at the barrier until all three threads have
bonded, and then the oxygen thread releases the mutex. Since there is only
one oxygen thread in each set of three, we are guaranteed to signal mutex once.
The code for hydrogen is similar:
Hydrogen code
1 mutex . wait ()
2 hydrogen += 1
3 if hydrogen >= 2 and oxygen >= 1:
4 hydroQueue . signal (2)
5 hydrogen -= 2
6 oxyQueue . signal ()
7 oxygen -= 1
8 else :
9 mutex . signal ()
10
11 hydroQueue . wait ()
12 bond ()
13
14 barrier . wait ()

*/