#!/usr/bin/perl -w

# Copyright (c) 2004-2005 Clifton Labs, Inc.
# All rights reserved.

# CLIFTON LABS MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
# OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
# PURPOSE, OR NON-INFRINGEMENT.  CLIFTON LABS SHALL NOT BE LIABLE FOR ANY
# DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
# DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

# By using or copying this Software, Licensee agrees to abide by the
# intellectual property laws, and all other applicable laws of the U.S.,
# and the terms of this license.

# You may modify, distribute, and use the software contained in this package
# under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
# June 1991. A copy of this license agreement can be found in the file
# "LGPL", distributed with this archive.
#
# --------------------------------------------------------------------------
#   This script creates a new set of files for implementing a SAVANT Scram plugin.
# This includes the AIRE nodes, class factory, plugin interface, and Makefile

use File::Path;
use File::Copy;
use English;

sub createWrapperDeclarations();
sub createWrapperFunctions();
sub getVars();
sub helpMessage();

######################
# Parse command line #
######################

for($i=0;$i<=$#ARGV;$i++){
    if($ARGV[$i] eq '-r'){
        $i++;
	if(!defined($ARGV[$i])){
	    print "Wrong use of -r parameter!\n";
	    print "Run plugin_creation.pl -h for more help.\n";
	    exit;
	}
	if(-d $ARGV[$i]){
	    $SAVANTROOT=$ARGV[$i];
	} else {
	    print "Directory ".$ARGV[$i]." does not exist.\n";
	    exit;
	}
        next;
    }
    if($ARGV[$i] eq '-n'){
        $i++;
	if(!defined($ARGV[$i])){
	    print "Wrong use of -n parameter!\n";
	    print "Run plugin_creation.pl -h for more help.\n";
	    exit;
	}
	$Name=$ARGV[$i];
        next;
    }
    if($ARGV[$i] eq '-H'){
        $i++;
	if(!defined($ARGV[$i])){
	    print "Wrong use of -H parameter!\n";
	    print "Run plugin_creation.pl -h for more help.\n";
	    exit;
	}
	if(-f $ARGV[$i]){
	    $HeaderFile=$ARGV[$i];
	} else {
	    print "Header file ".$ARGV[$i]." does not exist.\n";
	    exit;
	}
        next;
    }
    if($ARGV[$i] eq '-o'){
        $i++;
	if(!defined($ARGV[$i])){
	    print "Wrong use of -o parameter!\n";
	    print "Run plugin_creation.pl -h for more help.\n";
	    exit;
	}
	if(-d $ARGV[$i]){
	    $OutputDir=$ARGV[$i];
	} else {
	    print "Output directory ".$ARGV[$i]." does not exist.\n";
	    exit;
	}
        next;
    }
    if($ARGV[$i] eq '-h'){
	helpMessage();
        exit;
    }
    print "Argument '$ARGV[$i]' not supported. Use -h for help.\n";
    exit;
}

# Check whether the SAVANTROOT was specified. If not, check if
# environment variable SAVANTROOT exists and use it instead. Otherwise
# quit with an error message.
if(!defined($SAVANTROOT)){
    if(defined($ENV{SAVANTROOT})){
	if(-d ($ENV{SAVANTROOT})){
	    $SAVANTROOT=$ENV{SAVANTROOT};
	} else {
	    print "Directory ".$ENV{SAVANTROOT}." does not exist.\n";
	    exit;
	}
    } else {
	print "Neither -r option nor SAVANTROOT variable defined.\n\n";
	#print "Run plugin_creation.pl -h for more help.\n";
	helpMessage();
	exit;
    }
}

# Check whether the project name (Name variable) was given.
if(!defined($Name)){
    print "No project name specified (-n option).\n\n";
	#print "Run plugin_creation.pl -h for more help.\n";
	helpMessage();
	exit;
}

# Check whether a header file (HeaderFile) was specified. If not, use an empty header.
if(defined($HeaderFile)){
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
} else {
    # No header file specified
    $HeaderSource[0]="";
    $HeaderMakefile[0]="";
}

# Generate the OutputDir variable.
if(defined($OutputDir)){
    # Remove / after the last directory
    $OutputDir =~ s/\/$//;
    $OutputDir.="/$Name";
} else {
    $OutputDir="./$Name";
}


########
# Init #
########

