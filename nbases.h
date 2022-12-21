#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/* 'nbases - number bases conversions': 

'nbases' is a library that provides basics number bases 
conversions. I've written this library, previosuly, in 
python. And then, I aslo decided to write this library 
in C. This library consists of two part. First is some 
methods which checks, prepares and converts given values. 
These are:

+ remove_char()
+ is_proper()
+ get_pow()
+ str_to_num()
+ clamper()
+ num_to_char()
+ hex_chars()
+ num_to_str()
+ hex_to_num()

Second is the main methods provides the basics number
base conversions including:

+ dec_to_bin()      (decimal to binary)
+ dec_to_oct()      (decimal to octal)
+ dec_to_hex()      (decimal to hexadecimal)
+ bin_to_dec()      (binary to decimal)
+ bin_to_oct()      (binary to octal)
+ bin_to_hex()      (binary to hexadecimal)
+ oct_to_dec()      (octal to decimal)
+ oct_to_bin()      (octal to binary)
+ oct_to_hex()      (octal to hexadecimal)
+ hex_to_dec()      (hexadecimal to decimal)
+ hex_to_bin()      (hexadecimal to binary)
+ hex_to_oct()      (hexadecimal to octal)

Also, you can inspect the same library written in Python.

DON'T FORGET: 
-------------
The biggest number is 2**30 which can be calculated correctly. 
The smallest number is 2**-30 which can be calculated correctly.

*/

// the biggest values
#define MAX_LEN 128
#define MAX_POW_BIN 25   // pow(2, 30)
#define MAX_POW_OCT 25   // pow(8, 15)
#define MAX_POW_DEC 15    // pow(10, 10)
#define MAX_POW_HEX 12     // pow(16, 5)

// number bases characters for four number base system.
char BINARY[]  = {'0', '1', '.'};
char OCTAL[]   = {'0', '1', '2', '3', 
                  '4', '5', '6', '7', '.'};
char DECIMAL[] = {'0', '1', '2', '3', '4', '5', 
                  '6', '7', '8', '9', '.'};
char HEX[]     = {'0', '1', '2', '3', '4', 
                  '5', '6', '7', '8', '9',
                  'A', 'B', 'C', 'D', 'E', 'F', 
                  'a', 'b', 'c', 'd','e', 'f', '.'};

// Helper Methods:
// ---------------

void remove_char(char* string, char element) {
   // removes a char from given 'string' value.
   int i, j;
   int lenght = strlen(string);
   // loops all chars in the 'string'.
   for (i=0; i<lenght; i++) {
      // finds '.' chars.
      if (string[i] == element) {
         for (j=i; j<lenght; j++) string[j] = string[j+1];
         lenght --; i--;
      }
   }
}

int is_proper(char* value, char nbase) {
   // returns 1, if given 'value' is in proper number
   // base system. Otherwise, returns 0.
   int wrong = 0;
   int points = 0;
   bool is_neg = false;
   // determines given 'value' is negative or not.
   if (value[0] == '-') { 
      remove_char(value, value[0]); 
      is_neg = true;
   }
   if (value[0] == '+') remove_char(value, value[0]);
   // inspects 'points' and its positions.
   for (int i=0; i<strlen(value); i++) {
      if (value[i] == '.') points ++;
   }
   if (points > 1) return 0;
   if (value[0] == '.') return 0;
   if (value[strlen(value)-1] == '.') return 0;
   // right now, inspects 'nbase' and its conditions.
   if (nbase == 'd' || nbase == 'D') {
      for (int i=0; i<strlen(value); i++) {
         for (int j=0; j<11; j++) {
            if (value[i] != DECIMAL[j]) wrong ++;
         }
      }
      // checks out the results
      if (strlen(value) * 11 - strlen(value) == wrong) return 1;
      else return 0;
   }
   else if (nbase == 'b' || nbase == 'B') {
      for (int i=0; i<strlen(value); i++) {
         for (int j=0; j<3; j++) {
            if (value[i] != BINARY[j]) wrong ++;
         }
      }
      // checks out the results
      if (strlen(value) * 3 - strlen(value) == wrong) return 1;
      else return 0;
   }
   else if (nbase == 'o' || nbase == 'O') {
      for (int i=0; i<strlen(value); i++) {
         for (int j=0; j<9; j++) {
            if (value[i] != OCTAL[j]) wrong ++;
         }
      }
      // checks out the results
      if (strlen(value) * 9 - strlen(value) == wrong) return 1;
      else return 0;
   }
   else if (nbase == 'h' || nbase == 'H') {
      for (int i=0; i<strlen(value); i++) {
         for (int j=0; j<23; j++) {
            if (value[i] != HEX[j]) wrong ++;
         }
      }
      // checks out the results
      if (strlen(value) * 23 - strlen(value) == wrong) return 1;
      else return 0;
   }
   else return 0;
}

