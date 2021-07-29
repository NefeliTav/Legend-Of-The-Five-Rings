all:  game.o DeckBuilder.o TypeConverter.o
	g++ -g -o game game.o DeckBuilder.o TypeConverter.o

game.o:  game.cpp Card.hpp DeckBuilder.hpp TypeConverter.hpp
	g++ -g -c game.cpp

DeckBuilder.o:  DeckBuilder.cpp DeckBuilder.hpp
	g++ -g -c DeckBuilder.cpp

TypeConverter.o:  TypeConverter.cpp TypeConverter.hpp
	g++ -g -c TypeConverter.cpp

clean: 
	rm -rf game *.o