# We read in the IIR classes to determine what to output
$InputDir   = "$SAVANTROOT/src/aire/iir/IIR";
$IIRBaseDir = "$SAVANTROOT/src/aire/iir/IIRBase";
# Create the output dir
mkpath($OutputDir);

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

   # Ruda M.: a warning was generated for =~ operator if the
   # $className = 'IIR'
   if($className ne 'IIR'){
      $newBaseClassName =~ s/IIR(_)?/IIRBase$1/g;
   } else {
      $newBaseClassName = 'IIRBase';
   }

   if (defined $derivedClass) {
      $newDerivedClassName = $derivedClass;
      $newDerivedClassName =~ s/IIR(_)?/$Name/g;
   }

   getVars();
   undef $wrapperDeclarations;
   $wrapperDeclarations = createWrapperDeclarations();
   ##########
   # Header #
   ##########
   
   #    Create the plugin class based on the class we just read.  
   #  This can be adjusted to conform to coding standards
   $newClass =  "\n";
   if (defined $derivedClass) {
      $newClass .= "#include \"savant/${newBaseClassName}.hh\"\n";
      $newClass .= "#include \"${newDerivedClassName}.hh\"\n\n";
      $newClass .= "class ${newClassName} : public virtual ${newBaseClassName}, public virtual ${newDerivedClassName} {\n";
   } else {
      # Special case for base base class
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
   $outputBuf .= join "", @HeaderSource;
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

   #  Create the source file
   $newSource =  "\n";
   $newSource .= join "", @HeaderSource;
   $newSource .= "\n";
   $newSource .= "#include \"${newClassName}.hh\"\n";
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
   close INFILE;
}

####################
# Standard Package #
####################
print "Generating StandardPackage\n";
$capsName = uc $Name;
$outputBuf  = "#ifndef ${capsName}_STANDARD_PACKAGE\n";
$outputBuf .= "#define ${capsName}_STANDARD_PACKAGE\n";
$outputBuf .= join "", @HeaderSource;
$outputBuf .= "\n#include \"savant/PluginStandardPackage.hh\"\n";

# Ruda M.: Commented out since this include does not have any effect (includes itself).
#$outputBuf .= "#include \"${Name}StandardPackage.hh\"\n\n";

$outputBuf .= "class ${Name}StandardPackage : public virtual PluginStandardPackage, public virtual ${Name}PackageDeclaration {\n";
$outputBuf .= "public:\n";
$outputBuf .= "  ${Name}StandardPackage(plugin_class_factory *factory) : PluginStandardPackage(factory) {};\n";

# Ruda M.: Added empty constructor for use in class_factory.
$outputBuf .= "  ${Name}StandardPackage() {};\n";

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
open INFILE, "$SAVANTROOT\/src\/util\/plugin_class_factory.hh";
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
$outputBuf .= join "", @HeaderSource;

# Include the plugin class factory interface
$outputBuf .= "#include \"savant/plugin_class_factory.hh\"\n";

# Ruda M.: We need to add one declaration at the beginnig of this
# class. Remove old Copyright, includes, forward defs, and class header.
while ($FactoryHeader[$i] !~ /public:/){
    $i++;
}
$i++;

# Add class opening
$lcName = lc $Name;
$outputBuf .= "class ${lcName}_plugin_class_factory : public plugin_class_factory \{\n";

# Ruda M.: Add member function instance()
$outputBuf .= "  /**\n";
$outputBuf .= "     Access the singleton object of this class.\n";
$outputBuf .= "  */\n";
$outputBuf .= "  static plugin_class_factory *instance();\n\n";

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
open INFILE, "$SAVANTROOT\/src\/aire\/iir\/IIRScram\/scram_plugin_class_factory.cc";