float get_pow(int x, int y) {
   /* Actually, there is a pow  operation in 'math.h' package. 
   But, I can not use it in linux ubuntu distrubition. So,
   I defined a simple pow operation. */
   
   float result = 1;
   // these are shorthand result.
   if (x == 0 && y != 0) return 0;
   if (y == 0 && x != 0) return 1;
   // there are four possible situations.
   if (y > 0) {
      while (1) {result = result * x; y --; if (y == 0) break;}
   }
   else {
      while (1) {result = result / x; y ++; if (y == 0) break;}
   }

   return result;
}

float str_to_num(char* value) {
   // converts given 'value' from string to float.
   float decimal = 0;
   float number;
   int index = -1;
   bool is_frac = false;
   // if there is, finds point index in 'value'.
   for (int i=0; i<strlen(value); i++) { index ++;
   if (value[i] == '.') {is_frac = true; break;}}
   // removes '.' char.
   remove_char(value, '.');
   // converts chars to integer.
   for (int i=0; i<strlen(value); i++) {
      int limit = strlen(value) - 1 - i;
      decimal += (value[i] - '0') * get_pow(10, limit);
   }
   // considers place of point.
   if (is_frac == true) {
      int divison = strlen(value) - index;
      number = decimal / (float) get_pow(10, divison);
   } else number = decimal;

   return number;
}

char* clamper(char* string) {
   // clamps given 'string' between 'start' and 'finish'.
   char str[MAX_LEN];
   int start = -1;
   int finish = strlen(string);
   bool is_point = false;
   // finds start index.
   for (int i=0; i<strlen(string); i++) {
      start ++; if (string[i] != '0') break;
   }
   // finds point, if given number has fraction. 
   for (int i=0; i<strlen(string); i++) {
      if (string[i] == '.') { is_point = true; break; }
   }
   if (is_point == true) {
      // finds end index.
      for (int i=1; i<strlen(string); i++) {
      int limit = strlen(string) - i; finish --;
      if (string[limit] != '0') break;
      }
   }
   // right, now, clamps the given 'string'.
   for (int i=0; i<strlen(string); i++) {
      if (i >= start && finish >= i) str[i-start] = string[i];
   }
   // returns the clapped 'string'.
   char* clapped = str; return clapped;
}

char num_to_char(int number) {
   // converts 'number' to char.
   char converted[MAX_LEN];
   // uses 'sprintf'.
   sprintf(converted, "%d", number);

   return converted[0];
}

char hex_chars(float number, float pow) {
   // converts hexadecimal chars to 'A', 'B', 'C', 'D', 'E',
   // 'F' or char numbers in order.
   int biggest = (int) (number / get_pow(16, pow));
   // writes consitions.
   if (biggest == 10) return 'A';
   else if (biggest == 11) return 'B';
   else if (biggest == 12) return 'C';
   else if (biggest == 13) return 'D';
   else if (biggest == 14) return 'E';
   else if (biggest == 15) return 'F';
   else return num_to_char(biggest);
}

char* num_to_str(float number) {
   // converts 'number' to char.
   char converted[MAX_LEN];
   // uses 'sprintf'.
   sprintf(converted, "%f", number);

   char* string = converted; return string;
}

float hex_to_num(char element) {
   // returns hexadecimal chars to number.
   float number;
   // writes consitions.
   if (element == 'A' || element == 'a') return 10.0;
   else if (element == 'B' || element == 'b') return 11.0;
   else if (element == 'C' || element == 'c') return 12.0;
   else if (element == 'D' || element == 'd') return 13.0;
   else if (element == 'E' || element == 'e') return 14.0;
   else if (element == 'F' || element == 'f') return 15.0;
   else return number = (element - '0');
}


