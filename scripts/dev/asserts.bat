// assert testing
option persist
sub setx{
  $x= 999
}

start 

$x = 2
assert  ($x = 2) -> var assign literal

$x = +3
assert  ($x = 5) -> var increment literal

$x = {timer}
assert  ($x > 0) -> var assign template

$x = (2 + 5)
assert  ($x = 7) -> var assign expression

$x = (+ 1, 2, 3)
assert  ($x = 6) -> var assign lisp expression

$x = MAX(2, 3)
assert  ($x = 3) -> var assign MAX fn expression $x

$x = MIN(2, 1)
assert  ($x = 1) -> var assign MIN fn expression $x

$x = $x
assert  ($x > 0) -> var assign self

$x = $zoz
assert  ($x = 0) -> var assign non-existent var $x

$x = fasdf
assert  ($x = 0) -> var assign garbage

$x = [11,22,33][1]
assert  ($x = 22) -> var assign normal array

$x = [&2;112233][1]
assert  ($x = 22) -> var assign fixed array $x

$x =  [&|;11|22|33][1]
assert  ($x = 22) -> var assign custom delim array $x

store=dan=22
assert  ({&dan} = 22) ->var store set and get

gosub setx
assert  ($x = 999) -> var assign from sub routine
