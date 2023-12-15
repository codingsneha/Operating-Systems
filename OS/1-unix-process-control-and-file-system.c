/*
1. Collect the following basic information about your machine using the /proc file system and
answer the following questions:
a. How many CPU and cores does the machine have?
b. What is the frequency of each CPU?
c. How much memory does your system have?
d. How much of it is free and available? What is the difference between them?
e. What is total number of user-level processes in the system?
f. How many context switches has the system performed since bootup?
2. Run all programs in the subdirectory memory and identify memory usage of each
program. What is the meaning of the parameters VmSize and VmRSS ? Compare the
memory usage of these programs in terms of VmSize & VmRSS and justify your results
based on code.
3. Run the executable subprocesses provided in the subdirectory subprocess and
provide your roll number as input argument. Find the number of sub processes created by
this program. Describe how you obtained the answer.
4. Run strace along with the binary program of empty.c given in subdirectory strace .
What do you think the output of strace indicates in this case? How many different system
call functions do you see?
Next, use strace along with another binary program of hello.c (which is in the same
directory).Compare the two strace outputs
a. Which part of the strace output is common, and which part has to do with the specific
program?
b. List all unique system calls along with input and output parameters and overall
functionality of each system call?
5. Run the executable openfiles in subdirectory files and list the files which are opened
by this program. Describe how you obtained the answer.
6. Find all the block devices on your system, their mount points and file systems present
on them. Describe how you obtained the answer.
Home Task
7. Create 5000 files starting from foo1.pdf to foo5000.pdf using script.sh given in the
subdirectory disk.
Run the programs disk1 and disk2 and identify the average disk utilization. Justify your
answer with the help of code. 
*/

1. Collect Basic System Information
a. To find the number of CPUs and cores, use:

bash
Copy code
cat /proc/cpuinfo | grep "processor" | wc -l
b. To find the frequency of each CPU, use:

bash
Copy code
cat /proc/cpuinfo | grep "MHz"
c. To find the total memory, use:

bash
Copy code
cat /proc/meminfo | grep "MemTotal"
d. To find free and available memory, use:

bash
Copy code
cat /proc/meminfo | grep "MemFree"
cat /proc/meminfo | grep "MemAvailable"
e. To find the total number of user-level processes, use:

bash
Copy code
ps aux | wc -l
f. To find the number of context switches, use:

bash
Copy code
cat /proc/stat | grep "ctxt"
2. Memory Usage
The VmSize represents the total virtual memory used by the process, while VmRSS represents the resident set size, i.e., the portion of the process's memory held in RAM.

3. Subprocesses
Run the provided executable with your roll number as an argument:

bash
Copy code
./subprocesses <roll_number>
To find the number of subprocesses, you can use:

bash
Copy code
ps --ppid=<pid_of_parent_process> | wc -l
4. Strace
Run strace with the binary program:

bash
Copy code
strace ./empty
Analyze the output for system call information. Repeat for hello.c. Compare the common and specific parts of the outputs.

5. Open Files
Run the executable and use lsof to list open files:

bash
Copy code
./openfiles
lsof -p <pid_of_openfiles_program>
6. Block Devices
Use lsblk to list block devices and their mount points:

bash
Copy code
lsblk
Home Task: Disk Utilization
Execute script.sh to create 5000 files:

bash
Copy code
./script.sh
Run disk1 and disk2 and measure disk utilization:

bash
Copy code
./disk1
./disk2

