Shared Library One way messaging system
This is the README file 




1-CONTENTS OF THE PACKAGE
----------
reader.cpp	- source code for reader application
writer.cpp	- source code for writer application
sharedlib.c  - Shared library for messaging system
Makefile - Build system
README	- this file

----------

2-SYSTEM REQUIREMENTS:
-------------------
Linux
Gcc
------------------


3-CODE COMPILATION and EXECUTION:
------------------

1. Open a terminal and run the "make clean" and then "make all" command to compile the libary and source files.
2. Run the following command : "export LD_LIBRARY_PATH=." on the two terminals where you will run the reader and writer applications
3. Run "./reader" on one terminal
4. Run "./writer" on another terminal
5. Write data into the shared memory using "writer" application, and read data from the "reader" application by using appropriate commands as on the terminal.





Author: Sumanth Murali