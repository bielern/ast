/**
 * The lexer for the "J"-Format.
 *
 * It recognizes, integers, doubles, words, strings
 * and the signs for objects and lists
 */
%{
#include <iostream>
#include <string>
#include "jscanner.h"

/* import the parser's token type into a local typedef */
typedef io::JParser::token token;
typedef io::JParser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* Save strings without the quotes */
#define SAVE_STRING \
    yylval->string = new std::string(yytext + 1, yyleng - 2);

#define SAVE_WORD \
    yylval->string = new std::string(yytext, yyleng); 

%}

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="J"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput 

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

INT         [0-9]*
DOUBLE      [0-9]*\.[0-9]*([eE][+-]?{INT})?
WORD        [[:alnum:]_]*
STRING      ["][^"\n]*["] 
    /*"*/
IS          "="
OBJ_START   \{ 
OBJ_END     \} 
LST_START   \[ 
LST_END     \] 
COMMENT_SGN "//"
COMMENT     {COMMENT_SGN}[^\n]*\n

%{
    // reset location
    // yylloc->step()
%}

%%

[ \t\r]     { yylloc->step();                        } 
[ \n]       { yylloc->lines(yyleng); yylloc->step(); } 
{COMMENT}   { yylloc->lines(yyleng); yylloc->step(); }
{IS}        { return token::IS; }
{OBJ_START} { return token::OBJ_START; }
{OBJ_END}   { return token::OBJ_END;   }
{LST_START} { return token::LST_START; }
{LST_END}   { return token::LST_END;   }
{INT}       { SAVE_WORD; return token::INT; }
{DOUBLE}    { SAVE_WORD; return token::DOUBLE; }
{STRING}    { SAVE_STRING; return token::STRING; }
{WORD}      { SAVE_WORD;   return token::WORD; }
.           { std::cerr << "Unknown character: " <<  yytext << "\n"; }

%% /*** Additional Code ***/

namespace io {

JScanner::JScanner(std::istream* in,
		 std::ostream* out)
    : JFlexLexer(in, out)
{
}

JScanner::~JScanner()
{
}

void JScanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int JFlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int JFlexLexer::yywrap()
{
    return 1;
}