// Main Methods:
// -------------

char* dec_to_bin(char* decimal) {
   // checks out given decimal is in right base system.
   if (is_proper(decimal, 'd') == 0) return "inconsistent decimal";
   // converts given decimal to binary.
   int max_pow = MAX_POW_BIN;
   int min_pow = - (MAX_POW_BIN + 1);
   float number = str_to_num(decimal);
   char binary[MAX_LEN];
   int index = 0;

   while (true) {
      // decreases number until correct value comes.
      if (get_pow(2, max_pow) > number) binary[index] = '0';
      else {
         binary[index] = '1';
         number = number - get_pow(2, max_pow); 
      }
      // updates these variables and then breaks up the loop.
      max_pow --; index ++; if (max_pow < 0) break;
   }
   // if given decimal has fraction, repeats same loop.
   if (number != 0.0) {
      // adds up '.' char and updates variable.
      binary[index] = '.'; index ++;
   
      while (true) {
         // decreases number until correct value comes.
         if (get_pow(2, max_pow) <= number) {
            binary[index] = '1';
            number = number - get_pow(2, max_pow);
         } else binary[index] = '0';
         // updates these variables and breaks up the loop.
         index ++; max_pow --; if (max_pow == min_pow) break;
      }
   }
   char* bin = clamper(binary); return bin;
}

char* dec_to_oct(char* decimal) {
   // checks out given decimal is in right base system.
   if (is_proper(decimal, 'd') == 0) return "inconsistent decimal";
   // converts given decimal to octal.
   int max_pow = MAX_POW_OCT;
   int min_pow = - (MAX_POW_OCT + 1);
   float number = str_to_num(decimal);
   char octal[MAX_LEN];
   int index = 0;

   while (true) {
      // decreases number until correct value comes.
      if (get_pow(8, max_pow) > number) octal[index] = '0';
      else {
         // finds biggest number in given 'number'.
         int biggest = (int) (number / get_pow(8, max_pow));
         char big_char = num_to_char(biggest);
         // adds up it onto 'octal' string.
         octal[index] = big_char;
         number = number - (get_pow(8, max_pow) * biggest); 
      }
      // updates variables and then breaks up the loop
      max_pow --; index ++; if (max_pow < 0) break;
   }
   // if given decimal has fraction, repeats same loop.
   if (number != 0.0) {
      // adds up '.' char and updates variables.
      octal[index] = '.'; index ++;

      while (true) {
         // decreases number until correct value comes.
         if (get_pow(8, max_pow) <= number) {
            // finds biggest number in given 'number'.
            int biggest2 = (int) (number / get_pow(8, max_pow));
            char big_char2 = num_to_char(biggest2);
            // adds up it onto 'octal' string.
            octal[index] = big_char2;
            number = number - (get_pow(8, max_pow) * biggest2);
         } else octal[index] = '0';
         // updates these variables and then breaks up the loop.
         index ++; max_pow --; if (max_pow == min_pow) break;
      }
   }
   char* oct = clamper(octal); return oct;
}

char* dec_to_hex(char* decimal) {
   // checks out given decimal is in right base system.
   if (is_proper(decimal, 'd') == 0) return "inconsistent decimal";
   // converts given decimal to hexadecimal.
   int max_pow = MAX_POW_HEX;
   int min_pow = - (MAX_POW_HEX + 1);
   float number = str_to_num(decimal);
   char hex[MAX_LEN];
   int index = 0;

   while (true) {
      // decreases number until correct value comes.
      if (get_pow(16, max_pow) > number) hex[index] = '0';
      else {
         // finds biggest number in given 'number'.
         int biggest = (int) (number / get_pow(16, max_pow));
         // adds up it onto 'hex' string.
         hex[index] = hex_chars(number, max_pow);
         number = number - (get_pow(16, max_pow) * biggest); 
      }
      // updates these variables and the breaks up the loop.
      max_pow --; index ++; if (max_pow < 0) break;
   }
   // if given decimal has fraction, repeats same loop.
   if (number != 0.0) {
      // adds up '.' char and update variable.
      hex[index] = '.'; index ++;
      
      while (true) {
         // decreases number until correct value comes.
         if (get_pow(16, max_pow) <= number) {
            // finds biggest number in given 'number'.
            int biggest2 = (int) (number / get_pow(16, max_pow));
            // adds up it onto 'hex' string.
            hex[index] = hex_chars(number, max_pow);
            number = number - (get_pow(16, max_pow) * biggest2);
         } else hex[index] = '0';
         // updates these variables and the breaks up the loop.
         index ++; max_pow --; if (max_pow == min_pow) break;
      }
   }
   char* hexadecimal = clamper(hex); return hexadecimal;
}  

