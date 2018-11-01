all : tp.x libplog.a 

tp.x : tp.o libplog.a
	g++ -std=gnu++11 -I. -o tp.x tp.o -L. -lplog

libplog.a : plog.o 
	ranlib libplog.a
	ar t libplog.a

tp.o : tp.cpp
	g++ -std=gnu++11 -DUNICODE -I. -c tp.cpp

plog.o : plog.cpp plog.h
	g++ -std=gnu++11 -I. -c plog.cpp
	ar r libplog.a plog.o

clean :
	rm -f tp.x libplog.a tp.o plog.o
