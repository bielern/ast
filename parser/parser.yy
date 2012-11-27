%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

// DEBUG
#include <iostream>

#include "../tree/node.h"

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug
%verbose
%define parse.trace

/* start symbol is named "start" */
%start fields

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="io"

/* set the parser's class identifier */
%define "parser_class_name" "JParser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

%union {
    std::string*    string;
    struct Field*      field;
    struct Value*      value;
    int             token;
}

%token			END	     0	"end of file"
%token			EOL		"end of line"
%token			IS
%token			OBJ_START
%token			OBJ_END
%token			LST_START
%token			LST_END
%token <string> 	    STRING		"string"
%token <string> 	    WORD		"word"

%type <field>	field
%type <string>	key
%type <value>	item value

%destructor { delete $$; } STRING

/* Add debug information to states and tokens 
 */
%printer { std::cout << "Found field\n"; } <field>
%printer { std::cout << "Found key\n";   } WORD
%printer { std::cout << "Found value\n"; } STRING


%{

#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/


fields: /* empty */
      | field fields    { driver.root.push_back($1); }

field: key IS value     { $$ = new Field(*($1), $3); }

key: WORD               { $$ = $1; }

value: item             { $$ = $1; }

item: STRING            { $$ = new Item(*$1); }


%% /*** Additional Code ***/

void io::JParser::error(const JParser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}

