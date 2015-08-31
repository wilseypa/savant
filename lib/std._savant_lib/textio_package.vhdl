package textio is

-- type definitions for text i/o

type line is access string;
type text is file of string;
type side is (right, left);
subtype width is natural;

-- standard text files

file input:  text open read_mode is  "stdin";
file output: text open write_mode is "stdout";

-- input routines for standard types

procedure readline(variable f: in text; l: inout line);

procedure read(l: inout line; value: out bit;         good: out boolean);
procedure read(l: inout line; value: out bit);         

procedure read(l: inout line; value: out bit_vector;  good: out boolean);
procedure read(l: inout line; value: out bit_vector);

procedure read(l: inout line; value: out boolean;     good: out boolean);
procedure read(l: inout line; value: out boolean);    

procedure read(l: inout line; value: out character;   good: out boolean);
procedure read(l: inout line; value: out character); 

procedure read(l: inout line; value: out integer;     good: out boolean);
procedure read(l: inout line; value: out integer);   

procedure read(l: inout line; value: out real;        good: out boolean);
procedure read(l: inout line; value: out real);      

procedure read(l: inout line; value: out string;      good: out boolean);
procedure read(l: inout line; value: out string);    

procedure read(l: inout line; value: out time;        good: out boolean);
procedure read(l: inout line; value: out time);      

-- output routines for standard types

procedure writeline(f: out text; l: inout line);
   
procedure write(l: inout line; value: in bit;
                justified: in side := right; field: in width := 0);

procedure write(l: inout line; value: in bit_vector;
                justified: in side := right; field: in width := 0);

procedure write(l: inout line; value: in boolean;
                justified: in side := right; field: in width := 0);

procedure write(l: inout line; value: in character;
                justified: in side := right; field: in width := 0);

procedure write(l: inout line; value: in integer;
                justified: in side := right; field: in width := 0);

procedure write(l: inout line; value: in real;
                justified: in side := right; field: in width := 0;
                digits: in natural := 0);

procedure write(l: inout line; value: in string;
                justified: in side := right; field: in width := 0);

procedure write(l: inout line; value: in time;
                justified: in side := right; field: in width := 0;
                unit: in time := ns);

-- file position predicate

-- function endfile(f: in text) return boolean;

end textio;
