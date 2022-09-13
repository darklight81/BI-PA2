CXXFLAGS=-Wall -pedantic -std=c++11
CXX=g++
RM=rm -rf
OBJECTS=bin/objects/main.o bin/objects/CInterface.o bin/objects/CMultipleChoice.o bin/objects/COpenText.o bin/objects/CPage.o bin/objects/CQuestion.o bin/objects/CQuiz.o bin/objects/CSequence.o
BIN=./sulovigo
DOXY=Doxyfile

all:	$(OBJECTS)
	make compile
compile:	$(BIN)

run:	$(BIN)
	$(BIN)
doc:	Doxyfile src/*
	doxygen Doxyfile
clean:
	$(RM) doc bin $(BIN)
	
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)
		
bin/objects/main.o: src/main.cpp
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/objects/main.o
 
bin/objects/CInterface.o: src/CInterface.cpp src/CInterface.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/CInterface.cpp -o bin/objects/CInterface.o
 
bin/objects/CMultipleChoice.o: src/CMultipleChoice.cpp src/CMultipleChoice.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/CMultipleChoice.cpp -o bin/objects/CMultipleChoice.o
 
bin/objects/COpenText.o: src/COpenText.cpp src/COpenText.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/COpenText.cpp -o bin/objects/COpenText.o
 
bin/objects/CPage.o: src/CPage.cpp src/CPage.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/CPage.cpp -o bin/objects/CPage.o
 
bin/objects/CQuestion.o: src/CQuestion.cpp src/CQuestion.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/CQuestion.cpp -o bin/objects/CQuestion.o
 
bin/objects/CQuiz.o: src/CQuiz.cpp src/CQuiz.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/CQuiz.cpp -o bin/objects/CQuiz.o $(CLIBS)
 
bin/objects/CSequence.o: src/CSequence.cpp src/CSequence.h
	mkdir -p bin/objects
	$(CXX) $(CXXFLAGS) -c src/CSequence.cpp -o bin/objects/CSequence.o