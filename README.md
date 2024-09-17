# Synchronized File Access with Lock File

## Overview

This project implements a synchronization mechanism for file access using a lock file, ensuring that multiple processes can write to the same file but only one at a time. This approach helps prevent data corruption and ensures the order of messages in a file as specified.

## Project Description

### Objective

The goal is to develop a robust method using a lock file (`lockfile.lock`) to control write access to a common file by multiple child processes spawned by a parent process. The parent process coordinates the execution and ensures all children complete their writing tasks in an orderly fashion.

### Implementation Details

- **Process Creation**: The program dynamically creates multiple child processes based on user input.
- **Writing Mechanism**: Each child process writes a specific message to a common file, ensuring exclusive access through a lock file.
- **Synchronization Approach**: Uses a lock file to manage access to the file, allowing only one process to write at a time.
- **User Interaction**: Accepts input parameters specifying the messages and the number of times each message is written.

### Key Functionalities

1. **Lock File Usage**:
   - A file named `lockfile.lock` is used as a mutex to control access to the main output file.
  
2. **Exclusive Writing**:
   - Child processes synchronize access to the output file using the lock file, checking for its existence and waiting if necessary.

3. **Orderly Execution**:
   - Ensures that writes to the file are done in a controlled manner, with the parent process managing the synchronization and termination of child processes.

4. **Command-Line Flexibility**:
   - The program allows users to specify the content and the frequency of writes via command-line arguments.

## Compilation and Execution

Compile the program using a C compiler such as GCC:

```bash
gcc -o file_access part2.c
Run the program with the necessary arguments:

bash
Copy code
./file_access "Message from process A" "Message from process B" "Message from process C" 10 > output2.txt
Example
This command will execute the child processes, each writing their respective messages 10 times to the output file output2.txt, managed by the lock file.

Error Handling
Includes error checking for system calls (fork, wait, unlink, open, etc.) and outputs errors using perror.

Contributions
Contributions to enhance the synchronization mechanism or to extend the functionality are welcome. Please fork the repository and submit a pull request with your updates.

License
This project is released under the MIT License.

Contact
For more details or queries about the project, please contact me at [your-email@example.com].
