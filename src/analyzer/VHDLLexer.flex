%{

// Copyright (c) The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

%}

%option yyclass="VHDLLexer"
%option noyywrap

%s ATTR
%s AMSATTR

%s VHDL93
%s VHDLAMS
%s VHDL2001

%{
#undef yyFlexLexer
#include <FlexLexer.h>
#include "VHDLLexer.hh"
#include "VHDLTokenTypes.hh"
#include <ctype.h>
#include "language_processing_control.hh"
#include "IIRScram_Comment.hh"

// global flag for parse errors
extern bool parse_error;

// define type signature and name for scanner
#undef YY_DECL
#define YY_DECL ANTLRAbstractToken *VHDLLexer::getToken()

// external flag to control if we catch comments in the design file or not
extern bool capture_comments;

// external object that tracks the input language to be processed
extern language_processing_control *lang_proc;

// this variable records which input language to recongize tokens for;
// the variable actually records the start condition for the specific
// input language.  
int language_to_process;

// this is an initial action that is invoked before the first scan.  it
// queries the lang_proc object to learn which input language the lexer
// should recognize
#define YY_USER_INIT \
  if (lang_proc->processing_vhdl_93()) { \
    language_to_process = VHDL93; \
    BEGIN(VHDL93); \
  } else if (lang_proc->processing_vhdl_ams()) { \
    language_to_process = VHDLAMS; \
    BEGIN(VHDLAMS); \
  } else if (lang_proc->processing_vhdl_2001()) { \
    language_to_process = VHDL2001; \
    BEGIN(VHDL2001); \
  }

%}

%%

\-\-[^\n]*	{
  if (capture_comments == true) {
    IIR_Comment *comment = new IIRScram_Comment();
    comment->set_text(strdup(yytext), yyleng);
    comment_list->append_element(comment);
  }
  _FileOffset = _FileOffset + YYLeng();
}

[\t\v\f\r ]*\n	{
  _LineNo = _LineNo + 1;
  _LineOffset = 1;
  _FileOffset = _FileOffset + YYLeng();
}

[\t\v\f\r ]+		{advanceOffsets( YYLeng() );}

<AMSATTR,ATTR>{
  active	{BEGIN(language_to_process); return buildToken( ACTIVE, yyleng );}
  ascending	{BEGIN(language_to_process); return buildToken( ASCENDING, yyleng );}
  base		{BEGIN(language_to_process); return buildToken( BASE, yyleng );}
  delayed	{BEGIN(language_to_process); return buildToken( DELAYED, yyleng );}
  driving_value	{BEGIN(language_to_process); return buildToken( DRIVING_VALUE, yyleng );}
  driving	{BEGIN(language_to_process); return buildToken( DRIVING, yyleng );}
  event    	{BEGIN(language_to_process); return buildToken( EVENT, yyleng );}
  high		{BEGIN(language_to_process); return buildToken( HIGH, yyleng );}
  image		{BEGIN(language_to_process); return buildToken( IMAGE, yyleng );}
  instance_name	{BEGIN(language_to_process); return buildToken( INSTANCE_NAME, yyleng );}
  last_active	{BEGIN(language_to_process); return buildToken( LAST_ACTIVE, yyleng );}
  last_event	{BEGIN(language_to_process); return buildToken( LAST_EVENT, yyleng );}
  last_value	{BEGIN(language_to_process); return buildToken( LAST_VALUE, yyleng );}
  leftof	{BEGIN(language_to_process); return buildToken( LEFTOF, yyleng );}
  left		{BEGIN(language_to_process); return buildToken( LEFT, yyleng );}
  length	{BEGIN(language_to_process); return buildToken( LENGTH, yyleng );}
  low		{BEGIN(language_to_process); return buildToken( LOW, yyleng );}
  path_name	{BEGIN(language_to_process); return buildToken( PATH_NAME, yyleng );}
  pos		{BEGIN(language_to_process); return buildToken( POS, yyleng );}
  pred		{BEGIN(language_to_process); return buildToken( PRED, yyleng );}
  rightof	{BEGIN(language_to_process); return buildToken( RIGHTOF, yyleng );}
  right		{BEGIN(language_to_process); return buildToken( RIGHT, yyleng );}
  reverse_range	{BEGIN(language_to_process); return buildToken( REVERSE_RANGE, yyleng );}
  simple_name	{BEGIN(language_to_process); return buildToken( SIMPLE_NAME, yyleng );}
  stable	{BEGIN(language_to_process); return buildToken( STABLE, yyleng );}
  succ		{BEGIN(language_to_process); return buildToken( SUCC, yyleng );}
  transaction	{BEGIN(language_to_process); return buildToken( TRANSACTION, yyleng );}
  quiet		{BEGIN(language_to_process); return buildToken( QUIET, yyleng );}
  value		{BEGIN(language_to_process); return buildToken( VALUE, yyleng );}
  val		{BEGIN(language_to_process); return buildToken( VAL, yyleng );}
}

