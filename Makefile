CXX = g++
CXXFLAGS = -c -Ihh -Icpp -Wall -pedantic -std=c++17 -g
OBJ = obj/main.o obj/wspolrzedne.o obj/figura.o obj/goniec.o\
	obj/hetman.o obj/krol.o obj/pionek.o obj/skoczek.o obj/wieza.o\
	obj/druzyna.o obj/plansza.o obj/szachy.o

__start__: szachy
	

szachy: obj obj/main.o $(OBJ)
	g++ -Wall -Werror -Wextra -pedantic -std=c++17 -o szachy.exe $(OBJ)
	./szachy.exe

obj: 
	mkdir obj

obj/main.o: src/main.cpp src/inc/szachy.hh
	$(CXX) ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/figura.o: src/figura.cpp src/inc/figura.hh src/inc/wspolrzedne.hh src/inc/mozliwosc.hh
	$(CXX) ${CXXFLAGS} -o obj/figura.o src/figura.cpp

obj/goniec.o: src/goniec.cpp src/inc/goniec.hh src/inc/figura.hh src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/goniec.o src/goniec.cpp

obj/hetman.o: src/hetman.cpp src/inc/hetman.hh src/inc/figura.hh src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/hetman.o src/hetman.cpp

obj/krol.o: src/krol.cpp src/inc/krol.hh src/inc/figura.hh src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/krol.o src/krol.cpp

obj/pionek.o: src/pionek.cpp src/inc/pionek.hh src/inc/figura.hh src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/pionek.o src/pionek.cpp

obj/skoczek.o: src/skoczek.cpp src/inc/skoczek.hh src/inc/figura.hh src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/skoczek.o src/skoczek.cpp

obj/wieza.o: src/wieza.cpp src/inc/wieza.hh src/inc/figura.hh src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/wieza.o src/wieza.cpp

obj/druzyna.o: src/druzyna.cpp src/inc/druzyna.hh src/inc/figura.hh src/inc/goniec.hh\
			src/inc/hetman.hh src/inc/krol.hh src/inc/pionek.hh src/inc/skoczek.hh\
			src/inc/wieza.hh
	$(CXX) ${CXXFLAGS} -o obj/druzyna.o src/druzyna.cpp

obj/plansza.o: src/plansza.cpp src/inc/plansza.hh src/inc/wspolrzedne.hh src/inc/figura.hh\
			src/inc/mozliwosc.hh src/inc/druzyna.hh src/inc/tablica_ruchow.hh src/inc/blokada_szacha.hh
	$(CXX) ${CXXFLAGS} -o obj/plansza.o src/plansza.cpp

obj/wspolrzedne.o: src/wspolrzedne.cpp src/inc/wspolrzedne.hh
	$(CXX) ${CXXFLAGS} -o obj/wspolrzedne.o src/wspolrzedne.cpp

obj/szachy.o: src/szachy.cpp src/inc/szachy.hh src/inc/plansza.hh
	$(CXX) ${CXXFLAGS} -o obj/szachy.o src/szachy.cpp

clean_linux:
	rm -f obj/*.o szachy.exe
clean_windows:
	del /f obj szachy.exe