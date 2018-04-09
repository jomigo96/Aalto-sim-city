CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE=main
DOCC=doxygen

SOURCES=$(wildcard *.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
DOCDIR=../doc

all: $(SOURCES) $(EXECUTABLE) doc
  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cc.o:
	$(CC) $(CPPFLAGS) $< -o $@

doc:
	@$(DOCC) 1>/dev/null

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(DOCDIR)/html $(DOCDIR)/latex

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all doc clean