<AMSATTR>{
  above         {BEGIN(language_to_process); return buildToken( ABOVE, yyleng );}
  across        {BEGIN(language_to_process); return buildToken( ACROSS, yyleng );}
  contribution  {BEGIN(language_to_process); return buildToken( CONTRIBUTION, yyleng );}
  dot           {BEGIN(language_to_process); return buildToken( DOT_, yyleng );}
  reference     {BEGIN(language_to_process); return buildToken( REFERENCE, yyleng );}
  through       {BEGIN(language_to_process); return buildToken( THROUGH, yyleng );}
  ltf           {BEGIN(language_to_process); return buildToken( LTF, yyleng );}
  ztf           {BEGIN(language_to_process); return buildToken( ZTF, yyleng );}
}

<VHDLAMS>{
  across	{BEGIN(language_to_process); return buildToken( ACROSS, yyleng );}  
  break		{BEGIN(language_to_process); return buildToken( BREAK, yyleng );}  
  ==		{BEGIN(language_to_process); return buildToken( EQUAL_EQUAL, yyleng );}  
  limit		{BEGIN(language_to_process); return buildToken( LIMIT, yyleng );}  
  nature	{BEGIN(language_to_process); return buildToken( NATURE, yyleng );}  
  noise		{BEGIN(language_to_process); return buildToken( NOISE, yyleng );}  
  procedural	{BEGIN(language_to_process); return buildToken( PROCEDURAL, yyleng );}  
  quantity	{BEGIN(language_to_process); return buildToken( QUANTITY, yyleng );}  
  reference	{BEGIN(language_to_process); return buildToken( REFERENCE, yyleng );}  
  spectrum	{BEGIN(language_to_process); return buildToken( SPECTRUM, yyleng );}  
  subnature	{BEGIN(language_to_process); return buildToken( SUBNATURE, yyleng );}  
  terminal	{BEGIN(language_to_process); return buildToken( TERMINAL, yyleng );}  
  through	{BEGIN(language_to_process); return buildToken( THROUGH, yyleng );}  
  tolerance	{BEGIN(language_to_process); return buildToken( TOLERANCE, yyleng );}  
}

<VHDL2001>{
  protected	{BEGIN(language_to_process); return buildToken( PROTECTED, yyleng );}  
}

&		{BEGIN(language_to_process); return buildToken( AMPERSAND, yyleng );}
\(		{BEGIN(language_to_process); return buildToken( L_PAREN, yyleng );}
\)		{BEGIN(language_to_process); return buildToken( R_PAREN, yyleng );}
\[		{BEGIN(language_to_process); return buildToken( L_BRACKET, yyleng );}
\]		{BEGIN(language_to_process); return buildToken( R_BRACKET, yyleng );}
,		{BEGIN(language_to_process); return buildToken( COMMA, yyleng );}

