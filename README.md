# NYCSubwaySystem
Created for Advanced Algorithms in C++ class at Polytechnic University, Fall 2000

The program uses the Bellman-Ford algorithm, a variant of Dijkstra's shortest path algorithm that uses negative weights, to determine the shortest path. A path was defined as the distance between any two stations. Set(s) of lines were associated with each station. For some stations, it was possible to transfer from one line to another, and from one side to the other.

The focus of the program was to determine, "How to get from Station A to Station B?" without any other extraneous information, such as time or day of the week. In the program, the data structure that was used was an adjacency list representation. This structure was chosen because it was convenient for subway stations that served multiple lines. The adjacency list was implemented by using STL techniques, such as containers, iterators, and genericity.

A highly technical and rigorous approach was taken to extract and manipulate the necessary information from the data files. Regarding user input, several functions were implemented to handle the operations on the strings.

A simple dialog was created for interaction with the user. The user has two options: (1) Find the shortets path between two stations, and (2) Exit. In the former, the user could enter his/her starting point and a destination. Upon entering this information, string manipulations were performed to determine the correct input, and this could be a prompt asked the user to verify this entry. If the answer was 'Yes', then the shortest path could be determined. Otherwise, the user had an option to either re-enter the information or exit the program.

In the creation of the program, several important aspects were covered. A facet that was covered was the situation where there were two stations with the same name where the lines at each location were listed, and the user was asked which line they preferred. The program handled another interesting feature, which was the concept of "equivalent" trains; that is, the trains stopped at the same stops and required transfers in the same places.
