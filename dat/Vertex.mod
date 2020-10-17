#
#                 Minimal Viable Vertex Coloring Problem:
#
# - Given a symmetrical graph G = (V,E) where
#    * V Is the set of vertexes
#    * E Is the set of edges
#
# - Minimize the number of colors k such that:
#    * Each vertex v in V has an assigned color
#    * No two vertexes u,v in V that share an edge have the same color
#

# Input parameters

# Set containing every vertex in the input graph, numbered 1 through N
set V;

# Adjacency matrix for input graph G
param graph {V, V};

# Big M
param M;

# Problem variables
var color {V} integer, >= 0; # Color given to node v
var decision {V,V} binary;   # Binary variable for modeling inequality

# Problem objective
minimize ColorSum:
	sum {v in V} color[v];

# Problem restrictions
subject to FullColoring {v in vertices}:
    color[v] > 0;

subject to SameColorConstraintUpper {u, v in vertices}: 
    color[u] - color[v]*graph[u,v] != 0 # FIXME