:=		{BEGIN(language_to_process); return buildToken( COLON_EQUAL, yyleng );}
:		{BEGIN(language_to_process); return buildToken( COLON, yyleng );}
;		{BEGIN(language_to_process); return buildToken( SEMI_COLON, yyleng );}
\<\>		{BEGIN(language_to_process); return buildToken( LESS_GREATER, yyleng );}
\<=		{BEGIN(language_to_process); return buildToken( LESS_EQUAL, yyleng );}
\<		{BEGIN(language_to_process); return buildToken( LESS, yyleng );}
=\>		{BEGIN(language_to_process); return buildToken( EQUAL_GREATER, yyleng );}
=		{BEGIN(language_to_process); return buildToken( EQUAL, yyleng );}
\>=		{BEGIN(language_to_process); return buildToken( GREATER_EQUAL, yyleng );}
\>		{BEGIN(language_to_process); return buildToken( GREATER, yyleng );}
\|		{BEGIN(language_to_process); return buildToken( CHOICE1, yyleng );}
\!		{BEGIN(language_to_process); return buildToken( CHOICE2, yyleng );}
\/=		{BEGIN(language_to_process); return buildToken( NOT_EQUAL, yyleng );}
\.		{BEGIN(language_to_process); return buildToken( DOT, yyleng );}

\*\*		{BEGIN(language_to_process); return buildToken( EXPONENT, yyleng );}
\*		{BEGIN(language_to_process); return buildToken( MULTIPLY, yyleng );}
\/		{BEGIN(language_to_process); return buildToken( DIVIDE, yyleng );}
\+		{BEGIN(language_to_process); return buildToken( PLUS, yyleng );}
\-		{BEGIN(language_to_process); return buildToken( MINUS, yyleng );}

