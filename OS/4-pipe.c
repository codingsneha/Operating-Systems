/*
Implement using Pipe: Full duplex communication between parent and child
processes. Parent process writes a pathname of a file (the contents of the file are
desired) on one pipe to be read by child process and child process writes the contents
of the file on second pipe to be read by parent process and displays on standard
output. How to do it?
*/
#!/bin/bash

# Create two named pipes
pipe1="/tmp/pipe1"
pipe2="/tmp/pipe2"

mkfifo $pipe1
mkfifo $pipe2

# Function to be executed by the child process
child_process() {
    local file_path
    read file_path < $pipe1

    # Check if the file exists
    if [ -f "$file_path" ]; then
        cat "$file_path" > $pipe2
    else
        echo "File not found." > $pipe2
    fi
}

# Start the child process
child_process &

# Parent process
echo "Enter the path of the file:"
read file_path

# Write file path to the first pipe
echo $file_path > $pipe1

# Read the contents from the second pipe
read -r contents < $pipe2

# Display the contents
echo "Contents of the file:"
echo "$contents"

# Clean up - Close and remove pipes
exec 3>&-
exec 4>&-
rm $pipe1
rm $pipe2

/*
In this script:

The parent process creates two named pipes (pipe1 and pipe2) using mkfifo.
It spawns a child process that reads the file path from pipe1, checks if the file exists, and then writes the contents to pipe2.
The parent process takes user input for the file path, writes it to pipe1, and then reads the contents from pipe2.
The contents are then displayed on the standard output.
Please note that named pipes (FIFOs) are used for communication between processes, and they are represented as special files. Make sure to run this script in a shell environment that supports named pipes (most Unix-like systems do).
*/