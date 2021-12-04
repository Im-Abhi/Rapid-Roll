# -L path where are libraries are located src/lib
# -l which library to include
# -I searches for the files in #include <something>
LIBRARIES	:= -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio

all: compile link

compile:
	g++ -I src/include -I include -I lib -c main.cpp -c lib/*.cpp
link:
	g++ main.o -o main -L src/lib $(LIBRARIES)
	.\main.exe