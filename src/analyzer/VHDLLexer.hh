
#ifndef VHDLLexer_HH
#define VHDLLexer_HH

// Copyright (c) 1996-2003 The University of Cincinnati.
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com

#include "savant_config.hh"
#include "VHDLToken.hh"
#include "ATokenStream.h"
#include "savant.hh"
#include "IIRScram_BitStringLiteral.hh"
#include "IIRScram_CharacterLiteral.hh"
#include "IIRScram_CommentList.hh"
#include "IIRScram_FloatingPointLiteral.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IntegerLiteral.hh"
#include "IIRScram_StringLiteral.hh"
#include <fstream>
#include <FlexLexer.h>

using std::ifstream;

class VHDLLexer : public yyFlexLexer, public ANTLRTokenStream {

public:
  VHDLLexer( ifstream *input, IIR_CommentList *comment_list_ptr ) : yyFlexLexer( input ) {
    comment_list = comment_list_ptr;
  };
  VHDLLexer(){
    _FileName = "";
    _LineNo = 1;
    _LineOffset = 1;
    _FileOffset = 0;
  };

  virtual ~VHDLLexer() {};

  ANTLRAbstractToken *getToken();

  // terminal locator counters/file name
  string _FileName;
  int _LineNo;
  int _LineOffset;
  int _FileOffset;

  /** build a token without copying the text of the token */
  ANTLRAbstractToken *buildToken(ANTLRTokenType tt, int tokenLength) {
    ANTLRToken *token;
    token = new ANTLRToken(tt,_FileName,_LineNo,_LineOffset,_FileOffset);
    advanceOffsets(tokenLength);
    return token;
  };

  /** build a token with a copy of the text of the token */
  ANTLRAbstractToken *buildToken(ANTLRTokenType tt, char* text, unsigned int textLength) {
    ANTLRToken *token;
    
    ASSERT(strlen(text)==textLength);

    token = new ANTLRToken(tt,text,textLength,_FileName,_LineNo,_LineOffset,_FileOffset);
    advanceOffsets(textLength);
    return token;
  };

  /** build a token for a BASIC_IDENTIFIER or EXTENDED_IDENTIFIER */
  ANTLRAbstractToken *buildIdentifierToken( ANTLRTokenType tt, char* text, 
					    unsigned int textLength);

  // build a token for non-numeric literals
  ANTLRAbstractToken *buildLiteralToken(ANTLRTokenType tt, char* text, unsigned int textLength);

  // build a token for a DECIMAL_INTEGER_LITERAL
  ANTLRAbstractToken *buildDecimalIntToken( char* text, unsigned int textLength) {

    ANTLRToken *token;
    
    ASSERT(strlen(text)==textLength);

    // use a token that stores the text to preserve ability to regen original string in error reporting.
    token = new ANTLRToken(DECIMAL_INTEGER_LITERAL,text,textLength,_FileName,_LineNo,_LineOffset,_FileOffset);
    advanceOffsets(textLength);

    char* origText = strdup(text);
    char* mantissa = NULL;
    char* exponent = NULL;
    int exponentLength = 0;

    setDecimalMantissaExponent(origText, &mantissa, &exponent);
    
    if (exponent != NULL) {
      exponentLength = strlen(exponent);
    };
	
    token->setIIRPtr(dynamic_cast<IIRScram *>(IIRScram_IntegerLiteral::get(10, mantissa, strlen(mantissa), exponent, exponentLength)));
		     
    free(origText);

    return token;
  };

  // build a token for a DECIMAL_FLOATING_POINT_LITERAL
  ANTLRAbstractToken *buildDecimalFloatToken( char* text, unsigned int textLength) {
    ANTLRToken *token;
    
    ASSERT(strlen(text)==textLength);

    // use a token that stores the text to preserve ability to regen original string in error reporting.
    token = new ANTLRToken(DECIMAL_FLOATING_POINT_LITERAL,text,textLength,_FileName,_LineNo,_LineOffset,_FileOffset);
    advanceOffsets(textLength);

    char* origText = strdup(text);
    char* mantissa = NULL;
    char* exponent = NULL;
    int exponentLength = 0;

    setDecimalMantissaExponent(origText, &mantissa, &exponent);
    
    if (exponent != NULL) {
      exponentLength = strlen(exponent);
    };
	
    token->setIIRPtr(dynamic_cast<IIRScram *>(IIRScram_FloatingPointLiteral::get(10, mantissa, strlen(mantissa), exponent, exponentLength)));
		     
    free(origText);

    return token;
  };

