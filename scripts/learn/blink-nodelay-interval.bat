// blinks led without blocking io
option interval=50
$state = 0

pinMode 2,OUTPUT

sub blink {
  $state=(1 - $state)
  set 2, ($state * 999)
}

start

interval blink, 500