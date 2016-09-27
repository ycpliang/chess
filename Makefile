CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = chess
OBJECTS = chess.o grid.o cell.o cpiece.o player.o knight.o rook.o bishop.o queen.o king.o pawn.o textdisplay.o window.o score.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}


clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
