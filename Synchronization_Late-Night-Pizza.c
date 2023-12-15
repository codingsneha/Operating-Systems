/* Late-Night Pizza. A group of students are studying for a CPS 110 exam. The students can study only
while eating pizza. Each student executes the following loop: while (true) { pick up a piece of pizza;
study while eating the pizza}. If a student finds that the pizza is gone, the student goes to sleep until
another pizza arrives. The first student to discover that the group is out of pizza phones Satisfactions at
Brightleaf to order another pizza before going to sleep. Each pizza has S slices.
Write code to synchronize the student threads and the pizza delivery thread. Your solution should avoid
deadlock and phone Satisfactions (i.e., wake up the delivery thread) exactly once each time a pizza is */
