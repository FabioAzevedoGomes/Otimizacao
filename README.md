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

## Compiling / Running
To compile the program, simply run `make` on the root directory (Where `Makefile` is) and the binary will be generated in the `bin` sub-directory.
\
To run the program, either run 
```
make test in=<filename>
```
to use our pre-defined algorithm input values and generate the progression graph for the instance, containing the current state values and generated neighbor values for each iteration. (Requires the `gnuplot` tool)
\
If you would like to use specific values, change to `bin` directory and run
```
./app <seed> <temperature> <constant> <cooling-factor> <max-neighbors> <max-iterations> <input-file>

* Where:
seed           : Seed for the random number generator
temperature    : Initial temperature
constant       : Connstant K that multiplies temperature on Metripolis-Hastings probability formula
cooling-factor : Cooling factor r for reducing temperature 
max-neighbors  : Number of neighbors generated each iteration 
max-iterations : Max number of iterations for the algorithm
filename       : Input file containig the graph in .col format
```
to specify each input value.

## Output
In addition to running the Simulated Annealing algorithm and outputting iteration and best state information to `stdout`, the program will generate the following files in the same directory:
* `data.dat`: GPLK-Ready param file for the problem instance
* `log.dat`: Log file containing the value of current state for each iteration, for plotting the graph
* `neighbor.dat`: Log file containing the values of generated neighbors for each iteration, for plotting the graph