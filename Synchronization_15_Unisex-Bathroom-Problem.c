/*
when a friend of mine left her position teaching physics
at Colby College and took a job at Xerox.
She was working in a cubicle in the basement of a concrete monolith, and
the nearest women’s bathroom was two floors up. She proposed to the Uberboss
that they convert the men’s bathroom on her floor to a unisex bathroom, sort
of like on Ally McBeal.
The Uberboss agreed, provided that the following synchronization constraints can be maintained:
• There cannot be men and women in the bathroom at the same time.
• There should never be more than three employees squandering company
time in the bathroom.
Of course the solution should avoid deadlock. For now, though, don’t worry
about starvation. You may assume that the bathroom is equipped with all the
semaphores you need.

Here are the variables I used in my solution:
Unisex bathroom hint
1 empty = Semaphore (1)
2 maleSwitch = Lightswitch ()
3 femaleSwitch = Lightswitch ()
4 maleMultiplex = Semaphore (3)
5 femaleMultiplex = Semaphore (3)
empty is 1 if the room is empty and 0 otherwise.
maleSwitch allows men to bar women from the room. When the first male
enters, the lightswitch locks empty, barring women; When the last male exits, it unlocks empty, allowing women to enter. Women do likewise using
femaleSwitch.
maleMultiplex and femaleMultiplex ensure that there are no more than
three men and three women in the system at a time.

Here is the female code:
Unisex bathroom solution (female)
1 femaleSwitch . lock ( empty )
2 femaleMultiplex . wait ()
3 # bathroom code here
4 femaleMultiplex . signal ()
5 female Switch . unlock ( empty )
The male code is similar.

No-starve unisex bathroom solution
As we have seen before, we can use a turnstile to allow one kind of thread to
stop the flow of the other kind of thread. This time we’ll look at the male code:
No-starve unisex bathroom solution (male)
1 turnstile . wait ()
2 maleSwitch . lock ( empty )
3 turnstile . signal ()
4
5 maleMultiplex . wait ()
6 # bathroom code here
7 maleMultiplex . signal ()
8
9 maleSwitch . unlock ( empty )
As long as there are men in the room, new arrivals will pass through the
turnstile and enter. If there are women in the room when a male arrives, the
male will block inside the turnstile, which will bar all later arrivals (male and
female) from entering until the current occupants leave. At that point the male
in the turnstile enters, possibly allowing additional males to enter.
The female code is similar, so if there are men in the room an arriving female
will get stuck in the turnstile, barring additional men
*/