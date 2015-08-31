#!/usr/bin/perl -w

# Copyright (c) 2004 The University of Cincinnati.
# All rights reserved.
# 
# UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
# THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
# FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
# MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
# 
# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the
# U.S., and the terms of this license.
# 
# You may modify, distribute, and use the software contained in this package
# under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
# June 1991. A copy of this license agreement can be found in the file
# "LGPL", distributed with this archive.
# 
# Author: Dale E. Martin          dmartin@ece.uc.edu
# 
# --------------------------------------------------------------------------

#   This script creates a new set of files for implementing a SAVANT Scram plugin.
# This includes the AIRE nodes, class factory, plugin interface, and Makefile

########################################################
# These variables will need to be adjusted by the user #
########################################################

#   Name of plugin ex: IIRScram, Tyvis, etc.  This will be used to name 
# files, and classes.  Ex: IIRScram_DesignFile, class IIRScram_DesignFile
$Name = "XML";

# Root of new project
$RootDir = "/work/savant_plugin_tutorial";

# Location of the savant source directory
$SavantSrc = "/work/savant";

#   Name of text file containing copyright notice or any other 
# information to place at top of all the files.  If this is "" 
# the variable will be ignored.
$HeaderFile = "copyright";

#################################################################
# Code - do NOT modify anything below this line

$OutputDir = "${RootDir}\/src\/${Name}";

########
# Init #
########

use File::Path;
use File::Copy;
use English;

sub createWrapperDeclarations();
sub createWrapperFunctions();
sub getVars();
sub getVarType($);
sub getVarName($);

# We read in the IIR classes to determine what to output
$InputDir   = "$SavantSrc/src/aire/iir/IIR";
$IIRBaseDir = "$SavantSrc/src/aire/iir/IIRBase";
# Create the output dir
mkpath($OutputDir);

# Read the copyright data
@HeaderData = "\n";
if (length($HeaderFile) > 1) { 
   open COPYRIGHT, $HeaderFile or die "Unable to open copyright file!\n";
   @HeaderData = <COPYRIGHT>;   
}

# Generate C/C++ commented version
for ($i = 0; $i < scalar(@HeaderData); $i++) {
   $HeaderSource[$i] = "// $HeaderData[$i]";
}

# Generate Makefile commented version
for ($i = 0; $i < scalar(@HeaderData); $i++) {
   $HeaderMakefile[$i] = "# $HeaderData[$i]";
}

###########
# Process #
###########

# Read in the IIR files
opendir IIRDIR, $InputDir or die "Unable to get file list.";

