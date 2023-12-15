/*
Old Bridge
An old bridge has only one lane 
and can only hold at most 3 cars 
at a time without risking collapse. 
Create a monitor with methods 
ArriveBridge(int direction) and 
ExitBridge() that controls traffic 
so that at any given time, there are at most 
3 cars on the bridge, and all of them are going 
the same direction. A car calls ArriveBridge when 
it arrives at the bridge and wants to go in the 
specified direction (0 or 1); ArriveBridge should 
not return until the car is allowed to get on the bridge.
 A car calls ExitBridge when it gets off the bridge,
  potentially allowing other cars to get on. 
  Don't worry about starving cars trying to go in 
  one direction; just make sure cars are always 
  on the bridge when they can be.
*/

/*
Old Bridge
Correctness constraints
At most 3 cars are on the bridge at a time
All cars on the bridge go in the same direction
Whenever the bridge is empty and a car is waiting, that car should get on the bridge
Whenever the bridge is not empty or full and a car is waiting to go the same direction as the cars on the bridge, that car should get on the bridge
Only one thread accesses shared state at a time
Cars will be waiting to get on the bridge, but in two directions. Use an array of two condition variables, waitingToGo[2].
It will be necessary to know the number of cars on the bridge (cars, initialized to 0), and the direction of these cars if there are any (call it currentdirection). It will also be useful to know the number of cars waiting to go in each direction; use an array waiters[2].
ArriveBridge(int direction) {
  lock.acquire();

  // while can't get on the bridge, wait
  while ((cars == 3) ||
         (cars > 0 && currentdirection != direction)) {
    waiters[direction]++;
    waitingToGo[direction].wait();
    waiters[direction]--;
  }

  // get on the bridge
  cars++;
  currentdirection = direction;

  lock.release();
}

ExitBridge() {
  lock.acquire();

  // get off the bridge
  cars--;

  // if anybody wants to go the same direction, wake them
  if (waiters[currentdirection] > 0)
    waitingToGo[currentdirection].signal();
  // else if empty, try to wake somebody going the other way
  else if (cars == 0)
    waitingToGo[1-currentdirection].broadcast();

  lock.release();
}
*/