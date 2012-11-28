FLEXOBJ=src/parser/scanner.o
BISONOBJ=src/parser/parser.o

CXX=g++
CXXFLAGS=-Wall -g #-o $(NAME)
PARSEROBJ=$(BISONOBJ) $(FLEXOBJ) src/parser/driver.o 
TREEOBJ=src/tree/ast.o src/tree/node.o src/tree/node_operator.o
OBJECTS=$(TREEOBJ) $(PARSEROBJ) src/test.o

PARSERFILES=src/parser/parser.cc src/parser/scanner.cc

#
#FLEX=flex++
#FLEXSOURCE=tokens.l
#
#token:
#	$(FLEX) $(FLEXSOURCE)
#
#main: $(OBJECTS)
#	$(CXX) $(CXXFLAGS) $(OBJECTS)

all:  clean bison flex $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o test $(OBJECTS)

bison:
	bison -Wall -d -t -o src/parser/parser.cc src/parser/parser.yy

flex:
	flex -o src/parser/scanner.cc src/parser/scanner.ll 

clean:
	rm -f $(OBJECTS) $(PARSERFILES) src/test
