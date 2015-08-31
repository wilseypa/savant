
#ifndef LANGUAGE_PROCESSING_CONTROL_HH
#define LANGUAGE_PROCESSING_CONTROL_HH

// Copyright (c) 2001 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Author: Philip A. Wilsey	philip.wilsey@ieee.org

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "savant.hh"
class ANTLRToken;

/** This class manages control information and functions to track and
    manage the input language that the scram analyzer is asked to
    recognize.  */
class language_processing_control {

public:

  /** This enumeration is the list of languages that the scram parser
      can process. */
  enum languages {VHDL_93, VHDL_AMS, VHDL_2001};

  /** Constructor
     @param lang_to_proc This parameter tells the constructor which
     language the analyzer should recognize. */
  language_processing_control(languages lang_to_proc) : 
    language_being_processed(lang_to_proc) {}

  /** Destructor; does nothing at this time. */
  ~language_processing_control() {}
  
  /** Returns true if the language to process is VHDL 93. */
  bool processing_vhdl_93();
  /** Returns true if the language to process is VHDL AMS. */
  bool processing_vhdl_ams();
  /** Returns true if the language to process is VHDL 2001. */
  bool processing_vhdl_2001();
  
  /** Report that scram sees VHDL AMS language syntax when it was
      invoked to process some other language.
      @param token The token where the VHDL AMS syntax was found.
  */
  void report_not_vhdl_ams(ANTLRToken *token);
  /** Report that scram sees VHDL 2001 language syntax when it was
      invoked to process some other language.
      @param token The token where the VHDL 2001 syntax was found.
  */
  void report_not_vhdl_2001(ANTLRToken *token);

protected:

private:

  /// Records the language to process.
  languages language_being_processed;

  /// Disable default constructor definition.
  language_processing_control() {}

};

#endif

