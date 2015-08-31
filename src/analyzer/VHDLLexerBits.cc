#include "VHDLLexer.hh"
#include "scram_plugin_class_factory.hh"

// These methods are separated out because they require the class factory
// to do their job.  We don't want to include the class factory in the
// VHDLLexer.hh header as we don't need that dependency to propagate
// unnecessarily.

ANTLRAbstractToken *
VHDLLexer::buildIdentifierToken( ANTLRTokenType tt,
				 char* text, 
				 unsigned int textLength ){
  ANTLRToken *token;
  
  ASSERT(strlen(text)==textLength);
  
  token = new ANTLRToken(tt,_FileName,_LineNo,_LineOffset,_FileOffset);
  advanceOffsets(textLength);
  
  plugin_class_factory *factory = scram_plugin_class_factory::instance();
  token->setIIRPtr( dynamic_cast<IIRScram *>(IIRScram_Identifier::get(text, textLength, factory)));
  return token;
}

ANTLRAbstractToken *
VHDLLexer::buildLiteralToken( ANTLRTokenType tt,
			      char *text,
			      unsigned int textLength ){
  ANTLRToken *token;
  
  ASSERT(text != NULL);
  ASSERT(strlen(text)==textLength);
  
  token = new ANTLRToken(tt,_FileName,_LineNo,_LineOffset,_FileOffset);
  advanceOffsets(textLength);
  
  plugin_class_factory *factory = scram_plugin_class_factory::instance();
  switch (tt) {
  case CHARACTER_LITERAL:
    ASSERT(textLength==3);
    token->setIIRPtr(IIRScram_CharacterLiteral::get(text, textLength));
    break;
  case STRING_LITERAL:
    token->setIIRPtr(dynamic_cast<IIRScram_StringLiteral *>(IIRScram_StringLiteral::get(text, textLength, factory)));
    break;
  case BIT_STRING_LITERAL:
    token->setIIRPtr(IIRScram_BitStringLiteral::get(text, textLength));
    break;
  default:
    abort();
  };
  return token;
}
