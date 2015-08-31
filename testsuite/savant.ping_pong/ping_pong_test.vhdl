
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

library pingpong;
use pingpong.ping_pong_pkg.all;
use std.textio.all;

entity ping_pong_test is
  
end ping_pong_test;


architecture tester of ping_pong_test is

  signal p1in, p1p2, p2p3, p3p4, p4p5, p5out : ball;
  signal finished : boolean := false;
  
  component ping_pong
    port (input  : in  ball; output : out ball);
  end component;

  for all: ping_pong use entity pingpong.ping_pong(ping_pong_arch);

  begin
  
    p1: component ping_pong port map (input => p1in, output => p1p2);
    p2: component ping_pong port map (input => p1p2, output => p2p3);
    p3: component ping_pong port map (input => p2p3, output => p3p4);
    p4: component ping_pong port map (input => p3p4, output => p4p5);
    p5: component ping_pong port map (input => p4p5, output => p5out);

  doit: process
  begin
    for i in 1 to 100 loop
      p1in <= 0;
      wait for 2 fs;
      p1in <= 1;
      wait for 2 fs;
    end loop;

    finished <= true;
    wait;
  end process doit;

  count: process( p5out, finished )
    variable ball_count : integer := 0;
    variable output_line : line;
  begin  -- process
    if finished = true and finished'event then
      write( output_line, string'("ball_count = ") );
      write( output_line, ball_count );
      writeline( output, output_line );
    elsif p5out = 1 and p5out'event then
      ball_count := ball_count + 1;
    end if;
  end process;
  
end tester;
