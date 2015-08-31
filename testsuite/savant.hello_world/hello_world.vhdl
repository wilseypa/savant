
-- Copyright (C) Clifton Labs, Inc

-- CLIFTON LABS MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE
-- SUITABILITY OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT
-- NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
-- A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  CLIFTON LABS SHALL NOT BE
-- LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
-- RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
-- DERIVATIVES.

-- By using or copying this Software, Licensee agrees to abide by the
-- intellectual property laws, and all other applicable laws of the U.S.,
-- and the terms of this license.

-- You may modify, distribute, and use the software contained in this
-- package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
-- version 2, June 1991. A copy of this license agreement can be found in
-- the file "LGPL", distributed with this archive.


-- Write "Hello World!!!" to a file name results.out.

use std.textio.all;

entity hello_world is

end hello_world;

architecture hello_world of hello_world is
  
begin
  
  process is
		     
    variable output_line: LINE;
    variable message: string(1 to 14) := "Hello World!!!";
		     
    file output_file: text open WRITE_MODE is "results.out";

  begin
    
    write(output_line, message);
    writeLine(output_file, output_line);
    
    wait;
    
  end process;
  
end architecture hello_world;
