# Final assignement for INF05010 - Otimização Combinatória, Universidade Federal do Rio Grande do Sul.
In this assignement we aim to formally model, as a Mixed Integer Programming problem, an *NP-Complete* problem in the **MathProg** language.

## The Problem
We have chosen to model and attempt to approximate solutions for the Vertex Coloring Problem, described below:

- Given a symmetrical graph $ G = (V,E)$ where
    * *V* Is the set of vertexes
    * *E* Is the set of edges

- Attribute colors to each vertex $v \in V$, such that 
    * $color(a) \neq color(b),\space\space \{\forall a,b \in V \space |\space \exists \space e(a,b) \in E\}$
    * $\exists \space color(v),\space\space \forall v \in V$

In the considered version of the problem, we would like to **minimize** the total amount of colors *K* needed for this coloring, such that both restrictions above are satisfied.

## The Approach
We have chosen to model this problem using the **MathProg** language, and further implement the **Simulated Annealing** algorithm in C++ to approximate the solution.

## Model

## Compiling / Running
