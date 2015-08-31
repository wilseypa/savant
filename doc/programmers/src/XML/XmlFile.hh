// Copyright (c) 2004 The University of Cincinnati.  
// All rights reserved.
// 
// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
// 
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.
// 
// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.
// 
//--------------------------------------------------------------------------

#include <vector>
#include <string>
#include <list>

using std::list;
using std::string;
using std::vector;

/**  This is the helper class for generating an XML file from
     the VHDL file parsed by scram. */
class XmlFile {
public:
  XmlFile();
  ~XmlFile();

  /** Writes the XML document out to disk. */
  void publishDocument(const string fileName);

  //@{
  /** Functions for adding information to the XML document */
  /** Adds a new "leaf" node */
  void addNode(const string tag, const string content = "", bool closeElement = true);

  /** Adds a new trunk node.  This opens a tag, and leaves it open. */
  void openScope(const string tag, const string content = "");
  /** Closes a trunk node.  It closes the last tag we opened. */
  void closeScope();
  //@}

private:
  /** Creates indent string.  Returns a string with the correct number of white space. */
  string                getIndentString() const;

  list<string>          document;
  vector<string>        scopeStack;
};
