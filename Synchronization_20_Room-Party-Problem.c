/*
One semester there was
a controversy over an allegation by a student that someone from the Dean of
Students Office had searched his room in his absence. Although the allegation
was public, the Dean of Students wasn’t able to comment on the case, so we
never found out what really happened. I wrote this problem to tease a friend
of mine, who was the Dean of Student Housing.
The following synchronization constraints apply to students and the Dean
of Students:
1. Any number of students can be in a room at the same time.
2. The Dean of Students can only enter a room if there are no students in
the room (to conduct a search) or if there are more than 50 students in
the room (to break up the party).
3. While the Dean of Students is in the room, no additional students may
enter, but students may leave.
4. The Dean of Students may not leave the room until all students have left.
5. There is only one Dean of Students, so you do not have to enforce exclusion
among multiple deans.
Puzzle: write synchronization code for students and for the Dean of Students
that enforces all of these constraints.
Room party hint
Room party hint
1 students = 0
2 dean = ’ not here ’
3 mutex = Semaphore (1)
4 turn = Semaphore (1)
5 clear = Semaphore (0)
6 lieIn = Semaphore (0)
students counts the number of students in the room, and dean is the state
of the Dean, which can also be “waiting” or “in the room”. mutex protects
students and dean, so this is yet another example of a scoreboard.
turn is a turnstile that keeps students from entering while the Dean is in
the room.
clear and lieIn are used as rendezvouses between a student and the Dean
(which is a whole other kind of scandal!).


Room party solution (dean)
1 mutex . wait ()
2 if students > 0 and students < 50:
3 dean = ’ waiting ’
4 mutex . signal ()
5 lieIn . wait () # and get mutex from the student .
6
7 # students must be 0 or >= 50
8
9 if students >= 50:
10 dean = ’in the room ’
11 breakup ()
12 turn . wait () # lock the turnstile
13 mutex . signal ()
14 clear . wait () # and get mutex from the student .
15 turn . signal () # unlock the turnstile
16
17 else : # students must be 0
18 search ()
19
20 dean = ’ not here ’
21 mutex . signal ()
When the Dean arrives, there are three cases: if there are students in the
room, but not 50 or more, the Dean has to wait. If there are 50 or more, the
Dean breaks up the party and waits for the students to leave. If there are no
students, the Dean searches and leaves.
In the first two cases, the Dean has to wait for a rendezvous with a student,
so he has to give up mutex to avoid a deadlock. When the Dean wakes up, he
has to modify the scoreboard, so he needs to get the mutex back. This is similar
to the situation we saw in the Sushi Bar problem. The solution I chose is the
“Pass the baton” pattern.

Room party solution (student)
1 mutex . wait ()
2 if dean == ’ in the room ’:
3 mutex . signal ()
4 turn . wait ()
5 turn . signal ()
6 mutex . wait ()
7
8 students += 1
9
10 if students == 50 and dean == ’ waiting ’:
11 lieIn . signal ()
# and pass mutex to the dean
12 else :
13 mutex . signal ()
14
15 party ()
16
17 mutex . wait ()
18 students -= 1
19
20 if students == 0 and dean == ’ waiting ’:
21 lieIn . signal () # and pass mutex to the dean
22 elif students == 0 and dean == ’in the room ’:
23 clear . signal () # and pass mutex to the dean
24 else :
25 mutex . signal ()
There are three cases where a student might have to signal the Dean. If
the Dean is waiting, then the 50th student in or the last one out has to signal
lieIn. If the Dean is in the room (waiting for all the students to leave), the last
student out signals clear. In all three cases, it is understood that the mutex
passes from the student to the Dean.
One part of this solution that may not be obvious is how we know at Line 7
of the Dean’s code that students must be 0 or not less than 50. The key is
to realize that there are only two ways to get to this point: either the first
conditional was false, which means that students is either 0 or not less than
50; or the Dean was waiting on lieIn when a student signaled, which means,
again, that students is either 0 or not less than 50.
*/