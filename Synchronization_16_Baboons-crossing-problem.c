/*
Baboon crossing
Description
In the baboon crossing problem, a number of baboons are located on the edges of a deep canyon. There are baboons on both sides and, as you have probably guessed, some of the baboons on the left side want to get to the right side, and vice versa. Fortunately, a large rope has been stretched across the abyss allowing baboons to cross by brachiation: hanging from the rope and swinging hand-over-hand to the other side.

The baboon crossing policy must be compatible with the constraints of the situation:

If two baboons meet in the middle of the rope, then all activity stops, and no other baboons can cross (deadlock). So, at any given time, all the baboons on the rope must be going the same direction.
The rope can hold only a certain number of baboons at a time. A baboon cannot be allowed on the rope if the rope is already at full capacity.
A continuous stream of baboons from one direction could prevent baboons wanting to go the opposite direction from ever being able to cross (unfairness, starvation).
Highlights
The rope is modeled in this example by class ROPE, and is the primary shared resource. The fact that, at any given moment, the rope is considered unavailable to baboons wanting to cross the canyon in the direction opposite the current flow of baboons adds an interesting twist ... as does the maximum limit of baboon flesh that the rope can support. The ROPE class has features to manage its state:

capacity is an integer representing the maximum number of baboons that can be supported at one time.
baboons is an integer which is the number of baboons currently traversing the rope.
direction is the current direction of baboon flow, represented as a boolean.
changing is an indicator of whether the direction of the rope is currently in the process of changing.
is_secure is a boolean indicating whether the rope is in such a state that a baboon may be allowed to mount the rope.
ROPE also includes procedures mount and dismount which a baboon uses to get on and off the rope.

There are two more interesting features of ROPE, directions and announce which will be discussed below.

The baboons (modeled by class BABOON), as they are created, are determined at random to want to go either left or right. As each baboon is created by the root class of the example, it is launched into life. For the purposes of this example, the baboon life is short and consists of four steps:

1) Announcing one's desired direction to the rope. Doing this involves the feature {ROPE}.announce that was mentioned above. The rope keeps a queue of these desired directions as announced by the baboons in its directions feature. It is by keeping this queue that the rope can make its decisions to change the direction of the flow of baboons. 
2) Mounting the rope. The baboon calls its own mount feature (which in turn calls {ROPE}.mount. The baboon's mount procedure includes two wait conditions. One makes sure the rope is safe ({ROPE}.is_secure), and the second make sure that the direction of the baboons is the same as that of the baboon wanting to mount. Whenever these conditions are met, the baboon is able to grab a spot on the rope and start to cross the canyon.
3) Traversing the canyon. Once on the rope, the baboon takes a short time to make it to the other side.
4) Dismounting the rope. After crossing the canyon, the baboon gets off the rope ... and dies immediately after attaining what was apparently its only goal in life.
Although it was mentioned above, it bears repeating that the rope is not just a shared resource, but an active and important player in this example. Indeed, it is the rope that controls the direction of the flow of baboons across the canyon, and ensures fairness.

When a baboon announces himself as a candidate for crossing the canyon in a particular direction, the rope queues this information. When the rope allows a baboon to mount and cross, the desired direction of the next baboon in the directions queue is queried. If the next baboon wants to go in a different direction, then the state of the rope is set to "changing", and no more baboons are allowed on the rope until the current stream finishes crossing. When the last baboon if that stream dismounts the rope, the direction of flow is changed and the "changing" state is repealed, allowing baboons wanting to cross in the opposite direction to have a go.
*/