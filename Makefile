FLEXOBJ=parser/scanner.o
BISONOBJ=parser/parser.o

CXX=g++
CXXFLAGS=-Wall -g #-o $(NAME)
PARSEROBJ=$(BISONOBJ) $(FLEXOBJ) parser/driver.o 
TREEOBJ=tree/ast.o tree/node.o tree/node_operator.o
OBJECTS=$(TREEOBJ) $(PARSEROBJ) test.o

PARSERFILES=parser/parser.cc parser/scanner.cc

#
#FLEX=flex++
#FLEXSOURCE=tokens.l
#
#token:
#	$(FLEX) $(FLEXSOURCE)
#
#main: $(OBJECTS)
#	$(CXX) $(CXXFLAGS) $(OBJECTS)

all:  bison flex $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o test $(OBJECTS)

bison:
	bison -Wall -d -t -o parser/parser.cc parser/parser.yy

flex:
	flex -o parser/scanner.cc parser/scanner.ll 

clean:
	rm -f $(OBJECTS) $(PARSERFILES) test
