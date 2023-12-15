/*
Stand Claus sleeps in his shop at the North Pole and can only be
awakened by either (1) all nine reindeer being back from their vacation in the South Pacific, or (2) some of the elves having difficulty
making toys; to allow Santa to get some sleep, the elves can only
wake him when three of them have problems. When three elves are
having their problems solved, any other elves wishing to visit Santa
must wait for those elves to return. If Santa wakes up to find three
elves waiting at his shop’s door, along with the last reindeer having
come back from the tropics, Santa has decided that the elves can
wait until after Christmas, because it is more important to get his
sleigh ready. (It is assumed that the reindeer do not want to leave
the tropics, and therefore they stay there until the last possible moment.) The last reindeer to arrive must get Santa while the others
wait in a warming hut before being harnessed to the sleigh.
Here are some addition specifications:
• After the ninth reindeer arrives, Santa must invoke prepareSleigh, and
then all nine reindeer must invoke getHitched.
• After the third elf arrives, Santa must invoke helpElves. Concurrently,
all three elves should invoke getHelp.
• All three elves must invoke getHelp before any additional elves enter
(increment the elf counter).
Santa should run in a loop so he can help many sets of elves. We can assume
that there are exactly 9 reindeer, but there may be any number of elves.

Santa problem hint
1 elves = 0
2 reindeer = 0
3 santaSem = Semaphore (0)
4 reindeerSem = Semaphore (0)
5 elfTex = Semaphore (1)
6 mutex = Semaphore (1)
elves and reindeer are counters, both protected by mutex. Elves and
reindeer get mutex to modify the counters; Santa gets it to check them.
Santa waits on santaSem until either an elf or a reindeer signals him.
The reindeer wait on reindeerSem until Santa signals them to enter the
paddock and get hitched.
The elves use elfTex to prevent additional elves from entering while three
elves are being helped.


Santa problem solution (Santa)
1 santaSem . wait ()
2 mutex . wait ()
3 if reindeer >= 9:
4 prepareSleigh ()
5 reindeerSem . signal (9)
6 reindeer -= 9
7 else if elves == 3:
8 helpElves ()
9 mutex . signal ()
When Santa wakes up, he checks which of the two conditions holds and
either deals with the reindeer or the waiting elves. If there are nine reindeer
waiting, Santa invokes prepareSleigh, then signals reindeerSem nine times,
allowing the reindeer to invoke getHitched. If there are elves waiting, Santa
just invokes helpElves. There is no need for the elves to wait for Santa; once
they signal santaSem, they can invoke getHelp immediately.
Santa doesn’t have to decrement the elves counter because the elves do it
on their way out.
Here is the code for reindeer:
Santa problem solution (reindeer)
1 mutex . wait ()
2 reindeer += 1
3 if reindeer == 9:
4 santaSem . signal ()
5 mutex . signal ()
6
7 reindeerSem . wait ()
8 getHitched ()
The ninth reindeer signals Santa and then joins the other reindeer waiting
on reindeerSem. When Santa signals, the reindeer all execute getHitched.
The elf code is similar, except that when the third elf arrives it has to bar
subsequent arrivals until the first three have executed getHelp.

Santa problem solution (elves)
1 elfTex . wait ()
2 mutex . wait ()
3 elves += 1
4 if elves == 3:
5 santaSem . signal ()
6 else
7 elfTex . signal ()
8 mutex . signal ()
9
10 getHelp ()
11
12 mutex . wait ()
13 elves -= 1
14 if elves == 0:
15 elfTex . signal ()
16 mutex . signal ()
The first two elves release elfTex at the same time they release the mutex,
but the last elf holds elfTex, barring other elves from entering until all three
elves have invoked getHelp.
The last elf to leave releases elfTex, allowing the next batch of elves to
enter.
*/

