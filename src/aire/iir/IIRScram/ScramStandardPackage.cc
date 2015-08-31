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

#include "ScramStandardPackage.hh"
#include "IIRScram_AccessSubtypeDefinition.hh"
#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_AttributeDeclaration.hh"
#include "IIRScram_CharacterLiteral.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_FloatingPointLiteral64.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IntegerLiteral32.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_PhysicalLiteral.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRBase_String.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_SubtypeDeclaration.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_UnitList.hh"
#include "hash_table.hh"
#include "scram.hh"
#include "scram_plugin_class_factory.hh"
#include <climits>

ScramStandardPackage::ScramStandardPackage(){
  const char *id = "standard";
  set_declarator( IIRBase_Identifier::get( id, strlen( id ),
					   scram_plugin_class_factory::instance() ));
  fake_parser = new scram(false, NULL, scram_plugin_class_factory::instance(), this, false);
  fill_list( dynamic_cast<IIRScram_DeclarationList *>(get_package_declarative_part()) );
}

ScramStandardPackage::~ScramStandardPackage() {
  //Release the list memory
  delete get_package_declarative_part();
}

int 
ScramStandardPackage::STD_INT_MAX(){
  return INT_MAX;
}

int 
ScramStandardPackage::STD_INT_MIN(){
  // Putting INT_MIN in here causes some problems with default settings
  // on the compiler.  Also note that this should be the same number as
  // found in IntegerTypeInfo.cc in the runtime support.
  return -INT_MAX;
}

double 
ScramStandardPackage::REAL_MAX(){
  return 0.179769313486231e+309;
}

double 
ScramStandardPackage::REAL_MIN(){
  return -0.179769313486231e+309;
}

IIR_Identifier *
ScramStandardPackage::get_file_name(){
  static const string file_string("scram built-in standard library");
  static IIRScram_Identifier *file_name =
      dynamic_cast<IIRScram_Identifier *>( IIRBase_Identifier::get( file_string,
								    scram_plugin_class_factory::instance() ));
  return file_name;
}

IIR_DesignFile *
ScramStandardPackage::get_design_file(){
  static IIR_DesignFile *file_info = 0;
  if( !file_info ){
    file_info = scram_plugin_class_factory::instance()->new_IIR_DesignFile();
    file_info->set_name( get_file_name() );
    file_info->set_standard_package( this );
    file_info->set_parser( fake_parser );
  }
  return file_info;
}


// Boolean has to be defined before anything else
IIR_EnumerationSubtypeDefinition *
ScramStandardPackage::get_boolean_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_boolean_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_boolean_decl(){
  static IIRScram_TypeDeclaration *bool_decl = init_boolean_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(bool_decl);
}

// Here are the builtin universal types.
IIR_IntegerSubtypeDefinition *
ScramStandardPackage::get_savant_universal_integer(){
  static IIR_IntegerSubtypeDefinition  *universal_integer_type = init_integer_type();
  return universal_integer_type;
}

IIR_FloatingSubtypeDefinition *
ScramStandardPackage::get_savant_universal_real(){
  static IIR_FloatingSubtypeDefinition  *universal_real_type = init_real_type();
  return universal_real_type;
}

// These types represent those declared in std.standard.
IIR_EnumerationSubtypeDefinition *
ScramStandardPackage::get_bit_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_bit_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_bit_decl(){
  static IIRScram_TypeDeclaration *bit_decl = init_bit_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(bit_decl);
}

