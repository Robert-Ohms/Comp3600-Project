u6669461

The project contains three executable files, each of which utilises one of the functionalities.
Interfacing with the executables is performed through the command line, and with specific arguments
and formats for each executable.

--------------------------------------------------------------------------------------------------------

analyse.exe
This executable provides convex hull functionality. It takes exactly one argument which is a text file
containing a set of coordinate pairs, with one pair per line, space separated pairs, and with
the x coordinate as the first of each pair. The file must also contain the number of pairs in the
first line.

Using the executable from command line on windows is done as:
.\analyse.exe file_name
where file_name is the name of the file being processed
files for this functionality are f1

To compile the executable on windows, use:
g++ -o analyse date.cpp matrix.cpp case.cpp analyse.cpp    
--------------------------------------------------------------------------------------------------------

queue.exe
This executable provides the heap functionality. It allows the user to create a heap, insert into it,
and extract elements one at a time. The argument file is a list of heap elements in non-specific order.
The first line is the number of elements, and each successive line contains a space separated priority,
key, and date.
The executable acts in two parts. The first is to call the executable with an input file. Once done,
the user can interact with the heap by calling any of insert, extract, or rebuild one at a time. Once
finished, the user enters q to terminate.

Using the executable from command line on windows is done as:
Setup:
.\queue.exe file_name
where file_name is the name of the file being processed
files for this functionality are f2

Insert:
i priority key date
i is a literal and must be typed exactly as shown (upper case will not work). 
priority is an integer
key is a string
date is a string of format dd/mm/yyyy and must be typed in exactly this format (any value with
fewer than the required number of digits must have leading 0s to conform to this format)

Extract:
e
e is a literal, and must be typed exactly as shown (upper case will not work).
Note: using extract when the heap is empty will cause the program to terminate with an error.

Rebuild:
r date
r is a literal, and must be typed exactly as shown (upper case will not work). 
date is a string of format dd/mm/yyyy where all elements with dates earlier than the input 
are removed

Ending:
q
q is a literal, and must be typed exactly as shown (upper case will not work). 


To compile the executable on windows, use:
g++ -o queue heap.cpp date.cpp info.cpp active_queue.cpp

--------------------------------------------------------------------------------------------------------

records.exe
This executable provides the hash functionality. It allows the user to insert, remove, and search for
elements in the table. The input file is a list of table elements with no order. The first line is
the number of elements. From here, elements are defined one by one where the first line contains the key,
amount, number of steps, start date, end date, and number of points. Each successive line contains a
coordinate pair.
The executable acts in two parts. The first is to call the executable with an input file. Once done,
the user can interact with the hash table by calling any of insert, remove, or search one at a time. Once
finished, the user enters q to terminate.

Using the executable from command line on windows is done as:
Setup:
.\records.exe file_name
where file_name is the name of the file being processed
files for this functionality are f3

Insert:
i file_name key
i is a literal and must be typed exactly as shown (upper case will not work).
file_name is the file containing the data for the case being inserted. The format of this file is the
same as the format for cases used in analyse.exe (test-f1)
key is the string key of the element being inserted

Remove:
r key
i is a literal and must be typed exactly as shown (upper case will not work).
key is the string key of the element being removed

Get:
g key
g is a literal and must be typed exactly as shown (upper case will not work).
key is the string key of the element being searched for

Ending:
q
q is a literal, and must be typed exactly as shown (upper case will not work). 

To compile the executable on windows, use:
g++ -o records date.cpp matrix.cpp hash_table.cpp case.cpp records.cpp   