LEX=flex
LEXOBJ=src/parser/jscanner.o
LEXSOURCE=src/parser/jscanner.ll
LEXFILES=src/parser/jscanner.cc
LFLAGS=-o $(LEXFILES)
YACC=bison
YACCOBJ=src/parser/jparser.o
YACCFILES=src/parser/jparser.cc
YACCSOURCE=src/parser/jparser.yy
YFLAGS=-Wall -d  -o $(YACCFILES)

CXX=g++
CXXFLAGS=-Wall -g #-o $(NAME)
PARSEROBJ=$(YACCOBJ) $(LEXOBJ) src/parser/jdriver.o src/parser/input_file.o
TREEOBJ=src/tree/ast.o src/tree/node.o src/tree/node_operator.o
OBJECTS=$(PARSEROBJ) $(TREEOBJ) src/test.o

PARSERFILES=src/parser/jparser.cc src/parser/jscanner.cc

all:  clean $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o test/test $(OBJECTS)

$(LEXFILES): $(YACCFILES) $(LEXSOURCE)
	$(LEX) $(LFLAGS) $(LEXSOURCE)

$(YACCFILES): $(YACCSOURCE)
	$(YACC) $(YFLAGS) $(YACCSOURCE)

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(PARSERFILES) test/test
