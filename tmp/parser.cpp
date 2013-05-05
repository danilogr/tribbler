#include <iostream>



/*
 All key created using this script will hold a timestamp so that can be
 used for parsing
 
 Binary functions (order is always FUNCTION KEY DESTINATION/SOURCE/VALUE
 A K V -> Append to value K to  LIST D
 T K S -> Remove top from list D and save in variable S
 P K V -> Put key K with value V
 G K D -> Get key K value and save it in variable D
 
 Unary
 I C   -> Increment variable C


 User variables: Any letter from A to N, there is automatic conversion from
 string to int and vice-versa. When a variable holds an invalid int (if
 converted from string) than the result is 0
 
 Special variables:
 T -> holds a timestamp vector for this script operation


 Target script:

 User inputs with:
 A -> global counter key 
 B -> user posted message

 
 
 * */

