#
#                 Minimal Viable Vertex Coloring Problem:
#
# - Given a symmetrical graph G = (V,E) where
#    * V Is the set of vertexes
#    * E Is the set of edges
#
# - Minimize the number of colors k such that:
#    * Each vertex v in V has an assigned color 
#    * Each vertex v in V has ONLY one color
#    * No two vertexes u,v in V that share an edge have the same color
#

# Input parameters

set V; # Set containing every vertex in the input graph, numbered 1 through N
set C; # Set containing every color possible to be used in the solution, numbered 1 through M

# Adjacency matrix for input graph G
param graph {V, V};

# Variables
var vertex_has_color {V, C} binary; # If vertex v has color c
var color_is_used {C} binary;       # If color c is used

# Objective
minimize Colors:
    sum{ c in C } color_is_used[c];

# Restrictions
subject to OneColorLower { v in V }:          # Each node can only have 1 assigned color
    sum {c in C} vertex_has_color[v, c] <= 1;

subject to OneColorUpper { v in V }:          # Each node can only have 1 assigned color
    sum {c in C} vertex_has_color[v, c] >= 1; 

subject to SameColorRestriction { u, v in V , c in C }: # No 2 nodes can have the same color
    (graph[u,v]) * (vertex_has_color[u, c] + vertex_has_color[v, c]) <= 1
