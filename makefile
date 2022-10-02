all: pos_falsa bisec

pos_falsa: expr.h pos_falsa.cpp
	g++ -o pos_falsa pos_falsa.cpp expr.h

bisec: expr.h bisec.cpp
	g++ -o bisec bisec.cpp expr.h

clear:
	rm bisec pos_falsa

