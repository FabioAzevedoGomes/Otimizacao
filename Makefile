OBJ := obj/
INC := include/
SRC := src/
BIN := bin/
GLPK := glpk/

all:
	g++ -c ${SRC}Color.cpp              -I ${INC} -o ${OBJ}Color.o  -Wall -O3
	g++ -c ${SRC}Vertex.cpp             -I ${INC} -o ${OBJ}Vertex.o -Wall -O3
	g++ -c ${SRC}Edge.cpp               -I ${INC} -o ${OBJ}Edge.o   -Wall -O3
	g++ -c ${SRC}Graph.cpp              -I ${INC} -o ${OBJ}Graph.o  -Wall -O3
	g++ -c ${SRC}State.cpp              -I ${INC} -o ${OBJ}State.o  -Wall -O3
	g++ -c ${SRC}SimulatedAnnealing.cpp -I ${INC} -o ${OBJ}SimulatedAnnealing.o  -Wall -O3
	g++ -o ${BIN}app \
	           ${OBJ}Color.o\
	           ${OBJ}Vertex.o\
			   ${OBJ}Edge.o\
			   ${OBJ}Graph.o\
			   ${OBJ}State.o\
			   ${OBJ}SimulatedAnnealing.o\
	           -Wall -O3

test:
	cd bin && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./app 2 1 10 0.99 12 9999 $(in)
	gnuplot --persist plot.gnu

clean:
	rm ${BIN}* ${OBJ}* ${GLPK}data.dat