# Toss the copyright
while (($line = <INFILE>) !~ /#include/) {}

$outputBuf  = join "", @HeaderSource;
$outputBuf .= "\n" . $line;

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
print OUTFILE join "", @HeaderSource;
print OUTFILE "\n#include \"savant/plugin_interface.hh\"\n\n";
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
print OUTFILE join "", @HeaderSource;
print OUTFILE "\n#include \"${lcName}_plugin_interface.hh\"\n";
print OUTFILE "#include \"${lcName}_plugin_class_factory.hh\"\n";
print OUTFILE "#include \"savant/IIRBase.hh\"\n\n";
print OUTFILE "IIR*\n";
print OUTFILE "${lcName}_plugin_interface::process_tree(IIR *old_tree, int argc, char *argv[]) {\n";
print OUTFILE "  plugin_class_factory   *factory = new ${lcName}_plugin_class_factory();\n";
print OUTFILE "  IIR                    *new_tree = NULL;\n\n";
print OUTFILE "  // Transmute the AIRE tree into a new tree containing the plugin nodes\n";

# Ruda M.: transmute_tree is now convert_tree
#print OUTFILE "  new_tree = dynamic_cast<IIRBase *>(old_tree)->transmute_tree(factory);\n\n";
print OUTFILE "  new_tree = dynamic_cast<IIRBase *>(old_tree)->convert_tree(factory);\n\n";

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

###############
# Makefile.am #
###############
print "Generating Makefile\n";
open OUTFILE, "> $OutputDir\/Makefile.am";
print OUTFILE "# Process this file with automake to produce Makefile.in\n";
print OUTFILE join "", @HeaderMakefile;
print OUTFILE "\nlib_LTLIBRARIES = lib${lcName}plugin.la\n\n";
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
# configure.ac #
################
print "Generating configure.ac\n";
open OUTFILE, "> $OutputDir\/configure.ac";

open INFILE, "$SAVANTROOT\/doc\/plugin-configure.ac";
@TemplateFile = <INFILE>;
close INFILE;

$i=0;
while($TemplateFile[$i] !~ /\$Author.*\$/){
    $i++;
}
$i++;

# Add copyright notice
$outputBuf = "## Process this file with autoconf to produce a configure script.\n";
$outputBuf .= join "", @HeaderMakefile;

# Add configure.ac data
while ($i < scalar(@TemplateFile)) {
   $outputBuf .= $TemplateFile[$i++];
}

print OUTFILE "$outputBuf";
close OUTFILE;
  
#############################
# autoreconf required files #
#############################
 
# Get a copy of acinclude.m4 from the SAVANT root directory for CLUTILS, etc
copy( "$SAVANTROOT\/acinclude.m4", "$OutputDir\/acinclude.m4");

# NEWS
print "Generating NEWS\n";
open OUTFILE, "> $OutputDir\/NEWS";
close OUTFILE;

# README
print "Generating README\n";
open OUTFILE, "> $OutputDir\/README";
print OUTFILE "Requirements: gcc 3.4, g++ 3.4, automake 1.7, autoconf 2.5x, libtool\n";
print OUTFILE "To compile: autoreconf -i; ./configure; make\n";
print OUTFILE "If you want to debug the code,\n";
print OUTFILE "don't forget to set CXXFLAGS=-ggdb3 shell variable before compilation.\n";
close OUTFILE;

# AUTHORS
print "Generating AUTHORS\n";
open OUTFILE, "> $OutputDir\/AUTHORS";
close OUTFILE;

# ChangeLog
print "Generating ChangeLog\n";
open OUTFILE, "> $OutputDir\/ChangeLog";
close OUTFILE;

##############
# subroutines #
##############

sub helpMessage()
{
    $outputBuf = "Usage:  plugin_creation.pl -r <SAVANTROOT> -n <PLUGINNAME> [-H <HEADERFILE>]\n";
    $outputBuf .= "\t                   [-o <OUTPUTDIR>] [-h]\n";
    $outputBuf .= "\t-r <SAVANTROOT> - directory where savant sources are located.\n";
    $outputBuf .= "\t                  It is not required if SAVANTROOT variable is specified.\n";
    $outputBuf .= "\t-n <PLUGINNAME> - the name of the plugin being generated.\n";
    $outputBuf .= "\t-H <HEADERFILE> - a text file that will prepend all generated files\n";
    $outputBuf .= "\t                  Comment modifiers are added automatically.\n";
    $outputBuf .= "\t-o <OUTPUTDIR>  - directory where the plugin code will be generated.\n";
    $outputBuf .= "\t-h              - this message.\n";
    print $outputBuf;
}

sub createWrapperDeclarations() 
{
   local ($declarations);

   $declarations = "";
   foreach $var (grep /\*/, @vars) {

      # Seperate the type from the variable name
      $varType = $var;
      $varType =~ s/\s*(\w+)\s*(\*|\&)?\s*\w+/$1/;
      $varType =~ s/\s|;//g;
      $varType =~ s/IIR(_)?/$name/g;
      $varName = $var;
      $varName =~ s/\s*\w+\s*(\*|\&)?\s*//;
      $varName =~ s/\s|;//g;

      $declarations .= "$varType * _get_$varName();\n";
   }      

   return $declarations;
}

sub createWrapperFunctions() 
{
   local ($functions);

   $functions = "";
   foreach $var (grep /\*/, @vars) {

      # Separate the type from the variable name
      $varType = $var;
      $varType =~ s/\s*(\w+)\s*(\*|\&)?\s*\w+/$1/;
      $varType =~ s/\s|;//g;
      $varType =~ s/IIR(_)?/$name/g;
      $varName = $var;
      $varName =~ s/\s*\w+\s*(\*|\&)?\s*//;
      $varName =~ s/\s|;//g;

      $functions .= "$varType *\n";
      $functions .= "${name}::_get_$varName() {\n";
      $functions .= "  return dynamic_cast<$varType *>(get_$varName());\n";
      $functions .= "}\n";
   }      

   return $functions;
}

sub getVars() 
{
   $fileName = $className;
   $fileName =~ s/IIR/IIRBase/g;
   open INFILE, "$IIRBaseDir\/$fileName.hh" or die "Unable to open file $IIRBaseDir\/$fileName.hh\n";

   while (<INFILE>) {
      if (/class\\s+(\w+)\s*:\s*public\s+virtual\s+(\w+)/) {
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
                     print "Found a variable: $_\n";
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
