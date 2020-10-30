OBJ := obj/
INC := include/
SRC := src/
BIN := bin/

all: dirs SimulatedAnnealing State
	g++ -c ${SRC}driver.cpp -I${INC} -o ${OBJ}driver.o -Wall -O3
	g++ -o ${BIN}app ${OBJ}driver.o ${OBJ}SimulatedAnnealing.o ${OBJ}State.o ${OBJ}Vertex.o ${OBJ}Color.o -Wall -O3

SimulatedAnnealing: 
	g++ -c ${SRC}SimulatedAnnealing.cpp -I${INC} -o ${OBJ}SimulatedAnnealing.o -Wall -O3

State: Vertex Color
	g++ -c ${SRC}State.cpp -I${INC} -o ${OBJ}State.o -Wall -O3

Vertex:
	g++ -c ${SRC}Vertex.cpp -I${INC} -o ${OBJ}Vertex.o -Wall -O3

Color:
	g++ -c ${SRC}Color.cpp -I${INC} -o ${OBJ}Color.o -Wall -O3

dirs:
	mkdir -p ${OBJ}
	mkdir -p ${BIN}

test:
	cd bin && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./app 1 1 1 0.8 "../dat/CG/queen16_16.col"

clean:
	rm ${OBJ}*.o ${BIN}app ${BIN}log.txt dat/data.dat