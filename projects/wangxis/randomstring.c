In the testme(), it reaches printing error message under two codition: 1) a string �reset� is passed in by calling the function inputString(). 1)state=9 from series state change from 0 based on different char passed in by calling function inputChar().
I implemented inputChar() with random selection of char 32 to 126. The testme() function could easily reach state= 9 by calling this function as chance to match a char from 94 chars is pretty high. I implemented inputString() with limitation of string length to 5 and char from �e� to �t�. This still takes 10-20 second or over 4 million iterations to get desired string.  If I choose same char range as for the inputChar, it took very long time to reach the error message. It seems unnecessary for the testing.
