package standard is

type boolean is (false, true);

type bit is ('0', '1');

type integer is range -2147483648 to +2147483647;

type character is 
  ( NUL,  SOH,  STX,  ETX,  EOT,  ENQ,  ACK,  BEL,
    BS,   HT,   LF,   VT,   FF,   CR,   SO,   SI,
    DLE,  DC1,  DC2,  DC3,  DC4,  NAK,  SYN,  ETB,
    CAN,  EM,   SUB,  ESC,  FSP,  GSP,  RSP,  USP, 
    ' ',  '!',  '"',  '#',  '$',  '%',  '&',  ''',
    '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
    '0',  '1',  '2',  '3',  '4',  '5',  '6',  '7',
    '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    '@',  'A',  'B',  'C',  'D',  'E',  'F',  'G',
    'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
    'P',  'Q',  'R',  'S',  'T',  'U',  'V',  'W',
    'X',  'Y',  'Z',  '[',  '\',  ']',  '^',  '_',
    '`',  'a',  'b',  'c',  'd',  'e',  'f',  'g',
    'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
    'p',  'q',  'r',  's',  't',  'u',  'v',  'w',
    'x',  'y',  'z',  '{',  '|',  '}',  '~',  DEL,
    C128, C129, C130, C131, C132, C133, C134, C135,
    C136, C137, C138, C139, C140, C141, C142, C143,
    C144, C145, C146, C147, C148, C149, C150, C151,
    C152, C153, C154, C155, C156, C157, C158, C159,
    ' ',  '¡',  '¢',  '£',  '¤',  '¥',  '¦',  '§', 
    '¨',  '©',  'ª',  '«',  '¬',  '­',  '®',  '¯', 
    '°',  '±',  '²',  '³',  '´',  'µ',  '¶',  '·', 
    '¸',  '¹',  'º',  '»',  '¼',  '½',  '¾',  '¿', 
    'À',  'Á',  'Â',  'Ã',  'Ä',  'Å',  'Æ',  'Ç', 
    'È',  'É',  'Ê',  'Ë',  'Ì',  'Í',  'Î',  'Ï', 
    'Ð',  'Ñ',  'Ò',  'Ó',  'Ô',  'Õ',  'Ö',  '×', 
    'Ø',  'Ù',  'Ú',  'Û',  'Ü',  'Ý',  'Þ',  'ß',
    'à',  'á',  'â',  'ã',  'ä',  'å',  'æ',  'ç',
    'è',  'é',  'ê',  'ë',  'ì',  'í',  'î',  'ï', 
    'ð',  'ñ',  'ò',  'ó',  'ô',  'õ',  'ö',  '÷',
    'ø',  'ù',  'ú',  'û',  'ü',  'ý',  'þ',  'ÿ' );

subtype positive is integer range 1 to integer'high;
type string is array ( positive range <> ) of character;

attribute foreign : string;

-- function "and" (lhs, rhs: boolean) return boolean;
-- function "or" (lhs, rhs: boolean) return boolean;
-- function "nand" (lhs, rhs: boolean) return boolean;
-- function "nor" (lhs, rhs: boolean) return boolean;
-- function "xor" (lhs, rhs: boolean) return boolean;
-- function "xnor" (lhs, rhs: boolean) return boolean;

-- function "not" (rhs: boolean) return boolean;

-- function "=" (lhs, rhs: boolean) return boolean;
-- function "/=" (lhs, rhs: boolean) return boolean;
-- function "<" (lhs, rhs: boolean) return boolean;
-- function "<=" (lhs, rhs: boolean) return boolean;
-- function ">" (lhs, rhs: boolean) return boolean;
-- function ">=" (lhs, rhs: boolean) return boolean;

-- function "and" (lhs, rhs: bit) return bit;
-- function "or" (lhs, rhs: bit) return bit;
-- function "nand" (lhs, rhs: bit) return bit;
-- function "nor" (lhs, rhs: bit) return bit;
-- function "xor" (lhs, rhs: bit) return bit;
-- function "xnor" (lhs, rhs: bit) return bit;

-- function "not" (rhs: bit) return bit;

--function "=" (lhs, rhs: bit) return boolean;
--function "/=" (lhs, rhs: bit) return boolean;
--function "<" (lhs, rhs: bit) return boolean;
--function "<=" (lhs, rhs: bit) return boolean;
--function ">" (lhs, rhs: bit) return boolean;
--function ">=" (lhs, rhs: bit) return boolean;

--function "=" (lhs, rhs: character) return boolean;
--function "/=" (lhs, rhs: character) return boolean;
--function "<" (lhs, rhs: character) return boolean;
--function "<=" (lhs, rhs: character) return boolean;
--function ">" (lhs, rhs: character) return boolean;
--function ">=" (lhs, rhs: character) return boolean;

type severity_level is (note, warning, error, failure);

--function "=" (lhs, rhs: severity_level) return boolean;
--function "/=" (lhs, rhs: severity_level) return boolean;
--function "<" (lhs, rhs: severity_level) return boolean;
--function "<=" (lhs, rhs: severity_level) return boolean;
--function ">" (lhs, rhs: severity_level) return boolean;
--function ">=" (lhs, rhs: severity_level) return boolean;

-- predefined numeric types:
type real is range -0.179769313486231e+309 to +0.179769313486231e+309;

-- function "**" (lhs : integer; rhs: integer) return integer;
-- function "**" (lhs : real; rhs: integer) return real;

-- function "=" (lhs, rhs: integer) return boolean;
-- function "/=" (lhs, rhs: integer) return boolean;
-- function "<" (lhs, rhs: integer) return boolean;
-- function "<=" (lhs, rhs: integer) return boolean;
-- function ">" (lhs, rhs: integer) return boolean;
-- function ">=" (lhs, rhs: integer) return boolean;

-- function "+" (rhs: integer) return integer;
-- function "-" (rhs: integer) return integer;
-- function "abs" (rhs: integer) return integer;

-- function "+" (lhs, rhs: integer) return integer;
-- function "-" (lhs, rhs: integer) return integer;
-- function "*" (lhs, rhs: integer) return integer;
-- function "/" (lhs, rhs: integer) return integer;
-- function "mod" (lhs, rhs: integer) return integer;
-- function "rem" (lhs, rhs: integer) return integer;

-- the actual definition is above - this appears here for unformity
-- type real is range -0.179769313486231e+309 to +0.179769313486231e+309;

-- function "=" (lhs, rhs: real) return boolean;
-- function "/=" (lhs, rhs: real) return boolean;
-- function "<" (lhs, rhs: real) return boolean;
-- function "<=" (lhs, rhs: real) return boolean;
-- function ">" (lhs, rhs: real) return boolean;
-- function ">=" (lhs, rhs: real) return boolean;
 
-- function "+" (rhs: real) return real;
-- function "-" (rhs: real) return real;
-- function "abs" (rhs: real) return real;

-- function "+" (lhs, rhs: real) return real;
-- function "-" (lhs, rhs: real) return real;
-- function "*" (lhs, rhs: real) return real;
--function "/" (lhs, rhs: real) return real;
-- function "mod" (lhs, rhs: real) return real;
-- function "rem" (lhs, rhs: real) return real;

-- predefined type time:

--type time is range -9223372036854775807 to +9223372036854775807
type time is range -2147483648 to +2147483647
  units
    fs;                -- femtosecond 
    ps  = 1000 fs;     -- picosecond 
    ns  = 1000 ps;     -- nanosecond 
    us  = 1000 ns;     -- microsecond 
    ms  = 1000 us;     -- millisecond 
    sec = 1000 ms;     -- second 
    min =   60 sec;    -- minute
    hr  =   60 min;    -- hour
  end units;

-- function "=" (lhs, rhs: time) return boolean;
-- function "/=" (lhs, rhs: time) return boolean;
-- function "<" (lhs, rhs: time) return boolean;
-- function "<=" (lhs, rhs: time) return boolean;
-- function ">" (lhs, rhs: time) return boolean;
-- function ">=" (lhs, rhs: time) return boolean;

-- function "+" (rhs: time) return time;
-- function "-" (rhs: time) return time;
-- function "abs" (rhs: time) return time;

-- function "+" (lhs, rhs: time) return time;
-- function "-" (lhs, rhs: time) return time;

-- function "*" (lhs : time; rhs: time) return time;
-- function "*" (lhs : time; rhs: integer) return time;
-- function "*" (lhs : time; rhs: real) return time;
-- function "*" (lhs : integer; rhs: time) return time;

-- function "/" (lhs : real; rhs: real) return time;
-- function "/" (lhs, rhs: time) return integer;

subtype delay_length is time range 0 to time'high;

-- function that returns the current simulation time:

impure function now return time;

-- predefined numeric subtypes:

subtype natural is integer range 0 to integer'high;


-- predefined array types:
-- defined earlier
-- type string is array ( positive range <> ) of character;

-- function "=" (lhs, rhs: string) return boolean;
-- function "/=" (lhs, rhs: string) return boolean;
-- function "<" (lhs, rhs: string) return boolean;
-- function "<=" (lhs, rhs: string) return boolean;
-- function ">" (lhs, rhs: string) return boolean;
-- function ">=" (lhs, rhs: string) return boolean;

-- function "&" ( lhs : string ; rhs : string ) return string;
-- function "&" ( lhs : string ; rhs : character ) return string;
-- function "&" ( lhs : character ; rhs : string ) return string;
-- function "&" ( lhs : character ; rhs : character ) return string;

type bit_vector is array ( natural range <> ) of bit;

-- function "and" (lhs, rhs: bit_vector) return bit_vector;
-- function "or" (lhs, rhs: bit_vector) return bit_vector;
-- function "nand" (lhs, rhs: bit_vector) return bit_vector;
-- function "nor" (lhs, rhs: bit_vector) return bit_vector;
-- function "xor" (lhs, rhs: bit_vector) return bit_vector;
-- function "xnor" (lhs, rhs: bit_vector) return bit_vector;

-- function "not" (rhs: bit_vector) return bit_vector;

-- function "sll" (lhs: bit_vector; rhs: integer) return bit_vector;
-- function "slr" (lhs: bit_vector; rhs: integer) return bit_vector;
-- function "sla" (lhs: bit_vector; rhs: integer) return bit_vector;
-- function "sra" (lhs: bit_vector; rhs: integer) return bit_vector;
-- function "rol" (lhs: bit_vector; rhs: integer) return bit_vector;
-- function "ror" (lhs: bit_vector; rhs: integer) return bit_vector;

-- function "=" (lhs, rhs: bit_vector) return boolean;
-- function "/=" (lhs, rhs: bit_vector) return boolean;
-- function "<" (lhs, rhs: bit_vector) return boolean;
-- function "<=" (lhs, rhs: bit_vector) return boolean;
-- function ">" (lhs, rhs: bit_vector) return boolean;
-- function ">=" (lhs, rhs: bit_vector) return boolean;

-- function "&" ( lhs : bit_vector ; rhs : bit_vector ) return bit_vector;
-- function "&" ( lhs : bit_vector ; rhs : bit ) return bit_vector;
-- function "&" ( lhs : bit ; rhs : bit_vector ) return bit_vector;
-- function "&" ( lhs : bit ; rhs : bit ) return bit_vector;

-- the predefined type for opening files

type file_open_kind is (
	read_mode,	-- resulting access is read-only
	write_mode,     -- resulting access is write-only
	append_mode     -- resulting access is write-only; information
	);		-- is appended to the end of the existing file.

-- function "=" (lhs, rhs: file_open_kind) return boolean;
-- function "/=" (lhs, rhs: file_open_kind) return boolean;
-- function "<" (lhs, rhs: file_open_kind) return boolean;
-- function "<=" (lhs, rhs: file_open_kind) return boolean;
-- function ">" (lhs, rhs: file_open_kind) return boolean;
-- function ">=" (lhs, rhs: file_open_kind) return boolean;

type file_open_status is (
	open_kind,	-- file open was successful
	status_error,   -- file object was already open
	name_error,	-- external file not found or inaccessible
	mode_error	-- could not open file with requested access
	);		-- mode

-- function "=" (lhs, rhs: file_open_status) return boolean;
-- function "/=" (lhs, rhs: file_open_status) return boolean;
-- function "<" (lhs, rhs: file_open_status) return boolean;
-- function "<=" (lhs, rhs: file_open_status) return boolean;
-- function ">" (lhs, rhs: file_open_status) return boolean;
-- function ">=" (lhs, rhs: file_open_status) return boolean;

end standard;
