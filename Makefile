OBJ := obj/
INC := include/
SRC := src/
BIN := bin/
GLPK := glpk/
INPUT := bin/CG/

all:
	g++ -c ${SRC}Color.cpp              -I ${INC} -o ${OBJ}Color.o  -Wall -O3
	g++ -c ${SRC}Vertex.cpp             -I ${INC} -o ${OBJ}Vertex.o -Wall -O3
	g++ -c ${SRC}Edge.cpp               -I ${INC} -o ${OBJ}Edge.o   -Wall -O3
	g++ -c ${SRC}Graph.cpp              -I ${INC} -o ${OBJ}Graph.o  -Wall -O3
	g++ -c ${SRC}State.cpp              -I ${INC} -o ${OBJ}State.o  -Wall -O3
	g++ -c ${SRC}SimulatedAnnealing.cpp -I ${INC} -o ${OBJ}SimulatedAnnealing.o  -Wall -O3
	g++ -o  ${BIN}app                      \
            ${OBJ}Color.o              \
            ${OBJ}Vertex.o             \
            ${OBJ}Edge.o               \
            ${OBJ}Graph.o              \
            ${OBJ}State.o              \
            ${OBJ}SimulatedAnnealing.o \
            -Wall -O3

test:
	cd bin && ./app 1 1 100 0.997 150 99999 $(in)
	gnuplot --persist plot.gnu

benchmark:				
	for file in $(INPUT)*; do                                 \
		for seed in 1 2 3 4 5 6 7 8 9 10; do                 \
			./${BIN}app $$seed 1 100 0.997 150 99999 $$file; \
		done                                                 \
	done 

clean:
	rm *.dat *.csv ${BIN}* ${OBJ}* ${GLPK}data.dat
