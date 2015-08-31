#!/usr/bin/perl -w
#  This script is designed to read through the headers in the 
# IIRBase directory, and create a default tree walk for a plugin

########################################################
# These variables will need to be adjusted by the user #
########################################################

#   Name of plugin ex: IIRScram, Tyvis, etc.  This will be used to name 
# files, and classes.  Ex: IIRScram_DesignFile, class IIRScram_DesignFile
$Name = "XML";

# Root of new project
$RootDir = "/work/savant_plugin_tutorial";

# Location of the savant source files
$SavantSrc = "/work/savant";

#  Function signature.  This is the function declaration that will be added
# to the headers and source files for the walk.  By using a signature, the
# plugin writer can specify what gets passed into the function.
$functionSig = "xmlGeneration(XmlFile &file)";

# Return type for the function
$functionType = "void";

#  Function call.  Used then the function should be called for whatever reason
$functionCall = "xmlGeneration(file)"; 

#  Headers associated with the function
@headers = ( "\"XmlFile.hh\"" );

# Forward definitions associated with the function
@forwardDefs = ( "XmlFile" );

#################################################################
# Code - do NOT modify anything below this line

# Location of the plugin
$pluginDir = "$RootDir/src/$Name";

use File::Path;
use English;

# Verify the plugin has already been created
if (!-d $pluginDir) {
   die "Unable to find plugin directory.  Make sure that the directory variable (\$pluginDir) has been set correctly, and that the plugin has been created\n";
}

# Define some of the controling variables
$IIRBaseDir = "$SavantSrc\/src\/aire\/iir\/IIRBase";

# Define subroutines
sub insertLine($\@);
sub createFunction();
sub getVarType($);
sub getVarName($);
sub addForwardDefs(\@);

# Open the log
open LOGFILE, "> $pluginDir\/create_walk.log";

# Open the directory for a list of files
opendir BASEDIR, $IIRBaseDir or die "Unable to get file list";

print "Processing.....\n";
# For each header file in the list, read through it, and get it's vars
foreach $fileName (grep /hh$/, readdir BASEDIR) {

   open INFILE, "$IIRBaseDir\/$fileName" or die "Unable to open input file $IIRBaseDir\/$fileName\n";

   print LOGFILE "#########################################\n";
   print LOGFILE "### Parsing file: $fileName\n";
   print LOGFILE "#########################################\n";

   $className = "";
   while (<INFILE>) {
      if (/class\s+(\w+)\s*:\s*public\s+virtual/) {
	 $className = $1;
         print "Undefined class name in file $fileName\n" if (!defined $className);
	 print LOGFILE "Found class: $className\n";         

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
                     print LOGFILE "Found a variable: $_\n";
                     /.*(IIR.*);( |\t)*$/;                  
                     $posVar = $MATCH;
               
                     print LOGFILE "Refined var is: $posVar\n";

                     push @vars, $posVar;
                  }
	       }
	    }
            $_ = <INFILE>;
         }
      }
   }

   close INFILE;

   $pluginFileName = $fileName;
   $pluginFileName =~ s/IIRBase(_)?/$Name/g;

   #   If we found vars we want update the plugin class
   # otherwise we want to continue on to the next file
   if ((!defined @vars) || (scalar(@vars) <= 0)) {
      $msg = "No vars found for $className, no code will be generated for this node\n";
      print LOGFILE $msg;
      next;
   }

   print "  $pluginFileName\n";
   open INFILE, "$pluginDir\/$pluginFileName" or die "Unable to open $pluginDir\/$pluginFileName";
   print LOGFILE "########\n## Insert Override Function\n########\n";

   # We need to add in the overriding function declaration into the header file
   @fileBuf = <INFILE>;

   # Add the forward defs if any
   addForwardDefs(@fileBuf);

   insertLine("  $functionType $functionSig;\n", @fileBuf);

   # Write the rest to the file
   open OUTFILE, "> $pluginDir\/$pluginFileName";
   print OUTFILE @fileBuf;
   
   close INFILE;
   close OUTFILE;
   undef @fileBuf;

   # We need to add the overriding function to the source file
   $pluginSourceFileName = $pluginFileName;
   $pluginSourceFileName =~ s/\.hh/\.cc/g;
   open INFILE, "$pluginDir\/$pluginSourceFileName" or die "Unable to open $pluginDir\/$pluginSourceFileName\n";

   @fileBuf = <INFILE>;

   $function = createFunction();

   print LOGFILE "Added new function:\n$function\n";

   push @fileBuf, $function;

   # Add the headers
   $headers = "";

   # First user designated ones
   foreach $header (@headers) {
      $headers .= "#include $header\n";
   }

   # Now the headers associated with vars
   foreach $var (@vars) {
      $varType = getVarType($var);
      $headers .= "#include \"${varType}.hh\"\n";
   }

   $bInsertedHeaders = 0;
   for ($index = 0; $index < scalar(@fileBuf); $index++) {
      # Find the beginning of the header defs
      if ($fileBuf[$index] =~ /#include/) {
         #Find the end, or a gap
         until ($fileBuf[$index] !~ /#include/) {
            splice @fileBuf, $index, 0, $headers;
            $bInsertedHeaders = 1;
            last;
         }
      }
      last if ($bInsertedHeaders);
   }         

   # Output the results
   open OUTFILE, "> $pluginDir\/$pluginSourceFileName" or die "Unable to open $pluginDir\/$pluginSourceFileName\n";
   print OUTFILE @fileBuf;

   # reset the vars
   undef @vars;
   undef @fileBuf;

   close INFILE;
   close OUTFILE;
}


