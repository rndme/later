// fizzbuzz demo

option persist

for 1; 101

 if ! {i} % 15
   println FizzBuzz
   continue
 fi

 if ! {i} % 3
   println Fizz
   continue
 fi

 if ! {i} % 5
   println Buzz
   continue
 fi

 println {i}

next