OBJ := obj/
INC := include/
SRC := src/
BIN := bin/

all: dirs SimulatedAnnealing State
	g++ -c ${SRC}driver.cpp -I${INC} -o ${OBJ}driver.o -Wall
	g++ -o ${BIN}app ${OBJ}driver.o ${OBJ}SimulatedAnnealing.o ${OBJ}State.o -Wall

SimulatedAnnealing: 
	g++ -c ${SRC}SimulatedAnnealing.cpp -I${INC} -o ${OBJ}SimulatedAnnealing.o -Wall

State:
	g++ -c ${SRC}State.cpp -I${INC} -o ${OBJ}State.o -Wall

dirs:
	mkdir -p ${OBJ}
	mkdir -p ${BIN}

test:
	cd bin && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./app 1 10 1 0.5 "../dat/CG/2-FullIns_4.col"

clean:
	rm ${OBJ}*.o ${BIN}app ${BIN}log.txt dat/data.dat