abs		{BEGIN(language_to_process); return buildToken( ABS, yyleng );}
access		{BEGIN(language_to_process); return buildToken( ACCESS, yyleng );}
after		{BEGIN(language_to_process); return buildToken( AFTER, yyleng );}
alias		{BEGIN(language_to_process); return buildToken( ALIAS, yyleng );}
all		{BEGIN(language_to_process); return buildToken( ALL, yyleng );}
and		{BEGIN(language_to_process); return buildToken( AND, yyleng );}
architecture	{BEGIN(language_to_process); return buildToken( ARCHITECTURE, yyleng );}
array		{BEGIN(language_to_process); return buildToken( ARRAY, yyleng );}
assert		{BEGIN(language_to_process); return buildToken( ASSERT, yyleng );}
attribute	{BEGIN(language_to_process); return buildToken( ATTRIBUTE, yyleng );}
begin		{BEGIN(language_to_process); return buildToken( BEGIN_, yyleng );}
block		{BEGIN(language_to_process); return buildToken( BLOCK, yyleng );}
body		{BEGIN(language_to_process); return buildToken( BODY, yyleng );}
buffer		{BEGIN(language_to_process); return buildToken( BUFFER, yyleng );}
bus		{BEGIN(language_to_process); return buildToken( BUS, yyleng );}
case		{BEGIN(language_to_process); return buildToken( CASE, yyleng );}
component	{BEGIN(language_to_process); return buildToken( COMPONENT, yyleng );}
configuration	{BEGIN(language_to_process); return buildToken( CONFIGURATION, yyleng );}
constant	{BEGIN(language_to_process); return buildToken( CONSTANT, yyleng );}
disconnect	{BEGIN(language_to_process); return buildToken( DISCONNECT, yyleng );}
downto		{BEGIN(language_to_process); return buildToken( DOWNTO, yyleng );}
else		{BEGIN(language_to_process); return buildToken( ELSE, yyleng );}
elsif		{BEGIN(language_to_process); return buildToken( ELSIF, yyleng );}
end		{BEGIN(language_to_process); return buildToken( END, yyleng );}
entity		{BEGIN(language_to_process); return buildToken( ENTITY, yyleng );}
exit		{BEGIN(language_to_process); return buildToken( EXIT, yyleng );}
file		{BEGIN(language_to_process); return buildToken( FILE_, yyleng );}
for		{BEGIN(language_to_process); return buildToken( FOR, yyleng );}
function	{BEGIN(language_to_process); return buildToken( FUNCTION, yyleng );}
generate	{BEGIN(language_to_process); return buildToken( GENERATE, yyleng );}
generic		{BEGIN(language_to_process); return buildToken( GENERIC, yyleng );}
group		{BEGIN(language_to_process); return buildToken( GROUP, yyleng );}
guarded		{BEGIN(language_to_process); return buildToken( GUARDED, yyleng );}
if		{BEGIN(language_to_process); return buildToken( IF, yyleng );}
impure		{BEGIN(language_to_process); return buildToken( IMPURE, yyleng );}
inertial	{BEGIN(language_to_process); return buildToken( INERTIAL, yyleng );}
inout		{BEGIN(language_to_process); return buildToken( INOUT, yyleng );}
in		{BEGIN(language_to_process); return buildToken( IN, yyleng );}
is		{BEGIN(language_to_process); return buildToken( IS, yyleng );}
label		{BEGIN(language_to_process); return buildToken( LABEL, yyleng );}
library		{BEGIN(language_to_process); return buildToken( LIBRARY, yyleng );}
linkage		{BEGIN(language_to_process); return buildToken( LINKAGE, yyleng );}
literal		{BEGIN(language_to_process); return buildToken( LITERAL, yyleng );}
loop		{BEGIN(language_to_process); return buildToken( LOOP, yyleng );}
map		{BEGIN(language_to_process); return buildToken( MAP, yyleng );}
mod		{BEGIN(language_to_process); return buildToken( MOD, yyleng );}
nand		{BEGIN(language_to_process); return buildToken( NAND, yyleng );}
new		{BEGIN(language_to_process); return buildToken( NEW, yyleng );}
next		{BEGIN(language_to_process); return buildToken( NEXT, yyleng );}
nor		{BEGIN(language_to_process); return buildToken( NOR, yyleng );}
not		{BEGIN(language_to_process); return buildToken( NOT, yyleng );}
null		{BEGIN(language_to_process); return buildToken( NULL_, yyleng );}
of		{BEGIN(language_to_process); return buildToken( OF, yyleng );}
on		{BEGIN(language_to_process); return buildToken( ON, yyleng );}
open		{BEGIN(language_to_process); return buildToken( OPEN, yyleng );}
or		{BEGIN(language_to_process); return buildToken( OR, yyleng );}
others		{BEGIN(language_to_process); return buildToken( OTHERS, yyleng );}
out		{BEGIN(language_to_process); return buildToken( OUT, yyleng );}
package		{BEGIN(language_to_process); return buildToken( PACKAGE_, yyleng );}
port		{BEGIN(language_to_process); return buildToken( PORT, yyleng );}
postponed	{BEGIN(language_to_process); return buildToken( POSTPONED, yyleng );}
procedure	{BEGIN(language_to_process); return buildToken( PROCEDURE, yyleng );}
process		{BEGIN(language_to_process); return buildToken( PROCESS, yyleng );}
pure		{BEGIN(language_to_process); return buildToken( PURE, yyleng );}
range		{BEGIN(language_to_process); return buildToken( RANGE, yyleng );}
record		{BEGIN(language_to_process); return buildToken( RECORD, yyleng );}
register	{BEGIN(language_to_process); return buildToken( REGISTER, yyleng );}
reject		{BEGIN(language_to_process); return buildToken( REJECT_, yyleng );}
rem		{BEGIN(language_to_process); return buildToken( REM, yyleng );}
report		{BEGIN(language_to_process); return buildToken( REPORT, yyleng );}
return		{BEGIN(language_to_process); return buildToken( RETURN, yyleng );}
rol		{BEGIN(language_to_process); return buildToken( ROL, yyleng );}
ror		{BEGIN(language_to_process); return buildToken( ROR, yyleng );}
select		{BEGIN(language_to_process); return buildToken( SELECT, yyleng );}
severity	{BEGIN(language_to_process); return buildToken( SEVERITY, yyleng );}
sla		{BEGIN(language_to_process); return buildToken( SLA, yyleng );}
sll		{BEGIN(language_to_process); return buildToken( SLL, yyleng );}
sra		{BEGIN(language_to_process); return buildToken( SRA, yyleng );}
srl		{BEGIN(language_to_process); return buildToken( SRL, yyleng );}
shared		{BEGIN(language_to_process); return buildToken( SHARED, yyleng );}
signal		{BEGIN(language_to_process); return buildToken( SIGNAL, yyleng );}
subtype		{BEGIN(language_to_process); return buildToken( SUBTYPE, yyleng );}
then		{BEGIN(language_to_process); return buildToken( THEN, yyleng );}
to		{BEGIN(language_to_process); return buildToken( TO, yyleng );}
transport	{BEGIN(language_to_process); return buildToken( TRANSPORT, yyleng );}
type		{BEGIN(language_to_process); return buildToken( TYPE, yyleng );}
units		{BEGIN(language_to_process); return buildToken( UNITS, yyleng );}
until		{BEGIN(language_to_process); return buildToken( UNTIL, yyleng );}
unaffected	{BEGIN(language_to_process); return buildToken( UNAFFECTED, yyleng );}
use		{BEGIN(language_to_process); return buildToken( USE, yyleng );}
variable	{BEGIN(language_to_process); return buildToken( VARIABLE, yyleng );}
wait		{BEGIN(language_to_process); return buildToken( WAIT, yyleng );}
when		{BEGIN(language_to_process); return buildToken( WHEN, yyleng );}
while		{BEGIN(language_to_process); return buildToken( WHILE, yyleng );}
with		{BEGIN(language_to_process); return buildToken( WITH, yyleng );}
xor		{BEGIN(language_to_process); return buildToken( XOR, yyleng );}
xnor		{BEGIN(language_to_process); return buildToken( XNOR, yyleng );}


