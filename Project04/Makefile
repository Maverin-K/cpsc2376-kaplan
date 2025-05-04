
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
SDLFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
OBJS = main.o Game.o Engine.o

all: game

game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o game $(OBJS) $(SDLFLAGS)

main.o: main.cpp Game.h Engine.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h Engine.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Engine.o: Engine.cpp Engine.h
	$(CXX) $(CXXFLAGS) -c Engine.cpp

clean:
	rm -f *.o game