char* bin_to_dec(char* binary) {
   // checks out given binary is in right base system.
   if (is_proper(binary, 'b') == 0) return "inconsistent binary";
   // general variables.
   char part1[MAX_LEN];
   char part2[MAX_LEN];
   bool is_frac = false;
   int index = -1;
   float decimal = 0;
   // determines given binary has fraction or not.
   for (int i=0; i<strlen(binary); i++) {
      // counts index of point.
      index ++;
      if (binary[i] == '.') {is_frac = true; break;}
   }
   // if given binary has not fraction, converts directly.
   if (is_frac == false) {
      // loops the 'binary'.
      int pow = strlen(binary)-1;
      for (int i=0; i<strlen(binary); i++) {
         decimal += (binary[i] - '0') * get_pow(2, pow); pow --;
      }
   }
   // if given binary has fraction, seperates it, 
   if (is_frac == true) {
      // fills in 'part1' string.
      for (int i=0; i<index; i++) part1[i] = binary[i];
      // fills in 'part2' string.
      for (int i=index+1; i<=strlen(binary); i++) {
         int limit = i - (index+1); part2[limit] = binary[i];
      }
      // and then converts to decimal.
      int pow = strlen(part1)-1;
      // converts for 'part1'.
      for (int i=0; i<strlen(part1); i++) {
         decimal += (part1[i] - '0') * get_pow(2, pow); pow --;
      }
      int pow2 = -1;
      // converts for 'part2'.
      for (int i=0; i<strlen(part2); i++) {
         decimal += (part2[i] - '0') * get_pow(2, pow2); pow2 --;
      }
   } 
   // converts decimal number to string.
   char* string = num_to_str(decimal); 
   if (is_frac == true) return clamper(string);
   else {char* str = clamper(string); remove_char(str, '.');
   return str;
   }
}   

char* bin_to_oct(char* binary) {
   // converts binary to octal. For that, writing new  method 
   // is useless. Instead of that, can be used above methods. 
   // In two step, it can be handled.

   // 1. converts binary to decimal.
   char* decimal = bin_to_dec(binary);
   // 2. converts decimal to octal.
   char* octal = dec_to_oct(decimal);
   // lastly, returns it.
   return octal;
}    

char* bin_to_hex(char* binary) {
   // converts binary to hexadecimal. For that, writing new 
   // method is useless. Instead of that, can be used above 
   // methods. In two step, it can be handled.

   // 1. converts binary to decimal.
   char* decimal = bin_to_dec(binary);
   // 2. converts decimal to hexadecimal.
   char* hex = dec_to_hex(decimal);
   // lastly, returns it.
   return hex;

}

char* oct_to_dec(char* octal) {
   // checks out given octal is in right base system.
   if (is_proper(octal, 'o') == 0) return "inconsistent octal";
   // general variables.
   char part1[MAX_LEN];
   char part2[MAX_LEN];
   bool is_frac = false;
   int index = -1;
   float decimal = 0;
   // determines given octal has fraction or not.
   for (int i=0; i<strlen(octal); i++) {
      // counts index of point.
      index ++;
      if (octal[i] == '.') {is_frac = true; break;}
   }
   // if given octal has not fraction, converts directly.
   if (is_frac == false) {
      // loops the 'octal'.
      int pow = strlen(octal)-1;
      for (int i=0; i<strlen(octal); i++) {
         decimal += (octal[i] - '0') * get_pow(8, pow); pow --;
      }
   }
   // if given octal has fraction, seperates it,
   if (is_frac == true) {
      // fills in 'part1' string.
      for (int i=0; i<index; i++) part1[i] = octal[i];
      // fills in 'part2' string.
      for (int i=index+1; i<=strlen(octal); i++) {
         int limit = i - (index+1); part2[limit] = octal[i];
      }
      // and then converts to decimal.
      int pow = strlen(part1)-1;
      // converts for 'part1'.
      for (int i=0; i<strlen(part1); i++) {
         decimal += (part1[i] - '0') * get_pow(8, pow); pow --;
      }
      int pow2 = -1;
      // converts for 'part2'.
      for (int i=0; i<strlen(part2); i++) {
         decimal += (part2[i] - '0') * get_pow(8, pow2); pow2 --;
      }
   }
   // converts decimal number to string.
   char* string = num_to_str(decimal);
   if (is_frac == true) return clamper(string);
   else {char* str = clamper(string); remove_char(str, '.');
   return str;
   }
}   

