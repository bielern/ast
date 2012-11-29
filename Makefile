FLEXOBJ=src/parser/jscanner.o
BISONOBJ=src/parser/jparser.o

CXX=g++
CXXFLAGS=-Wall -g #-o $(NAME)
PARSEROBJ=$(BISONOBJ) $(FLEXOBJ) src/parser/jdriver.o src/parser/input_file.o
TREEOBJ=src/tree/ast.o src/tree/node.o src/tree/node_operator.o
OBJECTS=$(TREEOBJ) $(PARSEROBJ) src/test.o

PARSERFILES=src/parser/jparser.cc src/parser/jscanner.cc

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
	$(CXX) $(CXXFLAGS) -o test/test $(OBJECTS)

bison:
	bison -Wall -d -t -o src/parser/jparser.cc src/parser/jparser.yy

flex:
	flex -o src/parser/jscanner.cc src/parser/jscanner.ll 

clean:
	rm -f $(OBJECTS) $(PARSERFILES) test/test
