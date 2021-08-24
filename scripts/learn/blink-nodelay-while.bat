// blinks led without blocking io
option persist

$state = 0
$hits = 0
pinMode 2,OUTPUT


do while($hits < 100)
  $hits=+1
  $state = (1 - $state)
  set 2, ($state * 999)
  freeze 500
loop


