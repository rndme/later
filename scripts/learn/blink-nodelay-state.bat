// blinks led without blocking io
option interval=500
define $state = 0
pinMode 2,OUTPUT

$state=(1 - $state)
set 2, ($state * 999)
