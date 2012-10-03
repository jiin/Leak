GRIDSOURCE = src/core/grid.cpp
PLAYERSOURCE = src/core/player.cpp
GUISOURCE = src/gui/gui.cpp $(GRIDSOURCE) $(PLAYERSOURCE)
CC = g++

all:
	$(CC) -L./SFML/lib -I./SFML/include $(GRIDSOURCE) -o test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC

gui:
	$(CC) -L./SFML/lib -L./libs -L./Lua -I./SFML/include -I./boost -I./Lua $(GUISOURCE) -o SFML/test.exe -lsfml-graphics -lsfml-window -lsfml-system -lboost_thread -lboost_system -llua52 -DSFML_STATIC -g

asd:
	$(CC) -L./SFML/lib -I./SFML/include asd.cpp -o SFML/test.exe -lsfml-graphics -lsfml-window -lsfml-system -DSFML_STATIC

startg:
	./SFML/test
