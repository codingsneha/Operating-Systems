/*
River Crossing
A particular river crossing is shared by both Linux hackers and Microsoft employees. 
A boat is used to cross the river, but it only seats four people, and must always carry a full load. 
In order to guarantee the safety of the hackers, you cannot put three employees and one hacker in the same boat; 
similarly, you cannot put three hackers in the same boat as an employee. 
To further complicate matters, there is room to board only one boat at a time; 
a boat must be taken across the river in order to start boarding the next boat. All other combination are safe. Two procedures are needed, HackerArrives and EmployeeArrives, called by a hacker or employee when he/she arrives at the river bank. The procedures arrange the arriving hackers and employees into safe boatloads. To get into a boat, a thread calls BoardBoat(); once the boat is full, one thread calls RowBoat(). RowBoat() does not return until the boat has left the dock.
Assume BoardBoat() and RowBoat() are already written. Implement HackerArrives() and EmployeeArrives(). 
These methods should not return until after RowBoat() has been called for the boatload. 
Any order is acceptable (again, don't worry about starvation), and there should be no busy-waiting 
and no undue waiting (hackers and employees should not wait if there are enough of them for a safe boatload).
*/

/*
River Crossing
Correctness constraints
People board the boat using BoardBoat() such that situations with 3 employees and 1 hacker, or vice versa, do not occur
When the boat is full, one of the people in it calls RowBoat()
Only one person can access the boat's state at a time
Hackers and employees outside the boat will wait to get in using condition variables waitingToBoardH and waitingToBoardE. People inside the boat will wait for the boat to leave using condition variable waitingToRow.
First, it will be necessary to know the number of hackers waiting to be assigned to a boat (int wH) and the number of employees waiting to be assigned to a boat (int wE). It will also be necessary to know the number of hackers that haven't yet boarded but have been assigned to a boat (int aH) and the number of such employees (int aE). Finally, the last person in the boat needs to row it, so it's necessary to know the number of people in the boat (int inBoat). All these variables are initialized to 0.
HackerArrives() {
  lock.acquire();

  wH++;

  // while not allowed to board
  while (aH == 0) {
    // if there's another hacker, and room for 2, allow 2 to board
    if (inBoat+aH+aE < 4 && wH >= 2) {
      wH-=2; aH+=2;
      waitingToBoardH.signal();
    }
    // else wait for somebody else to find a pair
    else {
      waitingToBoardH.wait();
    }
  }

  // board
  aH--;
  BoardBoat();
  inBoat++;

  // if the last person, wake everybody else up and leave
  if (inBoat == 4) {
    waitingToRow.broadcast();
    RowBoat();
    // new boat is empty, let everybody run for it
    inBoat = 0;
    waitingToBoardH.signal();
    waitingToBoardH.signal();
    waitingToBoardE.signal();
    waitingToBoardE.signal();
  }
  // else wait for last person
  else {
    waitingToRow.wait();
  }
 
  lock.release();
}

The code for EmployeeArrives() is completely symmetric.
*/

/*
Control Flow

a.       The pool of hackers and employees are waiting for the queue-check function to release the queue-lock so that they can enter the queue.

b.      When the queue-lock is released the hackers/employees take a random backoff� and enter in the queue. The lock of the queue is released for certain amount of time only.

c.       The queue-check function checks for safe-boat load at all times. When safe boat load is achieved, the queue-check function locks the queue and empties people from respective queue�s.

d.      One of person on the boat calls rowBoat function and returns back the control to queue-check function.

e.       If the queue-check function finds safe-boat load condition again, it keeps on locking the queue, and empties the queue unless the safe-boat load condition removed.

f.        If safe-boat-load condition does not exist it unlocks the queue for certain amount of time.

g.       After unlocking of queue�s, control of program passes to step b.
*/