IIR_IntegerSubtypeDefinition *
ScramStandardPackage::get_integer_type(){
  return dynamic_cast<IIR_IntegerSubtypeDefinition *>(get_integer_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_integer_decl(){
  static IIRScram_TypeDeclaration *integer_decl = init_integer_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(integer_decl);
}

IIR_EnumerationSubtypeDefinition *
ScramStandardPackage::get_character_type(){
  IIR_EnumerationSubtypeDefinition *result = dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_character_decl()->get_type());
  return result;
}

IIR_TypeDeclaration *
ScramStandardPackage::get_character_decl(){
  static IIRScram_TypeDeclaration *character_decl = init_character_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(character_decl);
}

IIR_IntegerSubtypeDefinition *
ScramStandardPackage::get_positive_type(){
  return dynamic_cast<IIR_IntegerSubtypeDefinition *>(get_positive_decl()->get_subtype());
}

IIR_SubtypeDeclaration *
ScramStandardPackage::get_positive_decl(){
  static IIRScram_SubtypeDeclaration *positive_type = init_subtype_decl( "positive", init_positive_type() );
  return dynamic_cast<IIR_SubtypeDeclaration *>(positive_type);
}

IIR_ArraySubtypeDefinition *
ScramStandardPackage::get_string_type(){
  return dynamic_cast<IIR_ArraySubtypeDefinition *>(get_string_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_string_decl(){
  static IIRScram_TypeDeclaration *string_decl = init_string_decl( );
  return dynamic_cast<IIR_TypeDeclaration *>(string_decl);
}

IIR_EnumerationSubtypeDefinition *
ScramStandardPackage::get_severity_level_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_severity_level_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_severity_level_decl(){
  static IIRScram_TypeDeclaration *severity_level_decl = init_severity_level_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(severity_level_decl);
}

IIR_FloatingSubtypeDefinition *
ScramStandardPackage::get_real_type(){
  return dynamic_cast<IIR_FloatingSubtypeDefinition *>(get_real_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_real_decl(){
  static IIRScram_TypeDeclaration *real_decl = init_real_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(real_decl);
}

IIR_PhysicalSubtypeDefinition *
ScramStandardPackage::get_time_type(){
  return dynamic_cast<IIR_PhysicalSubtypeDefinition *>(get_time_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_time_decl(){
  static IIRScram_TypeDeclaration *time_decl = init_type_decl( "time", init_time_type() );
  return dynamic_cast<IIR_TypeDeclaration *>(time_decl);
}

IIR_PhysicalSubtypeDefinition *
ScramStandardPackage::get_delay_length_type(){
  return dynamic_cast<IIR_PhysicalSubtypeDefinition *>(get_delay_length_decl()->get_subtype());
}

IIR_SubtypeDeclaration *
ScramStandardPackage::get_delay_length_decl(){
  static IIRScram_SubtypeDeclaration *delay_length_decl = init_delay_length_decl();
  return dynamic_cast<IIR_SubtypeDeclaration *>(delay_length_decl);
}

IIR_IntegerSubtypeDefinition *
ScramStandardPackage::get_natural_type(){
  return dynamic_cast<IIR_IntegerSubtypeDefinition *>(get_natural_decl()->get_subtype());
}

IIR_SubtypeDeclaration *
ScramStandardPackage::get_natural_decl(){
  static IIRScram_SubtypeDeclaration *natural_decl
    = init_subtype_decl( "natural", init_natural_type() );
  return dynamic_cast<IIR_SubtypeDeclaration *>(natural_decl);
}

IIR_ArraySubtypeDefinition *
ScramStandardPackage::get_bit_vector_type(){
  return dynamic_cast<IIR_ArraySubtypeDefinition *>(get_bit_vector_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_bit_vector_decl(){
  static IIRScram_TypeDeclaration *bit_vector_decl = init_bit_vector_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(bit_vector_decl);
}

IIR_EnumerationSubtypeDefinition *
ScramStandardPackage::get_file_open_kind_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_file_open_kind_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_file_open_kind_decl(){
  static IIRScram_TypeDeclaration *file_open_kind_decl = init_file_open_kind_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(file_open_kind_decl);
}

IIR_EnumerationSubtypeDefinition *
ScramStandardPackage::get_file_open_status_type(){
  return dynamic_cast<IIR_EnumerationSubtypeDefinition *>(get_file_open_status_decl()->get_type());
}

IIR_TypeDeclaration *
ScramStandardPackage::get_file_open_status_decl(){
  static IIRScram_TypeDeclaration *file_open_status_decl = init_file_open_status_decl();
  return dynamic_cast<IIR_TypeDeclaration *>(file_open_status_decl);
}

IIR_AttributeDeclaration *
ScramStandardPackage::get_foreign_decl(){
  static IIRScram_AttributeDeclaration *foreign_decl  = init_foreign_decl();
  return dynamic_cast<IIR_AttributeDeclaration *>(foreign_decl);
}

IIR_FunctionDeclaration *
ScramStandardPackage::get_now_decl(){
  static IIRScram_FunctionDeclaration *now_decl = init_now_decl();
  return dynamic_cast<IIR_FunctionDeclaration *>(now_decl);
}

IIR_LibraryDeclaration *
ScramStandardPackage::get_std_decl(){
  static IIRScram_LibraryDeclaration *std_decl = init_std_decl();
  return dynamic_cast<IIR_LibraryDeclaration *>(std_decl);
}

IIR_AccessSubtypeDefinition *
ScramStandardPackage::get_savant_null_type_definition(){
  static IIR_AccessSubtypeDefinition *savant_null_type_definition = init_null_type();
  return savant_null_type_definition;
}



ScramStandardPackage *
ScramStandardPackage::instance(){
  static ScramStandardPackage *_instance = new ScramStandardPackage();
  return _instance;
}

IIR *
ScramStandardPackage::convert_tree(plugin_class_factory *factory){
  return BaseStandardPackage::convert_tree( factory );
}

void 
ScramStandardPackage::fill_list( IIRScram_DeclarationList *list ){
  list->append( get_boolean_decl() );
  list->_append( get_boolean_type()->get_enumeration_literals() );
  list->append( get_bit_decl() );
  list->_append( get_bit_type()->get_enumeration_literals() );
  list->append( get_integer_decl() );
  list->append( get_character_decl() );
  list->_append( get_character_type()->get_enumeration_literals() );
  list->append( get_positive_decl() );
  list->append( get_string_decl() );
  list->append( get_severity_level_decl() );
  list->_append( get_severity_level_type()->get_enumeration_literals() );
  list->append( get_real_decl() );
  list->append( get_time_decl() );
  list->append( get_time_type()->get_primary_unit() );
  list->_append( get_time_type()->get_units() );
  list->append( get_delay_length_decl() );
  list->append( get_natural_decl() );
  list->append( get_bit_vector_decl() );
  list->append( get_file_open_kind_decl() );
  list->_append( get_file_open_kind_type()->get_enumeration_literals() );
  list->append( get_file_open_status_decl() );
  list->_append( get_file_open_status_type()->get_enumeration_literals() );
  list->append( get_foreign_decl() );
  list->append( get_now_decl() );
}

IIRScram_IntegerSubtypeDefinition *
ScramStandardPackage::init_integer_type(){
  return init_integer_type( STD_INT_MIN(), STD_INT_MAX() );
}

IIRScram_IntegerSubtypeDefinition *
ScramStandardPackage::init_positive_type(){
  IIRScram_IntegerSubtypeDefinition *retval = NULL;

  IIRScram_RangeTypeDefinition *temp = new IIRScram_RangeTypeDefinition();

  temp->set_left( IIRScram_IntegerLiteral32::get( 1 ) );
  set_locator_info( temp->get_left() );
  temp->set_direction( get_integer_type()->get_direction() );
  set_locator_info( temp->get_direction() );
  temp->set_right( IIRScram_IntegerLiteral32::get( STD_INT_MAX() ) );
  set_locator_info( temp->get_right() );
  set_locator_info( temp );
  temp->_get_design_file()->set_parser(fake_parser);
  temp->_get_design_file()->set_standard_package(this);

  retval = dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(get_integer_type())->_construct_new_subtype( 0, temp ));
  
  retval->set_type_mark(get_integer_type());

  delete temp;

  return retval;
}

IIRScram_IntegerSubtypeDefinition *
ScramStandardPackage::init_natural_type(){
  IIRScram_IntegerSubtypeDefinition *retval = 0;

  IIRScram_RangeTypeDefinition *temp = new IIRScram_RangeTypeDefinition();

  temp->set_left( IIRScram_IntegerLiteral32::get( 0 ) );
  temp->set_direction( get_integer_type()->get_direction() );
  temp->set_right( IIRScram_IntegerLiteral32::get( STD_INT_MAX() ) );
  set_locator_info( temp->get_left() );
  set_locator_info( temp->get_direction() );
  set_locator_info( temp->get_right() );
  set_locator_info( temp );
  temp->_get_design_file()->set_parser(fake_parser);
  temp->_get_design_file()->set_standard_package(this);

  retval = dynamic_cast<IIRScram_IntegerSubtypeDefinition *> (dynamic_cast<IIRScram_IntegerSubtypeDefinition *>(get_integer_type())->_construct_new_subtype( 0, temp ));
  retval->set_type_mark( get_integer_type() );
  
  delete temp;

  return retval;
}

IIRScram_FloatingSubtypeDefinition *
ScramStandardPackage::init_real_type(){
  return init_real_type( REAL_MIN(), REAL_MAX() );
}

IIRScram_EnumerationLiteral *
ScramStandardPackage::init_false_literal(){
  IIRScram_EnumerationLiteral *retval = new IIRScram_EnumerationLiteral();
  set_locator_info( retval );
  retval->set_declarator( IIRBase_Identifier::get( "false",
						   strlen("false"),
						   scram_plugin_class_factory::instance()) );
  retval->set_position( IIRScram_IntegerLiteral32::get( 0 ) );
  set_locator_info( retval->get_position() );
  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

IIR_EnumerationLiteral *
ScramStandardPackage::get_false_literal(){
  static IIR_EnumerationLiteral *false_literal = init_false_literal();
  return false_literal;
}

IIRScram_EnumerationLiteral *
ScramStandardPackage::init_true_literal(){
  IIRScram_EnumerationLiteral *retval = new IIRScram_EnumerationLiteral();
  set_locator_info( retval );
  retval->set_declarator( IIRBase_Identifier::get( "true",
						   strlen( "true" ),
						   scram_plugin_class_factory::instance() ) );
  retval->set_position( IIRScram_IntegerLiteral32::get( 1 ) );
  set_locator_info( retval->get_position() );
  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

IIR_EnumerationLiteral *
ScramStandardPackage::get_true_literal(){
  static IIR_EnumerationLiteral *true_literal = init_true_literal();
  return true_literal;
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_boolean_decl(){
  static IIRScram_TypeDeclaration *boolean_decl = init_type_decl( "boolean", init_boolean_type() );

  boolean_decl->get_type()->set_declaration( boolean_decl );
  boolean_decl->get_type()->get_base_type()->set_declaration( boolean_decl );

  return boolean_decl;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_boolean_type(){
  IIRScram_EnumerationSubtypeDefinition *retval = NULL;

  IIRScram_EnumerationLiteralList *literals = new IIRScram_EnumerationLiteralList();
  literals->append( get_false_literal() );
  literals->append( get_true_literal() );

  retval = init_enumeration_type( literals );

  return retval;
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_bit_decl(){
  static IIRScram_TypeDeclaration *bit_decl = init_type_decl( "bit", init_bit_type() );

  bit_decl->get_type()->set_declaration( bit_decl );
  bit_decl->get_type()->get_base_type()->set_declaration( bit_decl );
  
  return bit_decl;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_bit_type(){
  char *literals[] = { "'0'", "'1'", 0 };
  return init_enumeration_type( literals );
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_character_decl(){
  static IIRScram_TypeDeclaration *character_decl 
    = init_type_decl( "character", init_character_type() );

  character_decl->get_type()->set_declaration( character_decl );
  character_decl->get_type()->get_base_type()->set_declaration( character_decl );

  return character_decl;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_character_type(){
  const char *literals[] = {
    "nul",  "soh",  "stx",  "etx",  "eot",  "enq",  "ack",  "bel",
    "bs",   "ht",   "lf",   "vt",   "ff",   "cr",   "so",   "si",
    "dle",  "dc1",  "dc2",  "dc3",  "dc4",  "nak",  "syn",  "etb",
    "can",  "em",   "sub",  "esc",  "fsp",  "gsp",  "rsp",  "usp", 
    "' '",  "'!'",  "'\"'", "'#'",  "'$'",  "'%'",  "'&'",  "'''",  
    "'('",  "')'",  "'*'",  "'+'",  "','",  "'-'",  "'.'",  "'/'",
    "'0'",  "'1'",  "'2'",  "'3'",  "'4'",  "'5'",  "'6'",  "'7'",
    "'8'",  "'9'",  "':'",  "';'",  "'<'",  "'='",  "'>'",  "'?'",
    "'@'",  "'A'",  "'B'",  "'C'",  "'D'",  "'E'",  "'F'",  "'G'",
    "'H'",  "'I'",  "'J'",  "'K'",  "'L'",  "'M'",  "'N'",  "'O'",
    "'P'",  "'Q'",  "'R'",  "'S'",  "'T'",  "'U'",  "'V'",  "'W'",
    "'X'",  "'Y'",  "'Z'",  "'['",  "'\\'",  "']'",  "'^'",  "'_'",
    "'`'",  "'a'",  "'b'",  "'c'",  "'d'",  "'e'",  "'f'",  "'g'",
    "'h'",  "'i'",  "'j'",  "'k'",  "'l'",  "'m'",  "'n'",  "'o'",
    "'p'",  "'q'",  "'r'",  "'s'",  "'t'",  "'u'",  "'v'",  "'w'",
    "'x'",  "'y'",  "'z'",  "'{'",  "'|'",  "'}'",  "'~'",  "del",
    "c128", "c129", "c130", "c131", "c132", "c133", "c134", "c135",
    "c136", "c137", "c138", "c139", "c140", "c141", "c142", "c143",
    "c144", "c145", "c146", "c147", "c148", "c149", "c150", "c151",
    "c152", "c153", "c154", "c155", "c156", "c157", "c158", "c159",
    "' '",  "'¡'",  "'¢'",  "'£'",  "'¤'",  "'¥'",  "'¦'",  "'§'", 
    "'¨'",  "'©'",  "'ª'",  "'«'",  "'¬'",  "'­'",  "'®'",  "'¯'", 
    "'°'",  "'±'",  "'²'",  "'³'",  "'´'",  "'µ'",  "'¶'",  "'·'", 
    "'¸'",  "'¹'",  "'º'",  "'»'",  "'¼'",  "'½'",  "'¾'",  "'¿'", 
    "'À'",  "'Á'",  "'Â'",  "'Ã'",  "'Ä'",  "'Å'",  "'Æ'",  "'Ç'", 
    "'È'",  "'É'",  "'Ê'",  "'Ë'",  "'Ì'",  "'Í'",  "'Î'",  "'Ï'", 
    "'Ð'",  "'Ñ'",  "'Ò'",  "'Ó'",  "'Ô'",  "'Õ'",  "'Ö'",  "'×'", 
    "'Ø'",  "'Ù'",  "'Ú'",  "'Û'",  "'Ü'",  "'Ý'",  "'Þ'",  "'ß'",
    "'à'",  "'á'",  "'â'",  "'ã'",  "'ä'",  "'å'",  "'æ'",  "'ç'",
    "'è'",  "'é'",  "'ê'",  "'ë'",  "'ì'",  "'í'",  "'î'",  "'ï'", 
    "'ð'",  "'ñ'",  "'ò'",  "'ó'",  "'ô'",  "'õ'",  "'ö'",  "'÷'",
    "'ø'",  "'ù'",  "'ú'",  "'û'",  "'ü'",  "'ý'",  "'þ'",  "'ÿ'", 
    0 };

  return init_enumeration_type( literals );
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_severity_level_decl(){
  static IIRScram_TypeDeclaration *severity_level_decl = init_type_decl( "severity_level",
								    init_severity_level_type() );
  severity_level_decl->get_type()->set_declaration( severity_level_decl );
  severity_level_decl->get_type()->get_base_type()->set_declaration( severity_level_decl );

  return severity_level_decl;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_severity_level_type(){
  const char *literals[] = {
    "note", 
    "warning", 
    "error", 
    "failure",
    0
  };

  return init_enumeration_type( literals );
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_file_open_kind_decl(){
  static IIRScram_TypeDeclaration *file_open_kind_decl 
    = init_type_decl( "file_open_kind", init_file_open_kind_type() );

  file_open_kind_decl->get_type()->set_declaration( file_open_kind_decl );
  file_open_kind_decl->get_type()->get_base_type()->set_declaration( file_open_kind_decl );

  return file_open_kind_decl;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_file_open_kind_type(){
  const char *literals[] = {
    "read_mode",
    "write_mode",  
    "append_mode",
    0
  };
  return init_enumeration_type( literals );
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_file_open_status_decl(){
  static IIRScram_TypeDeclaration *file_open_status_decl 
    = init_type_decl( "file_open_status", init_file_open_status_type() );

  file_open_status_decl->get_type()->set_declaration( file_open_status_decl );
  file_open_status_decl->get_type()->get_base_type()->set_declaration( file_open_status_decl );

  return file_open_status_decl;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_file_open_status_type(){
  const char *literals[] = {
    "open_kind",	
    "status_error",   
    "name_error",	
    "mode_error",
    0
  };
  return init_enumeration_type( literals );
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_integer_decl(){
  IIRScram_TypeDeclaration *retval = init_type_decl( "integer", init_integer_type() );

  retval->get_type()->set_declaration( retval );
  retval->get_type()->get_base_type()->set_declaration( retval );

  return retval;
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_real_decl(){
  IIRScram_TypeDeclaration *retval = init_type_decl( "real", init_real_type() );

  retval->get_type()->set_declaration( retval );
  retval->get_type()->get_base_type()->set_declaration( retval );

  return retval;
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_string_decl(){
  IIRScram_TypeDeclaration *retval = init_type_decl( "string", 0 );  
  IIRScram_ScalarTypeDefinition *pos_type = dynamic_cast<IIRScram_ScalarTypeDefinition *>(get_positive_type());
  IIRScram_TypeDefinition *char_type = dynamic_cast<IIRScram_TypeDefinition *>(get_character_type());
  ASSERT( pos_type != 0 );
  ASSERT( char_type != 0 );
  IIRScram_ArraySubtypeDefinition *string_type = 
    dynamic_cast<IIRScram_ArraySubtypeDefinition *>(init_unconstrained_array_type( pos_type,
                                                                                   char_type,
                                                                                   retval ));
  string_type->_get_design_file()->set_parser(fake_parser);
  string_type->_get_design_file()->set_standard_package(this);
  retval->set_type( string_type );

  return retval;
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_bit_vector_decl(){
  IIRScram_TypeDeclaration *retval = init_type_decl( "bit_vector", 0 );  
  IIR_ArraySubtypeDefinition *bit_vector_type 
    = init_unconstrained_array_type( dynamic_cast<IIRScram_ScalarTypeDefinition *>(get_natural_type()),
                                     dynamic_cast<IIRScram_TypeDefinition *>(get_bit_type()),
                                     retval );

  dynamic_cast<IIRScram_ArraySubtypeDefinition *>(bit_vector_type)->_get_design_file()->set_parser(fake_parser);
  bit_vector_type->get_design_file()->set_standard_package(this);

  retval->set_type( bit_vector_type );
  return retval;
}

IIRScram_PhysicalSubtypeDefinition *
ScramStandardPackage::init_time_type(){
  struct unit units[] = {
    { "ps",  1000, "fs" },
    { "ns",  1000, "ps" },
    { "us",  1000, "ns" },
    { "ms",  1000, "us" },
    { "sec", 1000, "ms" },
    { "min", 60,   "sec" },
    { "hr",  60,   "min" },
    { 0, 0, 0 }
  };

  return init_physical_type( (int)STD_INT_MIN(), (int)STD_INT_MAX(), (char *)"fs", units );
}

IIRScram_SubtypeDeclaration *
ScramStandardPackage::init_delay_length_decl(){
  IIRScram_SubtypeDeclaration *retval = init_subtype_decl( "delay_length", init_delay_length_type() );

  retval->_get_subtype()->set_declaration( retval );
  retval->_get_subtype()->_get_base_type()->set_declaration( retval );

  return retval;
}

IIRScram_PhysicalSubtypeDefinition *
ScramStandardPackage::init_delay_length_type(){
  IIRScram_PhysicalSubtypeDefinition *retval = new IIRScram_PhysicalSubtypeDefinition();
  retval->set_base_type( get_time_type()->get_base_type() );

  IIRScram_FloatingPointLiteral64 *left = IIRScram_FloatingPointLiteral64::get_value( 0.0 );
  left->_set_design_file( dynamic_cast<IIRScram_DesignFile *>(get_design_file()) );
  retval->set_left( left );
  retval->set_right( get_time_type()->get_right() );
  retval->set_direction( get_true_literal() );
    
  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);
  retval->set_type_mark( get_time_type() );

  return retval;
}

IIRScram_AttributeDeclaration *
ScramStandardPackage::init_foreign_decl(){
  IIRScram_AttributeDeclaration *retval;

  retval = new IIRScram_AttributeDeclaration();
  retval->set_declarator( IIRBase_Identifier::get( "foreign", strlen("foreign"), scram_plugin_class_factory::instance()) );
  retval->set_subtype( get_string_type() );

  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

IIRScram_FunctionDeclaration *
ScramStandardPackage::init_now_decl(){
  IIRScram_FunctionDeclaration *retval;

  retval = new IIRScram_FunctionDeclaration();
  retval->set_declarator( IIRBase_Identifier::get( "now", strlen( "now" ), scram_plugin_class_factory::instance()) );
  retval->set_return_type( get_delay_length_type() );
  retval->set_pure( IIR_IMPURE_FUNCTION );
  
  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

IIRScram_TypeDeclaration *
ScramStandardPackage::init_type_decl( char *id, IIRScram_TypeDefinition *subtype ){
  ASSERT( id != NULL );

  IIRScram_TypeDeclaration *retval = new IIRScram_TypeDeclaration();
  retval->set_declarator( IIRBase_Identifier::get( (IIR_Char *)id, strlen( id ), scram_plugin_class_factory::instance()) );
  retval->set_type( dynamic_cast<IIR_TypeDefinition *>(subtype) );
  if( subtype != NULL ){
    subtype->set_declaration( retval );
    subtype->get_base_type()->set_declaration( retval );
  }

  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

IIRScram_SubtypeDeclaration *
ScramStandardPackage::init_subtype_decl( char *id, IIRScram_TypeDefinition *subtype ){
  ASSERT( id != NULL );
  ASSERT( subtype != NULL );

  IIRScram_SubtypeDeclaration *retval = new IIRScram_SubtypeDeclaration();
  retval->set_declarator( IIRBase_Identifier::get( id, strlen( id ), scram_plugin_class_factory::instance()) );
  retval->set_subtype( subtype );

  subtype->set_declaration( retval );
  subtype->get_base_type()->set_declaration( retval );

  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

IIRScram_EnumerationLiteralList *
ScramStandardPackage::build_literal_list( const char *const literals[] ){
  IIRScram_EnumerationLiteralList *retval = new IIRScram_EnumerationLiteralList();

  int i;
  for( i = 0; literals[i] != 0; i++ ){
    IIR_TextLiteral *literal_declarator;
    if( literals[i][0] == '\'' ){
      literal_declarator = IIRScram_CharacterLiteral::get( (char*)literals[i], strlen( literals[i] ) );
    }
    else{
      literal_declarator = IIRBase_Identifier::get( (char*)literals[i], strlen( literals[i] ), scram_plugin_class_factory::instance());
    }

    IIRScram_EnumerationLiteral *lit = new IIRScram_EnumerationLiteral();
    set_locator_info( lit );
    lit->set_declarator( literal_declarator );
    lit->set_position( IIRScram_IntegerLiteral32::get( i ) );
    set_locator_info( lit->get_position() );
    lit->_get_design_file()->set_parser(fake_parser);
    lit->_get_design_file()->set_standard_package(this);
    retval->append( lit );
  }

  return retval;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_enumeration_type( const char *const literals[] ){
  IIRScram_EnumerationSubtypeDefinition *retval = NULL;
  
  IIRScram_EnumerationLiteralList *list = build_literal_list( literals );
  retval = init_enumeration_type( list );

  return retval;
}

IIRScram_EnumerationSubtypeDefinition *
ScramStandardPackage::init_enumeration_type( IIRScram_EnumerationLiteralList *list ){
  IIRScram_EnumerationSubtypeDefinition         *retval = NULL;
  IIRScram_TypeDeclaration                      *fake = new IIRScram_TypeDeclaration();

  set_locator_info( fake );
  fake->_get_design_file()->set_parser(fake_parser);
  fake->_get_design_file()->set_standard_package(this);
  retval = IIRScram_EnumerationTypeDefinition::_construct_new_type( list, fake, fake->_get_design_file() );
  delete fake;

  return retval;
}

IIRScram_IntegerSubtypeDefinition *
ScramStandardPackage::init_integer_type( int left_bound, 
                                         int right_bound ){
  IIRScram_IntegerSubtypeDefinition *retval = 0;

  IIRScram_IntegerLiteral32 *left = dynamic_cast<IIRScram_IntegerLiteral32 *>(IIRScram_IntegerLiteral32::get( left_bound ));
  IIRScram_IntegerLiteral32 *right = dynamic_cast<IIRScram_IntegerLiteral32 *>(IIRScram_IntegerLiteral32::get( right_bound ));

  IIRScram_RangeTypeDefinition *temp = new IIRScram_RangeTypeDefinition();


  temp->set_left( left );
  temp->set_right( right );
  temp->set_direction( get_true_literal() );
  set_locator_info( temp->get_left() );
  set_locator_info( temp->get_direction() );
  set_locator_info( temp->get_right() );
  set_locator_info( temp );
  temp->_get_design_file()->set_parser(fake_parser);
  left->_set_design_file( dynamic_cast<IIRScram_DesignFile *>(get_design_file()));
  right->_set_design_file( dynamic_cast<IIRScram_DesignFile *>(get_design_file()) );

  retval = IIRScram_IntegerTypeDefinition::_construct_new_type( temp, 0, temp->_get_design_file() );
  retval->_get_design_file()->set_standard_package(this);

  delete temp;

  return retval;
}

IIRScram_FloatingSubtypeDefinition *
ScramStandardPackage::init_real_type( double left_bound, double right_bound ){
  IIRScram_FloatingSubtypeDefinition *retval = 0;

  IIRScram_FloatingPointLiteral64 *left = IIRScram_FloatingPointLiteral64::get_value( left_bound );
  IIRScram_FloatingPointLiteral64 *right = IIRScram_FloatingPointLiteral64::get_value( right_bound );

  left->_set_design_file( dynamic_cast<IIRScram_DesignFile *>(get_design_file()) );
  right->_set_design_file( dynamic_cast<IIRScram_DesignFile *>(get_design_file()) );

  IIRScram_RangeTypeDefinition *temp = new IIRScram_RangeTypeDefinition();
  temp->set_left( left );
  temp->set_right( right );
  temp->set_direction( get_true_literal() );
  set_locator_info( temp );
  temp->_get_design_file()->set_parser(fake_parser);
  temp->_get_design_file()->set_standard_package(this);

  retval = IIRScram_FloatingTypeDefinition::_construct_new_type( temp, 0, temp->_get_design_file() );

  delete temp;
  
  return retval;
}

IIRScram_PhysicalSubtypeDefinition *
ScramStandardPackage::init_physical_type( int left_bound, 
                                          int right_bound, 
                                          char *base_unit_string, 
                                          struct unit units[] ){

  IIRScram_PhysicalTypeDefinition *base_type = new IIRScram_PhysicalTypeDefinition();
  IIRScram_PhysicalSubtypeDefinition *retval = new IIRScram_PhysicalSubtypeDefinition();

  IIRScram_IntegerLiteral32 *left = dynamic_cast<IIRScram_IntegerLiteral32 *>(IIRScram_IntegerLiteral32::get( left_bound ));
  IIRScram_IntegerLiteral32 *right = dynamic_cast<IIRScram_IntegerLiteral32 *>(IIRScram_IntegerLiteral32::get( right_bound ));
  left->set_subtype( retval );
  right->set_subtype( retval );

  retval->set_base_type( base_type );
  retval->set_left( left );
  retval->set_right( right );
  retval->set_direction( get_true_literal() );

  base_type->set_left( left );
  base_type->set_right( left );
  base_type->set_direction( get_true_literal() );

  set_locator_info( retval->get_left() );
  set_locator_info( retval->get_direction() );
  set_locator_info( retval->get_right() );
  set_locator_info( retval );
  set_locator_info( base_type->get_left() );
  set_locator_info( base_type->get_direction() );
  set_locator_info( base_type->get_right());
  set_locator_info( base_type );

  base_type->_get_design_file()->set_parser(fake_parser);
  base_type->_get_design_file()->set_standard_package(this);
  IIRScram_PhysicalUnit *base_unit = new IIRScram_PhysicalUnit();
  set_locator_info( base_unit );

  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);
  base_unit->_get_design_file()->set_parser(fake_parser);
  base_unit->_get_design_file()->set_standard_package(this);

  base_unit->set_declarator( IIRBase_Identifier::get( base_unit_string, strlen(base_unit_string), scram_plugin_class_factory::instance()));
  base_unit->set_subtype( retval );

  IIRScram_IntegerLiteral32 *unity =
    dynamic_cast<IIRScram_IntegerLiteral32 *>(IIRScram_IntegerLiteral32::get( 1 ));
  set_locator_info( unity );
  base_unit->set_multiplier( unity );
  unity->set_subtype( retval );
  base_type->set_primary_unit( base_unit );

  IIRScram_PhysicalUnit *current_unit = NULL;
  int i = 0;
  while( units[i].unit_name != 0 ){
    current_unit = new IIRScram_PhysicalUnit();
    set_locator_info( current_unit );
    current_unit->_get_design_file()->set_parser(fake_parser);
    current_unit->_get_design_file()->set_standard_package(this);
  
    current_unit->set_declarator( IIRBase_Identifier::get( units[i].unit_name, 
                                                           strlen( units[i].unit_name ),
                                                           scram_plugin_class_factory::instance()) );

    IIRScram_PhysicalLiteral *multiplier = new IIRScram_PhysicalLiteral();
    set_locator_info( multiplier );
    multiplier->_get_design_file()->set_parser(fake_parser);
    multiplier->_get_design_file()->set_standard_package(this);
    multiplier->set_abstract_literal( IIRScram_IntegerLiteral32::get( units[i].multiplier ) );
    set_locator_info( multiplier->get_abstract_literal() );
    multiplier->set_unit_name( find_unit( units[i].base_unit, retval ) );
    multiplier->set_subtype( retval );
    current_unit->set_multiplier( multiplier );

    // Set subtypes of the current unit/multiplier.
    current_unit->set_subtype( retval );
    ASSERT( current_unit->get_multiplier() != NULL &&
	    current_unit->get_multiplier()->get_kind() == IIR_PHYSICAL_LITERAL );
    (dynamic_cast<IIR_PhysicalLiteral *>(current_unit->get_multiplier()))->set_subtype( retval );

    base_type->get_units()->append( current_unit );
    i++;
  }

  return retval;
}

IIRScram_ArraySubtypeDefinition *
ScramStandardPackage::init_unconstrained_array_type( IIRScram_ScalarTypeDefinition *index_type,
						     IIRScram_TypeDefinition *element_type,
						     IIRScram_TypeDeclaration *type_decl ){
  IIRScram_ArraySubtypeDefinition *retval;
  IIRScram_RangeTypeDefinition *empty_range = new IIRScram_RangeTypeDefinition();

  set_locator_info( empty_range );
  empty_range->set_base_type( index_type->get_base_type() );

  empty_range->_get_design_file()->set_parser(fake_parser);
  empty_range->_get_design_file()->set_standard_package(this);

  IIRScram_ScalarTypeDefinition *unconstrained_index =
    dynamic_cast<IIRScram_ScalarTypeDefinition *>(index_type->_construct_new_subtype( 0, empty_range ));
  // So, we the subtype constructed we're done with this.
  delete empty_range;
  unconstrained_index->set_type_mark( index_type );

  retval = dynamic_cast<IIRScram_ArraySubtypeDefinition*>(
    IIRScram_ArrayTypeDefinition::_construct_unconstrained( unconstrained_index, element_type, type_decl ));
  set_locator_info( retval );

  return retval;
}

void
ScramStandardPackage::set_locator_info( IIR *that ){
  that->set_base_info( get_design_file(), 0, 0, 0 );
}

IIRScram_PhysicalUnit *
ScramStandardPackage::find_unit( char *name, IIRScram_PhysicalSubtypeDefinition *physical_type ) {
  IIRScram_PhysicalUnit *retval = 0;

  IIRScram_PhysicalUnit *current = dynamic_cast<IIRScram_PhysicalUnit *>(physical_type->get_units()->first());
  while( current != NULL ){
    if( IIRBase_TextLiteral::cmp( current->_get_declarator(), name ) == 0 ){
      retval = current;
      break;
    }
    current = dynamic_cast<IIRScram_PhysicalUnit *>(physical_type->get_units()->successor( current ));
  }

  if( retval == NULL ){
    // We had better check the primary unit!
    if( IIRBase_TextLiteral::cmp( physical_type->_get_primary_unit()->_get_declarator(), name ) == 0 ){
      retval = physical_type->_get_primary_unit();
    }
  }

  return retval;
}

IIRScram_LibraryDeclaration *
ScramStandardPackage::init_std_decl(){
  IIRScram_LibraryDeclaration *retval = new IIRScram_LibraryDeclaration();
  retval->set_declarator( IIRBase_Identifier::get( "std", strlen("std"), scram_plugin_class_factory::instance() ) );
  set_locator_info( retval );
  retval->_get_design_file()->set_parser(fake_parser);
  retval->_get_design_file()->set_standard_package(this);

  return retval;
}

StandardPackage *
ScramStandardPackage::init_std_standard(){
  StandardPackage *retval = this;
  set_locator_info( retval );

  return retval;
}

IIRScram_AccessSubtypeDefinition *
ScramStandardPackage::init_null_type(){
  IIRScram_AccessSubtypeDefinition *retval =
    IIRScram_AccessTypeDefinition::_construct_new_type( NULL, NULL, dynamic_cast<IIRScram_DesignFile *>(get_design_file()) );

  set_locator_info( retval );
  retval->_set_design_file(dynamic_cast<IIRScram_DesignFile *>(get_design_file()));

  return retval;
}

StandardPackage *
ScramStandardPackage::get_std_standard_decl(){
  static StandardPackage *std_standard = init_std_standard();
  return std_standard;
}
