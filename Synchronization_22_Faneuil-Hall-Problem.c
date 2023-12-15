/*
This problem was written by Grant Hutchins, who was inspired by a friend who
took her Oath of Citizenship at Faneuil Hall in Boston.
“There are three kinds of threads: immigrants, spectators, and a one judge.
Immigrants must wait in line, check in, and then sit down. At some point, the
judge enters the building. When the judge is in the building, no one may enter,
and the immigrants may not leave. Spectators may leave. Once all immigrants
check in, the judge can confirm the naturalization. After the confirmation, the
immigrants pick up their certificates of U.S. Citizenship. The judge leaves at
some point after the confirmation. Spectators may now enter as before. After
immigrants get their certificates, they may leave.”
To make these requirements more specific, let’s give the threads some functions to execute, and put constraints on those functions.
• Immigrants must invoke enter, checkIn, sitDown, swear,
getCertificate and leave.
• The judge invokes enter, confirm and leave.
• Spectators invoke enter, spectate and leave.
• While the judge is in the building, no one may enter and immigrants may
not leave.
• The judge can not confirm until all immigrants who have invoked enter
have also invoked checkIn.
• Immigrants can not getCertificate until the judge has executed
confirm.


Faneuil Hall Problem Hint
Faneuil Hall problem hint
1 noJudge = Semaphore (1)
2 entered = 0
3 checked = 0
4 mutex = Semaphore (1)
5 confirmed = Semaphore (0)
noJudge acts as a turnstile for incoming immigrants and spectators; it also
protects entered, which counts the number of immigrants in the room. checked
counts the number of immigrants who have checked in; it is protected by mutex.
confirmed signals that the judge has executed confirm.

 Faneuil Hall problem solution
Here is the code for immigrants:
Faneuil Hall problem solution (immigrant)
1 noJudge . wait ()
2 enter ()
3 entered ++
4 noJudge . signal ()
5
6 mutex . wait ()
7 checkIn ()
8 checked ++
9
10 if judge = 1 and entered == checked :
11 allSignedIn . signal ()
# and pass the mutex
12 else :
13 mutex . signal ()
14
15 sitDown ()
16 confirmed . wait ()
17
18 swear ()
19 getCertificate ()
20
21 noJudge . wait ()
22 leave ()
23 noJudge . signal ()
Immigrants pass through a turnstile when they enter; while the judge is in
the room, the turnstile is locked.
After entering, immigrants have to get mutex to check in and update
checked. If there is a judge waiting, the last immigrant to check in signals
allSignedIn and passes the mutex to the judge.
Here is the code for the judge:
Faneuil Hall problem solution (judge)

noJudge . wait ()
2 mutex . wait ()
3
4 enter ()
5 judge = 1
6
7 if entered > checked :
8 mutex . signal ()
9 allSignedIn . wait ()
# and get the mutex back .
10
11 confirm ()
12 confirmed . signal ( checked )
13 entered = checked = 0
14
15 leave ()
16 judge = 0
17
18 mutex . signal ()
19 noJudge . signal ()
and mutex so he can access entered and checked.
If the judge arrives at an instant when everyone who has entered has also
checked in, she can proceed immediately. Otherwise, she has to give up the
mutex and wait. When the last immigrant checks in and signals allSignedIn,
it is understood that the judge will get the mutex back.
After invoking confirm, the judge signals confirmed once for every immigrant who has checked in, and then resets the counters (an example of “I’ll do
it for you”). Then the judge leaves and releases mutex and noJudge.
After the judge signals confirmed, immigrants invoke swear and
getCertificate concurrently, and then wait for the noJudge turnstile to open
before leaving.
The code for spectators is easy; the only constraint they have to obey is the
noJudge turnstile.
Faneuil Hall problem solution (spectator)
1 noJudge . wait ()
2 enter ()
3 noJudge . signal ()
4
5 spectate ()
6
7 leave ()
Note: in this solution it is possible for immigrants to get stuck, after they
get their certificate, by another judge coming to swear in the next batch of
immigrants. If that happens, they might have to wait through another swearing
in-ceremony.
Puzzle: modify this solution to handle the additional constraint that after
the judge leaves, all immigrants who have been sworn in must leave before the
judge can enter again.

*/