  // build a token for a BASED_INTEGER_LITERAL
  ANTLRAbstractToken *buildBasedIntToken( char* text, unsigned int textLength) {
    ANTLRToken *token;
    
    ASSERT(strlen(text)==textLength);

    // use a token that stores the text to preserve ability to regen original string in error reporting.
    token = new ANTLRToken(BASED_INTEGER_LITERAL,text,textLength,_FileName,_LineNo,_LineOffset,_FileOffset);
    advanceOffsets(textLength);

    int base = 0;
    char* origText = strdup(text);
    char* mantissa = NULL;
    char* exponent = NULL;
    int exponentLength = 0;

    setBaseMantissaExponent(origText, &base, &mantissa, &exponent);
    
    if (exponent != NULL) {
      exponentLength = strlen(exponent);
    };
	
    token->setIIRPtr(dynamic_cast<IIRScram *>(IIRScram_IntegerLiteral::get(base, mantissa, strlen(mantissa), exponent, exponentLength)));
		     
    free(origText);

    return token;
  };

  // build a token for a BASED_FLOATING_POINT_LITERAL
  ANTLRAbstractToken *buildBasedFloatToken( char* text, unsigned int textLength) {
    ANTLRToken *token;
    
    ASSERT(strlen(text)==textLength);

    // use a token that stores the text to preserve ability to regen original string in error reporting.
    token = new ANTLRToken(BASED_FLOATING_POINT_LITERAL,text,textLength,_FileName,_LineNo,_LineOffset,_FileOffset);
    advanceOffsets(textLength);

    int base = 0;
    char* origText = strdup(text);
    char* mantissa = NULL;
    char* exponent = NULL;
    int exponentLength = 0;

    setBaseMantissaExponent(origText, &base, &mantissa, &exponent);
    
    if (exponent != NULL) {
      exponentLength = strlen(exponent);
    };
	
    token->setIIRPtr(dynamic_cast<IIRScram *>(IIRScram_FloatingPointLiteral::get(base, mantissa, strlen(mantissa), exponent, exponentLength)));
		     
    free(origText);

    return token;
  };

  // function for external procedures to reset my internal state for proper
  // location setup
  void resetLexerFileLocators( const string &fname ){
    _FileName = fname;
    _LineNo = 1;
    _LineOffset = 1;
    _FileOffset = 0;
  }

  // procedure to advance values of offset counters
  void advanceOffsets( int length ) {
    _LineOffset = _LineOffset + length;
    _FileOffset = _FileOffset + length;
  }

private:

  void setDecimalMantissaExponent(char* origText, char** mantissa, char** exponent) {
    
    *mantissa = origText;

    stripChar(*mantissa, '_');  // remove underscores from the string
    
    *exponent = strchr(*mantissa, 'e');
    if (*exponent == NULL) {
      *exponent = strchr(*mantissa, 'E');
    }
    
    if (*exponent != NULL) {
      **exponent = '\0'; // if exponent present, null terminate the mantissa
      *exponent = (char*) (*exponent + 1); // advance the exponent pointer past the 'e'
    }
  }

  void setBaseMantissaExponent(char* origText, int* base, char** mantissa, char** exponent) {
    
    stripChar(origText, '_');  // remove underscores from the string
    
    *mantissa = strchr(origText, '#');
    if (*mantissa == NULL) {
      *mantissa = strchr(origText, ':');
    }

    ASSERT(*mantissa != NULL);  // can't find end of base string

    **mantissa = '\0'; // terminate char string for base
    *mantissa = (char*) (*mantissa + 1); // advance to beginning of mantissa string

    *base = atoi(origText); // compute integer value of the base
    
    char* mantissaEnd = strchr(*mantissa, '#');
    if (mantissaEnd == NULL) {
      mantissaEnd = strchr(*mantissa, ':');
    }

    ASSERT(mantissaEnd != NULL);  // can't find end of base string

    *mantissaEnd = '\0'; // terminate mantissa char string
    mantissaEnd++; // advance to beginning of exponent

    
    if (mantissaEnd[0] == '\0') {
      *exponent = NULL; // no exponent
      return; 
    }

    *exponent = strchr(mantissaEnd, 'e');
    if (*exponent == NULL) {
      *exponent = strchr(mantissaEnd, 'E');
    }
    
    if (*exponent != NULL) {
      *exponent = (char*) (*exponent + 1); // advance the exponent pointer past the 'e'
    }

    ASSERT(*exponent != NULL); // the previous test should have found when no exponent present

  }
  
  char *stripChar( char *string, char remove_me ){
    int i;
    int pos = 0;
    int length = strlen( string );
    
    for( i = 0; i < length; i++ ){
      if( string[i] != remove_me ){
	string[pos] = string[i];
	pos++;
      }
    }
    string[ pos ] = '\0';
    return string;
  }

  // The lexer will append comments to this list if we it is told to
  // capture comments.  
  IIR_CommentList *comment_list;
};

#endif
