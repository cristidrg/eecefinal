# main Makefile
main.o: main.cc Gamelogic.h ZedBoard.h Wiimote.h
	g++ -c main.cc

GameLogic.o: GameLogic.cc GameLogic.h Zedboard.h Wiimote.h
	g++ -c GameLogic.cc

ZedBoard.o: ZedBoard.cc ZedBoard.h
	g++ -c ZedBoard.cc

Wiimote.o: Wiimote.cc Wiimote.h
	g++ -c Wiimote.cc

clean:
	rm Wiimote.o ZedBoard.o GameLogic.o main.o