print "Processing...\n";
foreach $filename (readdir IIRDIR) {

   # We only want to open headers that begin with IIR
   next if ($filename !~ /^IIR.*\.hh$/);

   print "   $filename\n";
   open INFILE, "$InputDir\/$filename" or die "Unable to open input file $InputDir\/$filename\n";

   undef $className;
   while (<INFILE>) {
      if (/class\s+(\w+)\s*:\s*public\s+virtual\s+(\w+)/) {
         $className = $1;
         $derivedClass = $2;
	 $_ = <INFILE>;
     } elsif (/class\s+IIR\s*\{/) {
         $className = "IIR";
         undef $derivedClass;
      }
   }
 
   # Generate new class names based on the originals
   $newClassName = $className;
   $newClassName =~ s/IIR(_)?/$Name/g;
   $newBaseClassName = $className;
   $newBaseClassName =~ s/IIR(_)?/IIRBase$1/g;
   if (defined $derivedClass) {
      $newDerivedClassName = $derivedClass;
      $newDerivedClassName =~ s/IIR(_)?/$Name/g;
   }

   getVars();
   undef $wrapperDeclarations;
   $wrapperDeclarations = createWrapperDeclarations();

   $forwardDefList = "";
   if (scalar(@vars) > 0) {
      # Create the actual forward defs from list
      foreach $var (@vars) {
         $varType = getVarType($var);
         $forwardDefList .= "class ${varType};\n";
      }
   }

   ##########
   # Header #
   ##########
   
   #    Create the plugin class based on the class we just read.  
   #  This can be adjusted to conform to coding standards
   $newClass =  "\n";
   if (defined $derivedClass) {
      $newClass .= "#include \"savant/${newBaseClassName}.hh\"\n";
      $newClass .= "#include \"${newDerivedClassName}.hh\"\n\n";
      $newClass .= "$forwardDefList\n" if ($forwardDefList ne "");
      $newClass .= "class ${newClassName} : public virtual ${newBaseClassName}, public virtual ${newDerivedClassName} {\n";
   } else {
      # Special case for the base class
      $newClass =  "\n";
      $newClass .= "#include \"savant/IIRBase.hh\"\n";
      $newClass .= "class ${newClassName} : public virtual ${newBaseClassName} {\n";
   }
   $newClass .= "public:\n";
   $newClass .= "  $newClassName();\n";
   $newClass .= "  ~$newClassName();\n";
   $newClass .= "\n";
   if (length ($wrapperDeclarations) > 0) {
      $newClass .= "  // AIRE function wrappers\n";
      $newClass .= "$wrapperDeclarations\n";
   }
   $newClass .= "};\n";
   
   #  Add the endifs and copyright notice if any
   $capsNewClass = uc $newClassName;   
   $outputBuf =  "#ifndef ${capsNewClass}_HH\n";
   $outputBuf .= "#define ${capsNewClass}_HH\n\n";
   $outputBuf .= "@HeaderSource";
   $outputBuf .= $newClass;
   $outputBuf .= "#endif\n";

   # Save the results to the file
   $outfileName = $filename;
   $outfileName =~ s/IIR(_)?/$Name/g; 
   open OUTFILE, "> $OutputDir\/$outfileName\n";
   print OUTFILE $outputBuf;
   close OUTFILE;

   ##########
   # Source #
   ##########

   # Create the wrappers, if any
   $wrapperFunctions = createWrapperFunctions();

   # Add headers for those wrappers if any
   $headerList = "";
   if (scalar(@vars) > 0) {
      # Create the actual forward defs from list
      foreach $var (@vars) {
         $varType = getVarType($var);
         $headerList .= "#include \"${varType}.hh\"\n";
      }
   }   

   #  Create the source file
   $newSource =  "\n";
   $newSource .= "@HeaderSource";
   $newSource .= "\n";
   $newSource .= "#include \"${newClassName}.hh\"\n";
   $newSource .= $headerList if ($headerList ne "");
   $newSource .= "\n";
   $newSource .= "${newClassName}::${newClassName}() {}\n";
   $newSource .= "${newClassName}::~${newClassName}() {}\n";
   $newSource .= "\n";
   $newSource .= "$wrapperFunctions";

   # Save the results to the file
   $outfileName =~ s/hh/cc/g;
   open OUTFILE, "> $OutputDir\/$outfileName";
   print OUTFILE $newSource;
   close OUTFILE;

   undef @vars;
}

####################
# Standard Package #
####################
print "Generating StandardPackage\n";
$capsName = uc $Name;
$outputBuf  = "#ifndef ${capsName}_STANDARD_PACKAGE\n";
$outputBuf .= "#define ${capsName}_STANDARD_PACKAGE\n";
$outputBuf .= "@HeaderSource\n";
$outputBuf .= "#include \"savant/PluginStandardPackage.hh\"\n";
$outputBuf .= "#include \"${Name}StandardPackage.hh\"\n\n";
$outputBuf .= "class ${Name}StandardPackage : public virtual PluginStandardPackage, public virtual ${Name}PackageDeclaration {\n";
$outputBuf .= "public:\n";
$outputBuf .= "  ${Name}StandardPackage(plugin_class_factory *factory) : PluginStandardPackage(factory) {}\n";
$outputBuf .= "};\n";
$outputBuf .= "#endif\n";
 
open OUTFILE, "> $OutputDir\/${Name}StandardPackage.hh";
print OUTFILE $outputBuf;
close OUTFILE;

#################
# Class Factory #
#################
# Header File
print "Generating Class Factory\n";
open INFILE, "$SavantSrc\/src\/util\/plugin_class_factory.hh";
@FactoryHeader = <INFILE>;
close INFILE;

# First Adjust the # defines
$i = 0;
while ($FactoryHeader[$i] !~ /PLUGIN_CLASS_FACTORY/) {
   $i++;
}
$outputBuf = "$FactoryHeader[$i++]";
$outputBuf .= $FactoryHeader[$i];
$outputBuf =~ s/PLUGIN_CLASS_FACTORY/${capsName}_PLUGIN_CLASS_FACTORY/g;

# Add copyright notice
$outputBuf .= "@HeaderSource";

# Include the plugin class factory interface
$outputBuf .= "#include \"savant/plugin_class_factory.hh\"\n";

# Toss out the old Copyright, includes, and forward defs
while ($FactoryHeader[$i] !~ /class plugin_class_factory/) {
   $i++;
}
$i++;

# Add class opening
$lcName = lc $Name;
$outputBuf .= "class ${lcName}_plugin_class_factory : public plugin_class_factory \{\n";

# Add the rest of the class to the buffer
while ($i < scalar(@FactoryHeader)) {
   $outputBuf .= $FactoryHeader[$i++];
}

# Remove the pure virtual designation from function declarations
$outputBuf =~ s/ = 0//g;

# Write the results to disk
open OUTFILE, "> $OutputDir\/${lcName}_plugin_class_factory.hh";
print OUTFILE $outputBuf;
close OUTFILE;

##############
# Source File
open INFILE, "$SavantSrc\/src\/aire\/iir\/IIRScram\/scram_plugin_class_factory.cc";

# Toss the copyright
while (($line = <INFILE>) !~ /#include/) {}

$outputBuf  = "@HeaderSource\n";
$outputBuf .= $line;

# Add the rest of the class to the buffer
while (<INFILE>) {
   $outputBuf .= $_;
}

# Replace all instances of IIRScram with the new name
$outputBuf =~ s/IIRScram(_)?/$Name/g;
$outputBuf =~ s/scram/$lcName/g;
$outputBuf =~ s/Scram/$Name/g;
$outputBuf =~ s/IRKind/savant\/IRKind/g;

open OUTFILE, "> $OutputDir\/${lcName}_plugin_class_factory.cc";
print OUTFILE $outputBuf;
close OUTFILE;

####################
# Plugin Interface #
####################
# Header
print "Generating Plugin Interface\n";
open OUTFILE, "> $OutputDir\/${lcName}_plugin_interface.hh";
print OUTFILE "#ifndef ${capsName}_PLUGIN_INTERFACE_HH\n";
print OUTFILE "#define ${capsName}_PLUGIN_INTERFACE_HH\n";
print OUTFILE "@HeaderSource\n";
print OUTFILE "#include \"savant/plugin_interface.hh\"\n\n";
print OUTFILE "class ${lcName}_plugin_interface : plugin_interface {\n";
print OUTFILE "public:\n";
print OUTFILE "  /** \@return a string indicating what the plugin does. */\n";
print OUTFILE "  const string getPluginType() const;\n\n";
print OUTFILE "  /** \@return the name of the plugin. */\n";
print OUTFILE "  const string getPluginName() const;\n\n";
print OUTFILE "  IIR *process_tree(IIR *, int, char **);\n\n";
print OUTFILE "};\n";
print OUTFILE "#endif\n";
close OUTFILE;

#########
# Source
open OUTFILE, "> $OutputDir\/${lcName}_plugin_interface.cc";
print OUTFILE "@HeaderSource\n";
print OUTFILE "#include \"${lcName}_plugin_interface.hh\"\n";
print OUTFILE "#include \"${lcName}_plugin_class_factory.hh\"\n";
print OUTFILE "#include \"savant/IIRBase.hh\"\n\n";
print OUTFILE "IIR*\n";
print OUTFILE "${lcName}_plugin_interface::process_tree(IIR *old_tree, int argc, char *argv[]) {\n";
print OUTFILE "  plugin_class_factory   *factory = new ${lcName}_plugin_class_factory();\n";
print OUTFILE "  IIR                    *new_tree = NULL;\n\n";
print OUTFILE "  // Transmute the AIRE tree into a new tree containing the plugin nodes\n";
print OUTFILE "  new_tree = dynamic_cast<IIRBase *>(old_tree)->transmute_tree(factory);\n\n";
print OUTFILE "  // TODO:  Insert plugin specific code here!\n\n";
print OUTFILE "  // Return the newly generated tree to the compiler\n";
print OUTFILE "  return new_tree;\n";
print OUTFILE "}\n\n";
print OUTFILE "/** \@return a string saying what the module is for. */\n";
print OUTFILE "const string\n";
print OUTFILE "${lcName}_plugin_interface::getPluginType() const {\n";
print OUTFILE "  return string(\"Savant AIRE Plugin\");\n";
print OUTFILE "}\n\n";
print OUTFILE "/** \@return the name of the plugin. */\n";
print OUTFILE "const string\n";
print OUTFILE "${lcName}_plugin_interface::getPluginName() const {\n";
print OUTFILE "  return string(\"${Name} Plugin\");\n";
print OUTFILE "}\n\n";
print OUTFILE "extern \"C\" {\n";
print OUTFILE "  // Used by libtool to create a new version of the module\n";
print OUTFILE "  void *allocatelib${lcName}plugin() {\n";
print OUTFILE "    return new ${lcName}_plugin_interface();\n";
print OUTFILE "  }\n";
print OUTFILE "}\n";
close OUTFILE;

############
# Makefile #
############
print "Generating Makefiles\n";
# Ancillary Makefiles
open OUTFILE, "> $RootDir\/Makefile.am";
print OUTFILE "# Process this file with automake to produce Makefile.in\n";
print OUTFILE "@HeaderMakefile\n";
print OUTFILE "SUBDIRS=src\n\n";
print OUTFILE "AM_CPPFLAGS= \@CPPFLAGS\@\n";
print OUTFILE "AM_CXXFLAGS= \@CXXFLAGS\@\n";
close OUTFILE;

open OUTFILE, "> $RootDir\/src\/Makefile.am";
print OUTFILE "# Process this file with automake to produce Makefile.in\n";
print OUTFILE "@HeaderMakefile\n";
print OUTFILE "SUBDIRS=${Name}\n";
close OUTFILE;

# Project Makefile
open OUTFILE, "> $OutputDir\/Makefile.am";
print OUTFILE "# Process this file with automake to produce Makefile.in\n";
print OUTFILE "@HeaderMakefile\n";
print OUTFILE "lib_LTLIBRARIES = lib${lcName}plugin.la\n\n";
print OUTFILE "lib${lcName}plugin_la_LD_FLAGS= \\\n";
print OUTFILE "\t-module \\\n";
print OUTFILE "\t-avoid-version \n\n";
print OUTFILE "lib${lcName}plugin_la_LIBADD = \\\n";
print OUTFILE "\t-laire \\\n";
print OUTFILE "\t-lsavantutils \\\n";
print OUTFILE "\t-lclutils \\\n";
print OUTFILE "\t-lltdl \n\n";
print OUTFILE "lib${lcName}plugin_la_SOURCES = \\\n";

# Iterate through the files in the directory, and add them to the make file list
opendir OUTPUTDIR, $OutputDir or die "Unable to open the output directory\n";
@allFiles = grep /hh|cc/, readdir OUTPUTDIR;
close OUTPUTDIR;
for ($i = 0; $i < (scalar(@allFiles) - 1); $i++) {
   print OUTFILE "\t$allFiles[$i] \\\n";
}
print OUTFILE "\t$allFiles[$i] \n";
close OUTFILE;

################
# Configure.ac #
################
print "Generating configure.ac file\n";
open OUTFILE, "> $RootDir\/configure.ac";
print OUTFILE "@HeaderMakefile\n";
print OUTFILE "AC_INIT([$Name], [1.0])\n";
print OUTFILE "AC_CONFIG_SRCDIR([src\/${Name}\/${Name}.cc])\n";
print OUTFILE "AM_INIT_AUTOMAKE\n";
print OUTFILE "AC_PREREQ(2.57)\n\n";
print OUTFILE "AM_CONFIG_HEADER( src\/${Name}\/${Name}_config\.h )\n\n";
print OUTFILE "AC_CANONICAL_HOST\n\n";
print OUTFILE "AC_LANG(C++)\n";
print OUTFILE "# Checks for programs\n";
print OUTFILE "AC_PROG_CXX\n";
print OUTFILE "AC_PROG_CXXCPP\n";
print OUTFILE "AC_PROG_INSTALL\n";
print OUTFILE "AC_PROG_LIBTOOL\n\n";
print OUTFILE "# Checks for libraries\n";
print OUTFILE "CL_LIB_CLUTILS\n\n";
print OUTFILE "# Var substitutions\n";
print OUTFILE "AC_SUBST(CPPFLAGS)\n";
print OUTFILE "AC_SUBST(CFLAGS)\n";
print OUTFILE "AC_SUBST(CXXFLAGS)\n";
print OUTFILE "AC_SUBST(LDFLAGS)\n";
print OUTFILE "AC_SUBST(LIBS)\n";
print OUTFILE "AC_SUBST(CXX)\n\n";
print OUTFILE "AC_OUTPUT( [ Makefile src\/Makefile src\/${Name}\/Makefile ] )\n\n";
print OUTFILE "rm -rf ./config.cache\n";
close OUTFILE;

# Get a copy of acinclude.m4 from the SAVANT directory
copy( "$SavantSrc\/acinclude.m4", "$RootDir\/acinclude.m4");

# Misc files required by automake
open OUTFILE, "> $RootDir\/AUTHORS\n";
print OUTFILE "";
close OUTFILE;

open OUTFILE, "> $RootDir\/README\n";
print OUTFILE "";
close OUTFILE;

open OUTFILE, "> $RootDir\/NEWS\n";
print OUTFILE "";
close OUTFILE;

open OUTFILE, "> $RootDir\/ChangeLog\n";
print OUTFILE "";
close OUTFILE;

sub createWrapperDeclarations() {
   local ($declarations);

   $declarations = "";
   foreach $var (grep /\*/, @vars) {

      # Seperate the type from the variable name
      $varType = getVarType($var);
      $varName = getVarName($var);
      $declarations .= "  $varType * _get_$varName();\n";
   }      

   return $declarations;
}

sub createWrapperFunctions() {
   local ($functions);

   $functions = "";
   foreach $var (grep /\*/, @vars) {

      # Seperate the type from the variable name
      $varType = getVarType($var);
      $varName = getVarName($var);

      $functions .= "$varType *\n";
      $functions .= "${newClassName}::_get_$varName() {\n";
      $functions .= "  return dynamic_cast<$varType *>(get_$varName());\n";
      $functions .= "}\n";
   }      

   return $functions;
}

sub getVars() {
   $fileName = $className;
   $fileName =~ s/IIR/IIRBase/g;
   open INFILE, "$IIRBaseDir\/$fileName.hh" or die "Unable to open file $IIRBaseDir\/$fileName.hh\n";

   while (<INFILE>) {
      if (/class\s+(\w+)\s*:\s*public\s+virtual\s+(\w+)/) {
	 $_ = <INFILE>;

	 # in the class definition, look for variable declarations, until we find the end '};'
	 until ((eof INFILE) or (/^\s*\};/m)) {

	    # Get a complete line of text, by reading until we hit a ';', '}', '*/', or EOF
	    until (/;| \}|\*\/|\/\/|\#\w+/) {
               $_ .= <INFILE>;
	       # Check for end of class
	       if (/^\s*\};/m) {
                  last;
	       }

	       # If this is the end of the file, break out
	       if (eof INFILE) {
		  last;
	       }
            }

            # If this isn't a function, then it's probably a variable
            if (!((/(\s*(\&|\*)*((\w+)(\*|\&)*\s+(\&|\*)*)*\w+\s*\((\s|\w|,|\d|\*|\&)*)/) and (!/\/\/|\*\/|\/\*/))) {
	       # Check for a variable declaration
	       if (/(.*\n?)(\w+\s+)*\w+\s*(\*\s*)?\w+\s*;/ and !/friend /) {

                  # Make sure it's a IIR list var
                  if (/IIR_.*List/){
                     /.*(IIR.*);( |\t)*$/;                  
                     $posVar = $MATCH;
               
                     push @vars, $posVar;
                  }
	       }
	    }
            $_ = <INFILE>;
         }
      }
   }
}
   
# Using the var declaration line, it returns the var's type
sub getVarType($) {
   local($varDeclaration) = @_;
   local($varType);
   
   $varType = $varDeclaration;
   $varType =~ s/\s*(\w+)\s*(\*|\&)?\s*\w+/$1/;
   $varType =~ s/\s|;//g;
   $varType =~ s/IIR(_)?/$Name/g;
   
   return $varType;
}

# Using the var declaration line, it returns the var's name
sub getVarName($) {
   local($var) = @_;
   local($varName);

   $varName = $var;
   $varName =~ s/\s*\w+\s*(\*|\&)?\s*//;
   $varName =~ s/\s|;//g;
   
   return $varName;
}
