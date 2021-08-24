// dump out neopixel RGB LED values

option=persist
println <pre>

for 0;{leds};1
 $c = LED({i})
 $g = ($c % 65536 / 255)
 $r = ($c / 65536)
 $b = ($c % 256)
 if ({i} % 4) < 1
   print \t
 fi
 
  if ({i} % 28) < 1
   println \t
 fi
 
 println {i}: [$r,$g,$b]
next
    
    