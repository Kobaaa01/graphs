# graphs
Graphs project @ Politechnika Gdańska

Input:
In the first line there's a number k of graphs.
The following lines contain k graph data sets.
A single data set contains a number n - the graph order - and n lists of neighbours for each vertex. A list contains the number of neighbours (s) and s neighbours IDs.
Neighbours IDs are numbers from 1 to n.

Output (in next lines):
the degree sequence;
the number of components;
bipartiteness;
the eccentricity of vertices (within the components);
planarity (not done, prints '?');
vertices colours (consecutive natural numbers from 1) obtained using algorithms:
greedy (the vertex order according to its number);
LF method;
SLF method (not done, prints '?');
the number of different C4 subgraphs (not done, prints '?');
the number of the graph complement's edges

What is printed:
degree sequence, eccentricity, greedy, lf - sequence of numbers
bipartitness - T/F
the number of components, graph complement's edges - number
c4 subgraphs, planarity, SLF - '?'
