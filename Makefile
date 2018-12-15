CXX := g++
MXX := mpic++
MXXFLAGS := -std=c++11
CXXFLAGS := -std=c++11 -Wall -g -fno-stack-protector -D_FORTIFY_SOURCE=0
LDFLAGS := -lGL -lGLU -lglut
TARGET := main
PARALLEL := parallel

SOURCES := ${wildcard *.cpp}
OBJECTS := ${SOURCES:.cpp=.o}
HEADERS := ${wildcard *.h}

serial:
	g++ -std=c++11 main.cpp Agent.h Agent.cpp HueristicAgent.h HueristicAgent.cpp Board.h Board.cpp -o serial.out

clean:
	-rm -f $(TARGET)
	-rm -f $(OBJECTS)

parallel: 
	mpic++ -std=c++11 parallel_main.cpp Agent.h Agent.cpp MonteCarloParallelAgent.cpp MonteCarloParallelAgent.h MonteCarloAgent.cpp MonteCarloAgent.h Board.h Board.cpp -o parallel.out
