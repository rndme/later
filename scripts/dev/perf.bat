// storage interface test
option persist

println time test for various operations

timer start
for 0; 100
 $x = 44
next
timer var assign to literal
// ^ maybe it could be faster if use atoi instead of Number?

for 0; 100
 $g=$x;
next
timer dupe var

for 0; 100
 $y = (1 + 2 + 3)
next
timer var assign expression

for 0; 100
 $j=[1,2,3][2]
next
timer parse array

for 0; 100
 $k=&RESPONSE.fake
next
timer lookup RESPONSE object //4887, 4700

for 0; 100
 $a = {&dan}
next
timer var assign template

for 0; 100
 log $a {&dan}
next
timer log a var and template

clear

 