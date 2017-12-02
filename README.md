## Task
Implement an application which will do the following:

1. Application must accept one parameter from command line:
	1. N – number of elements to generate. It must be positive integer not larger than RAND_MAX (if this is not true – application must exit with error description).
2. Create a queue (FIFO – first in, first out) which will store positive integers.
3. One/first “producer” thread (you could create new or use main one) will be generating random numbers (value in the range between 1 – N) and will be adding/pushing these numbers to the queue. The size of the queue must not exceed some specified limit (i.e. limited by constant variable with default value 1000). It makes sense to pause generating of numbers if the queue is full (however it is up to you how to implement it).
4. Create a storage which will store N elements with following attributes:
	1. Number itself (positive integer)
	2. Number of microseconds it took to generate it (positive integer)
	3. Order by which the number was generated (it will be 1-N number).
5. Another/second “consumer” thread must do the following: 
	1. Read values from the queue (populated with “producer” thread) and check if this number/element already exists in the storage:
		- If yes – then simply discard this number.
		- If not – add new number/element to the storage. Calculate the time (the number of microseconds) which is the difference between current time and the time when previous number was added (i.e. how much time it took to find/add this new randomly generated number). Print (in console) the line with fixed length format which must contain all element attributes. Note: you could use/modify attached time_counter.h or do your own implementation.
6. Stop execution when all possible numbers in the range between 1 – N will be generated (i.e. every cell in the storage will be populated with correposnded number).
7. Calculate and print the average time it took to generate a number. Exit application.

## Implementation
The queue implementation supports several concurrent readers and writers. Implemented using atomic variables and does not use mutexes or other synchronization primitives.
Tested on Windows 10 using Visual Studio 2017 64bit toolchain.

Output example:
```
D:\dev\build\task\Release>task 10000
sequence:     1, value:     6, generated in:   949 microseconds
sequence:     2, value:    18, generated in:  2629 microseconds
sequence:     3, value:     7, generated in:   766 microseconds
sequence:     4, value:    71, generated in:   808 microseconds
sequence:     5, value:    22, generated in:   807 microseconds
sequence:     6, value:    23, generated in:  1332 microseconds
sequence:     7, value:    66, generated in:  1709 microseconds
sequence:     8, value:    39, generated in:   786 microseconds
sequence:     9, value:    51, generated in:  2452 microseconds
sequence:    10, value:    27, generated in:   786 microseconds
sequence:    11, value:    58, generated in:   743 microseconds
sequence:    12, value:    80, generated in:   800 microseconds
sequence:    13, value:    10, generated in:   789 microseconds
sequence:    14, value:    46, generated in:   745 microseconds
sequence:    15, value:    47, generated in:   745 microseconds
sequence:    16, value:    86, generated in:   743 microseconds
sequence:    17, value:     8, generated in:   813 microseconds
sequence:    18, value:    52, generated in:  1184 microseconds
sequence:    19, value:    89, generated in:  2762 microseconds
sequence:    20, value:    55, generated in:   794 microseconds
...
sequence:  6371, value:  8918, generated in:  2601 microseconds
sequence:  6372, value:  7258, generated in:   833 microseconds
sequence:  6373, value:  8193, generated in:   819 microseconds
sequence:  6374, value:   956, generated in:   799 microseconds
sequence:  6375, value:   902, generated in:   832 microseconds
sequence:  6376, value:  4108, generated in:   809 microseconds
sequence:  6377, value:  7790, generated in:  1253 microseconds
sequence:  6378, value:  8965, generated in:  1247 microseconds
sequence:  6379, value:  6964, generated in:   958 microseconds
sequence:  6380, value:  1023, generated in:  2877 microseconds
sequence:  6381, value:  4888, generated in:  1314 microseconds
sequence:  6382, value:  6228, generated in:  1268 microseconds
sequence:  6383, value:  3930, generated in:  1001 microseconds
sequence:  6384, value:  3581, generated in:   857 microseconds
average generation: 1314 microseconds
```