char* oct_to_bin(char* octal) {
   // converts octal to binary. For that, writing new 
   // method is useless. Instead of that, can be used above 
   // methods. In two step, it can be handled.

   // 1. converts octal to decimal.
   char* decimal = oct_to_dec(octal);
   // 2. converts decimal to binary.
   char* binary = dec_to_bin(decimal);
   // lastly, returns it.
   return binary;
}  

char* oct_to_hex(char* octal) {
   // converts octal to hexadecimal. For that, writing new 
   // method is useless. Instead of that, can be used above 
   // methods. In two step, it can be handled.

   // 1. converts octal to decimal.
   char* decimal = oct_to_dec(octal);
   // 2. converts decimal to hexadecimal.
   char* hex = dec_to_hex(decimal);
   // lastly, returns it.
   return hex;
}  

char* hex_to_dec(char* hex) {
   // checks out given hexadecimal is in right base system.
   if (is_proper(hex, 'h') == 0) return "inconsistent hexadecimal";
   // general variables.
   char part1[MAX_LEN];
   char part2[MAX_LEN];
   bool is_frac = false;
   int index = -1;
   float decimal = 0;
   // determines given hexadecimal has fraction or not.
   for (int i=0; i<strlen(hex); i++) {
      // counts index of point.
      index ++;
      if (hex[i] == '.') {is_frac = true; break;}
   }
   // if given binary has not fraction, converts directly.
   if (is_frac == false) {
      // loops the 'binary'.
      int pow = strlen(hex)-1;
      for (int i=0; i<strlen(hex); i++) {
         decimal += hex_to_num(hex[i]) * get_pow(16, pow); pow --;
      }
   }
   // if given hexadecimal has fraction, seperates it, 
   if (is_frac == true) {
      // fills in 'part1' string.
      for (int i=0; i<index; i++) part1[i] = hex[i];
      // fills in 'part2' string.
      for (int i=index+1; i<=strlen(hex); i++) {
         int limit = i - (index+1); part2[limit] = hex[i];
      }
      // and then converts to decimal.
      int pow = strlen(part1)-1;
      // converts for 'part1'.
      for (int i=0; i<strlen(part1); i++) {
         decimal += hex_to_num(part1[i]) * get_pow(16, pow); pow --;
      }
      int pow2 = -1;
      // converts for 'part2'.
      for (int i=0; i<strlen(part2); i++) {
         decimal += hex_to_num(part2[i]) * get_pow(16, pow2); pow2 --;
      }
   }
   // converts decimal number to string.
   char* string = num_to_str(decimal);
   if (is_frac == true) return clamper(string);
   else {char* str = clamper(string); remove_char(str, '.'); 
   return str;
   }
}     

char* hex_to_bin(char* hex) {
   // converts hexadecimal to binary. For that, writing new 
   // method is useless. Instead of that, can be used above 
   // methods. In two step, it can be handled.

   // 1. converts hexadecimal to decimal.
   char* decimal = hex_to_dec(hex);
   // 2. converts decimal to binary.
   char* binary = dec_to_bin(decimal);
   // lastly, returns it.
   return binary;
}    

char* hex_to_oct(char* hex) {
   // converts hexadecimal to octal. For that, writing new 
   // method is useless. Instead of that, can be used above 
   // methods. In two step, it can be handled.

   // 1. converts hexadecimal to decimal.
   char* decimal = hex_to_dec(hex);
   // 2. converts decimal to octal.
   char* octal = dec_to_oct(decimal);
   // lastly, returns it.
   return octal;
}