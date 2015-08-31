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

#include <iostream>
#include <fstream>
#include "XmlFile.hh"

using std::ofstream;
using std::ios;
using std::endl;

XmlFile::XmlFile() {
}

XmlFile::~XmlFile() {
}

void
XmlFile::addNode(const string tag, const string content, bool closeElement ) {
  string element = "";
  
  // Create the XML version of the node
  element += getIndentString();
  element += "<" + tag + ">";
  if (content != "") 
    element += content;

  if (closeElement)
    element += "</" + tag + ">";

  // Add the node to
  document.push_back(element);
}

void
XmlFile::openScope(const string tag, const string content) {
  // Create the XML version of the node
  addNode(tag, content, false);

  // Add the new scope to the list
  scopeStack.push_back(tag);
}

void
XmlFile::closeScope() {
  // Get the current top of the stack
  string curScope = scopeStack.back();

  // Remove it from the stack
  scopeStack.pop_back();

  // Add the close to the file
  string scopeClose = getIndentString();
  scopeClose += "</" + curScope + ">";
  document.push_back(scopeClose);
}

string
XmlFile::getIndentString() const {
  int           indentSize = scopeStack.size();
  string        indentStr = "";

  // Create the indentation
  for (int i = 0; i <= indentSize; i++) {
    indentStr += "  ";
  }

  return indentStr;
}

void
XmlFile::publishDocument(const string fileName) {
  ofstream      outputFile;

  // Open the file, using the passed in filename
  outputFile.open(fileName.c_str(), ios::out);

  // Add the XML initialization strings to the document
  outputFile << "<?xml version=\"1.0\"?>" << endl;
  outputFile << "<!DOCTYPE VHDLDoc>" << endl;  
  outputFile << "<VHDLDoc>" << endl;

  // Output the contents from the VHDL file
  for (list<string>::iterator iter = document.begin(); iter != document.end(); iter++) {
    outputFile << *iter << endl;    
  }
  
  // Close the document tag
  outputFile << "</VHDLDoc>" << endl;

  // All done save the file
  outputFile.close();
}
