
-- Copyright (C) 2001 Clifton Labs, Inc

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

-- Author: Philip A. Wilsey	philip.wilsey@ieee.org

-- $Author: paw $
-- $Revision: 1.1.1.1 $

-- ------------------------------------------------------------------------
--
-- $Id: ping_pong.vhdl,v 1.1.1.1 2001/11/12 15:09:53 paw Exp $
--
-- ------------------------------------------------------------------------

library pingPong;
use pingpong.ping_pong_pkg.all;
use std.textio.all;

entity ping_pong is
  port (input : in ball; output : out ball);
end ping_pong;

architecture ping_pong_arch of ping_pong is

begin

  catch: process(input)

  begin

    output <= input after 1 fs;
	   
  end process catch;

end ping_pong_arch;