[a-zÀ-ÖØ-Þß-öø-ÿ](_?[a-zÀ-ÖØ-Þß-öø-ÿ0-9]+)*	{
  int j;
  
  BEGIN(language_to_process); 
  
  // downcase the identifier
  for (j = 0; j <= yyleng; j++) {yytext[j] = tolower(yytext[j]);};
  
  return buildIdentifierToken( BASIC_IDENTIFIER, yytext, yyleng );
}

\\([^\\\000-\037\177-\237]|\\\\)+\\	{
  BEGIN(language_to_process); 
  return buildIdentifierToken( EXTENDED_IDENTIFIER, (char *)YYText(), yyleng );
}

((0[_0]*)?2\#[0-1](_?[0-1]+)*\.[0-1](_?[0-1]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?2\:[0-1](_?[0-1]+)*\.[0-1](_?[0-1]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?2\#[0-1](_?[0-1]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?2\:[0-1](_?[0-1]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?3\#[0-2](_?[0-2]+)*\.[0-2](_?[0-2]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?3\:[0-2](_?[0-2]+)*\.[0-2](_?[0-2]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?3\#[0-2](_?[0-2]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?3\:[0-2](_?[0-2]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?4\#[0-3](_?[0-3]+)*\.[0-3](_?[0-3]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?4\:[0-3](_?[0-3]+)*\.[0-3](_?[0-3]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?4\#[0-3](_?[0-3]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?4\:[0-3](_?[0-3]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?5\#[0-4](_?[0-4]+)*\.[0-4](_?[0-4]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?5\:[0-4](_?[0-4]+)*\.[0-4](_?[0-4]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?5\#[0-4](_?[0-4]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?5\:[0-4](_?[0-4]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?6\#[0-5](_?[0-5]+)*\.[0-5](_?[0-5]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?6\:[0-5](_?[0-5]+)*\.[0-5](_?[0-5]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?6\#[0-5](_?[0-5]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?6\:[0-5](_?[0-5]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process); 
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?7\#[0-6](_?[0-6]+)*\.[0-6](_?[0-6]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?7\:[0-6](_?[0-6]+)*\.[0-6](_?[0-6]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?7\#[0-6](_?[0-6]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?7\:[0-6](_?[0-6]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?8\#[0-7](_?[0-7]+)*\.[0-7](_?[0-7]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?8\:[0-7](_?[0-7]+)*\.[0-7](_?[0-7]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?8\#[0-7](_?[0-7]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?8\:[0-7](_?[0-7]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?9\#[0-8](_?[0-8]+)*\.[0-8](_?[0-8]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?9\:[0-8](_?[0-8]+)*\.[0-8](_?[0-8]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?9\#[0-8](_?[0-8]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?9\:[0-8](_?[0-8]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?0\#[0-9](_?[0-9]+)*\.[0-9](_?[0-9]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?0\:[0-9](_?[0-9]+)*\.[0-9](_?[0-9]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?0\#[0-9](_?[0-9]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?0\:[0-9](_?[0-9]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?1\#[0-9a](_?[0-9a]+)*\.[0-9a](_?[0-9a]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?1\:[0-9a](_?[0-9a]+)*\.[0-9a](_?[0-9a]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?1\#[0-9a](_?[0-9a]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?1\:[0-9a](_?[0-9a]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?2\#[0-9a-b](_?[0-9a-b]+)*\.[0-9a-b](_?[0-9a-b]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?2\:[0-9a-b](_?[0-9a-b]+)*\.[0-9a-b](_?[0-9a-b]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?2\#[0-9a-b](_?[0-9a-b]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?2\:[0-9a-b](_?[0-9a-b]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?3\#[0-9a-c](_?[0-9a-c]+)*\.[0-9a-c](_?[0-9a-c]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?3\:[0-9a-c](_?[0-9a-c]+)*\.[0-9a-c](_?[0-9a-c]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?3\#[0-9a-c](_?[0-9a-c]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?3\:[0-9a-c](_?[0-9a-c]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?4\#[0-9a-d](_?[0-9a-d]+)*\.[0-9a-d](_?[0-9a-d]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?4\:[0-9a-d](_?[0-9a-d]+)*\.[0-9a-d](_?[0-9a-d]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?4\#[0-9a-d](_?[0-9a-d]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?4\:[0-9a-d](_?[0-9a-d]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?5\#[0-9a-e](_?[0-9a-e]+)*\.[0-9a-e](_?[0-9a-e]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?5\:[0-9a-e](_?[0-9a-e]+)*\.[0-9a-e](_?[0-9a-e]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?5\#[0-9a-e](_?[0-9a-e]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?5\:[0-9a-e](_?[0-9a-e]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?6\#[0-9a-f](_?[0-9a-f]+)*\.[0-9a-f](_?[0-9a-f]+)*\#(e(\+|\-)?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?6\:[0-9a-f](_?[0-9a-f]+)*\.[0-9a-f](_?[0-9a-f]+)*\:(e(\+|\-)?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedFloatToken( (char *)YYText(), yyleng );
}

