
#ifndef VHDLToken_HH
#define VHDLToken_HH

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

#include "savant_config.hh"
#include "VHDLTokenTypes.hh"
#include "AToken.h"
#include "IIRScram_Identifier.hh"
#include "IIRScram_TextLiteral.hh"
#include <fstream>

using std::cerr;
using std::endl;

class ANTLRToken : public ANTLRRefCountToken {

protected:

  ANTLRTokenType _type;
  char* _text;
  int _textLength;
  string _fileName;
  int _line;
  int _lineOffset;   // offset from beginning of line
  int _fileOffset;   // offset from beginning of file
  IIRScram *_iirPtr;
  
public:
  
  ANTLRToken() {
    _type = NONE;
    _text = NULL;
    _textLength = 0; 
    _fileName = "";
    _line = -1;
    _lineOffset = -1;
    _fileOffset = -1;
    _iirPtr = NULL;
  };

  // construct an ANTLRToken without text
  ANTLRToken(ANTLRTokenType tt,
	     const string &fileName,
	     int lineNo,
	     int lineOffset,
	     int fileOffset) { 
    
    _type = tt;
    _text = NULL;
    _textLength = 0;
    _fileName = fileName;
    _line = lineNo;
    _lineOffset = lineOffset;
    _fileOffset = fileOffset;
    _iirPtr = NULL;

  };

  void setText(const ANTLRChar *){}

  // construct an ANTLRToken with text
  ANTLRToken(ANTLRTokenType tt,
	     char* text,
	     int textLength,
	     const string &fileName,
	     int lineNo,
	     int lineOffset,
	     int fileOffset) { 
    
    _type = tt;
    _text = strdup(text);
    _textLength = textLength;
    _fileName = fileName;
    _line = lineNo;
    _lineOffset = lineOffset;
    _fileOffset = fileOffset;
    _iirPtr = NULL;

  };

  ~ANTLRToken() {
    if (_text!=NULL) {free( _text );};
    // do *not* delete the iirPtr; it is allocated to be handed over to
    // the parser to reduce copying; if it needs deletion, the parser must
    // do it.  however, because antlr needs getText, the parser cannot
    // reclaim this memory until after the parse is complete.  this will
    // only be a problem when the wrong IIR node is built in the lexer.
    //    if (_iirPtr != NULL) {free(_iirPtr);};
  }

  ANTLRTokenType getType() { return ((const ANTLRToken *)this)->getType(); }
  ANTLRTokenType getType() const {return _type;}

  void setIIRPtr(IIRScram *node) {_iirPtr = node;}
  IIRScram *getIIRPtr() {return _iirPtr;}

  ANTLRChar *getText(){
    return ((const ANTLRToken *)this)->getText();
  }