# Special case of the base class needing an additional variable & default function
print "  $Name.hh\n";
open INFILE, "$pluginDir\/${Name}.hh" or die "Unable to open $pluginDir\/${Name}.hh";
@fileBuf = <INFILE>;
close INFILE;
insertLine("\n\n  virtual ${functionType} ${functionSig};\n", @fileBuf);
insertLine("\n  bool bVisited;\n", @fileBuf);
addForwardDefs(@fileBuf);
open OUTFILE, "> $pluginDir\/${Name}.hh" or die "Unable to open $pluginDir\/${Name}.hh";
print OUTFILE @fileBuf;
undef @fileBuf;

# Special case of the base class needing the bVisited var initialized
print "  $Name.cc\n";
open INFILE, "$pluginDir\/${Name}.cc" or die "Unable to open $pluginDir\/${Name}.cc";
@fileBuf = <INFILE>;
close INFILE;
# Search for ctor
for ($i = 0; $i < scalar (@fileBuf); $i++) {
   if ($fileBuf[$i] =~ /${Name}::${Name}/) {
      # Replace the existing ctor with a new one with the var initialization
      splice @fileBuf, $i, 1, "${Name}::${Name}() : bVisited(false) {}\n";
      last;
   }
}
push @fileBuf, "${functionType}\n${Name}::${functionSig} {}\n";
open OUTFILE, "> $pluginDir\/${Name}.cc" or die "Unable to open $pluginDir\/${Name}.cc";
print OUTFILE @fileBuf;
undef @fileBuf;

# Special case of creating walk for list base class
open INFILE, "$pluginDir\/${Name}List.hh" or die "Unable to open $pluginDir\/${Name}List.hh\n";
@fileBuf = <INFILE>;
close INFILE;
insertLine("\n  $functionType $functionSig;\n", @fileBuf);
addForwardDefs(@fileBuf);
open OUTFILE, "> $pluginDir\/${Name}List.hh" or die "Unable to open $pluginDir\/${Name}List.hh\n";
print OUTFILE @fileBuf;
close OUTFILE;
undef @fileBuf;

open INFILE, "$pluginDir\/${Name}List.cc" or die "Unable to open $pluginDir\/${Name}List.cc\n";
@fileBuf = <INFILE>;
close INFILE;
$indent = "  ";
$func  = ""; 
$func .= "\n${functionType}\n";
$func .= "${Name}List::${functionSig} \{\n";
$func .= "${indent}if (!bVisited) {\n";
$func .= "${indent}${indent}for (XML *ptr = dynamic_cast<XML *>(first()); ptr != NULL; ptr = dynamic_cast<XML *>(successor(ptr))) {\n";
$func .= "${indent}${indent}${indent}ptr->${functionCall};\n";
$func .= "${indent}${indent}}\n";
$func .= "${indent}}\n";
$func .= "}\n";
push @fileBuf, $func;
open OUTFILE, "> $pluginDir\/${Name}List.cc" or die "Unable to open $pluginDir\/${Name}List.cc\n";
print OUTFILE @fileBuf;
close OUTFILE;


sub createFunction() {  
   local ($indent, $func);

   # Determine the class we're modifying
   $pluginClassName = $className;
   $pluginClassName =~ s/IIRBase(_)?/$Name/g;

   # Create the overriding function
   $indent = "  ";
   $func .= "\n${functionType}\n";
   $func .= "${pluginClassName}::${functionSig} \{\n";
   $func .= "${indent}if (!bVisited) {\n";
   $func .= "${indent}${indent}// Process the node itself\n";
   $func .= "${indent}${indent}${Name}::${functionCall};\n\n";

   if (scalar(@vars) > 0) {
      $func .= "${indent}${indent}// Process the variables\n";

      foreach $var (@vars) {
         next if ($var !~/\*/);

         # Seperate the type from the variable name
         $varType = getVarType($var);
         $varName = getVarName($var);

         # Create the function call
         $func .= "${indent}${indent}_get_${varName}()->${functionCall};\n";
      }
   }

   $func .= "${indent}}\n";
   $func .= "}\n";

   return $func;
}

# Attempts to insert a list of stuff before the 'protected' or 'private' security accessors
sub insertLine($\@) {
   local ($line, $bufref) = @_;
   local ($index);

   # Find the first instance of protected declaration
   for ($index = 0; $index < scalar(@$bufref); $index++) {
      if ($$bufref[$index] =~ /\s*protected\s*:\s*$/) {
         # Created accessor functions
         splice @$bufref, $index - 1, 0, $line;
         print LOGFILE "Found an existing protected accessor at line: $index\n";
         return;
      }
   }

   # If we didn't find 'protected' accessor the
   # first instance of protected declaration
   for ($index = 0; $index < scalar(@$bufref); $index++) {
      if ($$bufref[$index] =~ /\s*private\s*:\s*$/) {
         # Created accessor functions
         splice @$bufref, $index - 1, 0, $line;
         print LOGFILE "Found an existing private accessor at line: $index\n";
         return;
      }
   }

   # If we didn't find either accessor declaration,
   # add the function at the end of the class
   for ($index = 0; $index < @$bufref; $index++) {
      # Check for the end of the class
      if ($$bufref[$index] =~ /\};/) { 
         # insert the accessors
         splice @$bufref, $index, 0, $line;
         return;
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

sub addForwardDefs(\@) {
   local ($fileBufRef) = @_;

   $forwardDefList = "";
   if (scalar(@forwardDefs) > 0) {
      # Create the actual forward defs from list
      foreach $forwardDef (@forwardDefs) {
         $forwardDefList .= "class $forwardDef;\n";
      }

      # Add them into the file buffer
      for ($i = 0; $i < scalar(@$fileBufRef); $i++) {
         if ($$fileBufRef[$i] =~ /\s*class/) {
            splice @$fileBufRef, $i, 0, $forwardDefList;
            last;
         }
      }
   }
}