((0[_0]*)?1_?6\#[0-9a-f](_?[0-9a-f]+)*\#(e\+?[0-9](_?[0-9]+)*)?|(0[_0]*)?1_?6\:[0-9a-f](_?[0-9a-f]+)*\:(e\+?[0-9](_?[0-9]+)*)?) {
  BEGIN(language_to_process);
  return buildBasedIntToken( (char *)YYText(), yyleng );
}

((0[_0]*)?(2|3|4|5|6|7|8|9|(1_?0)|(1_?1)|(1_?2)|(1_?3)|(1_?4)|(1_?5)|(1_?6))\#[0-9a-f](_?[0-9a-f]+)*\#(e\-[0-9](_?[0-9]+)*)?|(0[_0]*)?(2|3|4|5|6|7|8|9|(1_?0)|(1_?1)|(1_?2)|(1_?3)|(1_?4)|(1_?5)|(1_?6))\:[0-9a-f](_?[0-9a-f]+)*\:(e\-[0-9](_?[0-9]+)*)?) {
  cerr 
    << "file: "
    << _FileName
    << "line: " 
    << _LineNo
    << ": Illegal based integer literal "
    << yytext
    << ".  Negative exponent not allowed."
    << endl;
  parse_error = TRUE;
  BEGIN(language_to_process);
  return buildBasedIntToken( "2#00#", 5 ); // default for continuing parse
}