  ANTLRChar *getText()	const	{
    if (_text!=NULL) {
      return _text;
    } else {
      switch (_type) {
	
      case AMPERSAND:		return "&";		break;
      case L_PAREN:		return "(";		break;
      case R_PAREN:		return ")";		break;
      case L_BRACKET:		return "[";		break;
      case R_BRACKET:		return "]";		break;
      case COMMA:		return ",";		break;
      case COLON_EQUAL:		return ":=";		break;
      case COLON:		return ":";		break;
      case SEMI_COLON:		return ";";		break;
      case LESS_GREATER:	return "<>";		break;
      case LESS_EQUAL:		return "<=";		break;
      case LESS:		return "<";		break;
      case EQUAL_GREATER:	return "=>";		break;
      case EQUAL:		return "=";		break;
      case GREATER_EQUAL:	return ">=";		break;
      case GREATER:		return ">";		break;
      case CHOICE1:		return "|";		break;
      case CHOICE2:		return "!";		break;
      case NOT_EQUAL:		return "/=";		break;
      case DOT:			return ".";		break;
      case EXPONENT:		return "**";		break;
      case MULTIPLY:		return "*";		break;
      case DIVIDE:		return "/";		break;
      case PLUS:		return "+";		break;
      case MINUS:		return "-";		break;

      case ABS:			return "abs";		break;
      case ACCESS:		return "access";	break;
      case ACTIVE: 		return "active";	break;
      case AFTER:		return "after";		break;
      case ALIAS:		return "alias";		break;
      case ALL:			return "all";		break;
      case AND:			return "and";		break;
      case ARCHITECTURE:	return "architecture";	break;
      case ARRAY:		return "array";		break;
      case ASCENDING:		return "ascending";	break;
      case ASSERT:		return "assert";	break;
      case ATTRIBUTE:		return "attribute";	break;
      case BASE:		return "base";		break;
      case BEGIN_:		return "begin";		break;
      case BLOCK:		return "block";		break;
      case BODY:		return "body";		break;
      case BUFFER:		return "buffer";	break;
      case BUS:			return "bus";		break;
      case CASE:		return "case";		break;

      case CHARACTER_LITERAL:
      case STRING_LITERAL:
      case BIT_STRING_LITERAL:
	return const_cast<char *>((dynamic_cast<IIRScram_TextLiteral *>(_iirPtr))->convert_to_string().c_str());
        break;

      case COMPONENT:		return "component";	break;
      case CONFIGURATION:	return "configuration";	break;
      case CONSTANT:		return "constant";	break;
      case DELAYED:		return "delayed";	break;
      case DISCONNECT:		return "disconnect";	break;
      case DRIVING:		return "driving";	break;
      case DRIVING_VALUE:	return "driving_value";	break;
      case DOWNTO:		return "downto";	break;
      case ELSE:		return "else";		break;
      case ELSIF:		return "elsif";		break;
      case END:			return "end";		break;
      case ENTITY:		return "entity";	break;
      case EVENT:		return "event   ";	break;
      case EXIT:		return "exit";		break;
      case FILE_:		return "file";		break;
      case FOR:			return "for";		break;
      case FUNCTION:		return "function";	break;
      case GENERATE:		return "generate";	break;
      case GENERIC:		return "generic";	break;
      case GROUP:		return "group";		break;
      case GUARDED:		return "guarded";	break;
      case HIGH:		return "high";		break;

      case BASIC_IDENTIFIER:
      case EXTENDED_IDENTIFIER:
	return const_cast<char *>((dynamic_cast<IIRScram_Identifier*>(_iirPtr))->convert_to_string().c_str());
        break;

      case IF:			return "if";		break;
      case IMAGE:		return "image";		break;
      case IMPURE:		return "impure";	break;
      case IN:			return "in";		break;
      case INERTIAL:		return "inertial";	break;
      case INOUT:		return "inout";		break;
      case INSTANCE_NAME:	return "instance_name";	break;
      case IS:			return "is";		break;
      case LABEL:		return "label";		break;
      case LAST_ACTIVE:		return "last_active";	break;
      case LAST_EVENT:		return "last_event";	break;
      case LAST_VALUE:		return "last_value";	break;
      case LEFTOF:		return "leftof";	break;
      case LEFT:		return "left";		break;
      case LENGTH:		return "length";	break;
      case LIBRARY:		return "library";	break;
      case LINKAGE:		return "linkage";	break;
      case LITERAL:		return "literal";	break;
      case LOOP:		return "loop";		break;
      case LOW:			return "low";		break;
      case MAP:			return "map";		break;
      case MOD:			return "mod";		break;
      case NAND:		return "nand";		break;
      case NEW:			return "new";		break;
      case NEXT:		return "next";		break;
      case NOR:			return "nor";		break;
      case NOT:			return "not";		break;
      case NULL_:		return "null";		break;
      case OF:			return "of";		break;
      case ON:			return "on";		break;
      case OPEN:		return "open";		break;
      case OR:			return "or";		break;
      case OTHERS:		return "others";	break;
      case OUT:			return "out";		break;
      case PACKAGE_:		return "package";	break;
      case PATH_NAME:		return "path_name";	break;
      case PORT:		return "port";		break;
      case POS:			return "pos";		break;
      case PRED:		return "pred";		break;
      case POSTPONED:		return "postponed";	break;
      case PROCEDURE:		return "procedure";	break;
      case PROCESS:		return "process";	break;
      case PURE:		return "pure";		break;
      case QUIET:		return "quiet";		break;
      case QUOTE:		return "\'";		break;
      case RANGE:		return "range";		break;
      case RECORD:		return "record";	break;
      case REGISTER:		return "register";	break;
      case REJECT_:		return "reject";	break;
      case REM:			return "rem";		break;
      case REPORT:		return "report";	break;
      case RETURN:		return "return";	break;
      case REVERSE_RANGE:	return "reverse_range";	break;
      case RIGHT:		return "right";		break;
      case RIGHTOF:		return "rightof";	break;
      case ROL:			return "rol";		break;
      case ROR:			return "ror";		break;
      case SELECT:		return "select";	break;
      case SEVERITY:		return "severity";	break;
      case SIMPLE_NAME:		return "simple_name";	break;
      case SLA:			return "sla";		break;
      case SLL:			return "sll";		break;
      case SRA:			return "sra";		break;
      case SRL:			return "srl";		break;
      case SHARED:		return "shared";	break;
      case SIGNAL:		return "signal";	break;
      case STABLE:		return "stable";	break;
      case SUBTYPE:		return "subtype";	break;
      case SUCC:		return "succ";		break;
      case THEN:		return "then";		break;
      case TO:			return "to";		break;
      case TRANSACTION:		return "transaction";	break;
      case TRANSPORT:		return "transport";	break;
      case TYPE:		return "type";		break;
      case UNITS:		return "units";		break;
      case UNTIL:		return "until";		break;
      case UNAFFECTED:		return "unaffected";	break;
      case USE:			return "use";		break;
      case VAL:			return "val";		break;
      case VALUE:		return "value";		break;
      case VARIABLE:		return "variable";	break;
      case WAIT:		return "wait";		break;
      case WHEN:		return "when";		break;
      case WHILE:		return "while";		break;
      case WITH:		return "with";		break;
      case XOR:			return "xor";		break;
      case XNOR:		return "xnor";		break;

	// VHDL-AMS tokens
      case ACROSS:		return "across";	break;
      case BREAK:		return "break";		break;
      case EQUAL_EQUAL:		return "==";		break;
      case LIMIT:		return "limit";		break;
      case LTF:                 return "ltf";           break;
      case NATURE:		return "nature";	break;
      case NOISE:		return "noise";		break;
      case PROCEDURAL:		return "procedural";	break;
      case QUANTITY:		return "quantity";	break;
      case REFERENCE:		return "reference";	break;
      case SPECTRUM:		return "spectrum";	break;
      case SUBNATURE:		return "subnature";	break;
      case TERMINAL:		return "terminal";	break;
      case THROUGH:		return "through";	break;
      case TOLERANCE:		return "tolerance";	break;
      case ZTF:                 return "ztf";           break;

	// VHDL-2000 tokens
	
      case PROTECTED:		return "protected";	break;
	
      case ENDFILE:		return "<END OF FILE>";	break;

      default:
	cerr << "getText(): undefined for token type: " << (int)_type << "." << endl;
	cerr << "    Crosscheck with VHDLTokenTypes.hh for the token to define." << endl;
	return NULL;
      };
    };
  }

  ANTLRChar *getFileName()	{return const_cast<char *>(_fileName.c_str());}
  int getLine()	{return ((const ANTLRToken *)this)->getLine();}
  int getLine() const		{return _line;}
  int getLineOffset()		{return _lineOffset;}
  int getFileOffset()		{return _fileOffset;}

  void setType(ANTLRTokenType) {
    cerr << "setType(): Token fields set on construction." << endl;
  }
  void setText(ANTLRChar *) {
    cerr << "setText(): Token fields set on construction." << endl;
  }
  void setLine(int) {
    cerr << "setLine(): Token fields set on construction." << endl;
  }

  virtual ANTLRAbstractToken *makeToken(ANTLRTokenType, ANTLRChar *, int ) {
    cerr << "makeToken(): Tokens are now made by flex routines." << endl;
    return NULL;
  }

};

#endif