b\"[0-1](_?[0-1]+)*\"|b\%[0-1](_?[0-1]+)*\%|o\"[0-7](_?[0-7]+)*\"|o\%[0-7](_?[0-7]+)*\%|x\"[0-9a-f](_?[0-9a-f]+)*\"|x\%[0-9a-f](_?[0-9a-f]+)*\% {
  BEGIN(language_to_process); 
  return buildLiteralToken( BIT_STRING_LITERAL, (char *)YYText(), yyleng );
}

[0-9](_?[0-9]+)*\.[0-9](_?[0-9]+)*(e(\+|\-)?[0-9](_?[0-9]+)*)? {
  BEGIN(language_to_process); 
  return buildDecimalFloatToken( (char *)YYText(), yyleng );
}

[0-9](_?[0-9]+)*(e\+?[0-9](_?[0-9]+)*)? {
  BEGIN(language_to_process); 
  return buildDecimalIntToken( (char *)YYText(), yyleng );
}

[0-9](_?[0-9]+)*(e\-?[0-9](_?[0-9]+)*)? {
  cerr 
    << "file: "
    << _FileName
    << "line: " 
    << _LineNo
    << ": Illegal integer literal "
    << yytext
    << ".  Negative exponent not allowed."
    << endl;
  parse_error = TRUE;
  BEGIN(language_to_process); 
  return buildDecimalIntToken( "0", 1 ); // default to continue parse
}

(\"([0-9a-z\ \#\&\;\(\)\*\+\,\-\.\/\:\;\<\=\>\_\|\!\$\%\@\?\[\\\]\^\`\'\{\}\~]|(\"\"))*\"|\%([0-9a-z\ \#\&\;\(\)\*\+\,\-\.\/\:\;\<\=\>\_\|\!\$\@\?\[\\\]\^\`\'\{\}\~]|(\%\%))*\%) {
  BEGIN(language_to_process); 
  return buildLiteralToken( STRING_LITERAL, (char *)YYText(), yyleng );
}

\%([0-9a-z\ \#\&\;\(\)\*\+\,\-\.\/\:\;\<\=\>\_\|\!\$\@\?\[\\\]\^\`\'\{\}\~]|(\%\%))*\"([0-9a-z\ \#\&\;\(\)\*\+\,\-\.\/\:\;\<\=\>\_\|\!\$\"\@\?\[\\\]\^\`\'\{\}\~]|(\%\%))*\% {
  cerr 
    << "file: "
    << _FileName
    << " line: " 
    << _LineNo
    << " Illegal quote character (\") encountered in percent (%) bounded string literal:"
    << endl << "    " << yytext << endl
    << "seen.  Matching zero length string literal (%%)." << endl;
  parse_error = TRUE;
  BEGIN(language_to_process); 
  return buildLiteralToken( STRING_LITERAL, "%%", 1 );
}

\'\(\'(,\'.\')+	{
  yyless(3);
  BEGIN(language_to_process);
  return buildLiteralToken(CHARACTER_LITERAL, (char *)YYText(), yyleng );
}

\'\(\'.\'	{
  yyless(1);
  BEGIN(language_to_process);
  return buildToken( QUOTE, 1 );
}

\'.\'		{
  BEGIN(language_to_process); 
  return buildLiteralToken(CHARACTER_LITERAL, (char *)YYText(), yyleng );
}

\'\(		{
  yyless(1);
  BEGIN(language_to_process);
  return buildToken( QUOTE, 1 );
}

\' {
  if (language_to_process == VHDLAMS) {
    BEGIN(AMSATTR);
  } else {
    BEGIN(ATTR);
  }
  return buildToken( QUOTE, 1 );
}

.	{
  cerr 
    << "file: "
    << _FileName
    << " line: " 
    << _LineNo
    << " Illegal character '"
    << yytext
    << "' seen.  Ignored" << endl;
  parse_error = TRUE;
}

<<EOF>>	{BEGIN(language_to_process); return buildToken( ENDFILE, 0 );}

%%
