/* NBases - Number Base Conversions

Including methods:
------------------

dec_to_bin()      (decimal to binary)
dec_to_oct()      (decimal to octal)
dec_to_hex()      (decimal to hexadecimal)
bin_to_dec()      (binary to decimal)
bin_to_oct()      (binary to octal)
bin_to_hex()      (binary to hexadecimal)
oct_to_dec()      (octal to decimal)
oct_to_bin()      (octal to binary)
oct_to_hex()      (octal to hexadecimal)
hex_to_dec()      (hexadecimal to decimal)
hex_to_bin()      (hexadecimal to binary)
hex_to_oct()      (hexadecimal to octal)
*/

// Libraries:
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Macros:
#ifndef NBASES_H
   #define NBASES_H  1
#endif

#define True  1
#define False 0

#define MAX_POW  17
#define MIN_POW  -18
#define MAX_LEN  MAX_POW + -MIN_POW + 1

// User-defined data types:
typedef unsigned short boolean;
typedef char * string;

/* --------------------------------------------------------------- */
/* ----------------------- Helper Methods ------------------------ */
/* --------------------------------------------------------------- */

/* Cut the needless digits from '__number'. */
string _cut_needless_digits_(string __number) {
   // Declare the some variables and constants.
   int first = 0, last = strlen(__number);
   // Use the heap section of RAM for cuted string.
   string cstr = malloc(sizeof(char) * strlen(__number));
   // Find the first and last indexes of '__number'.
   for (int i=0; i<strlen(__number); i++) 
      { if (__number[i] != '0') break; first ++; }
   for (int i=strlen(__number)-1; i >= 0; i--)
      { if (__number[i] != '0') break; last --; }
   // Cut the '__number' between fisrt and last.
   for (int i=first; i<last; i++)
      cstr[i-first] = __number[i];

   return cstr;
}

/* Convert 'number' to characters. */
char _num_to_char_(int __number) {
   // converts 'number' to char.
   char character[32];
   sprintf(character, "%d", __number);

   return character[0];
}

/* Convert any decimal number to hexadecimal. */
char _hex_chars_(double __number, int __pow) {
   // Find the biggest number in '__number'.
   int biggest = (int) (__number / pow(16, __pow));
   // Return the corresponding hexadecimal digits.
   if (biggest == 10) return 'A';
   else if (biggest == 11) return 'B';
   else if (biggest == 12) return 'C';
   else if (biggest == 13) return 'D';
   else if (biggest == 14) return 'E';
   else if (biggest == 15) return 'F';
   else return _num_to_char_(biggest);
}

/* Convert any hexadecimal number to decimal. */
double _hex_to_num_(char __hex) {
   // Return the corresponding decimal digits.
   if (__hex == 'A' || __hex == 'a') return 10;
   else if (__hex == 'B' || __hex == 'b') return 11;
   else if (__hex == 'C' || __hex == 'c') return 12;
   else if (__hex == 'D' || __hex == 'd') return 13;
   else if (__hex == 'E' || __hex == 'e') return 14;
   else if (__hex == 'F' || __hex == 'f') return 15;
   else return (__hex - '0');
}

/* --------------------------------------------------------------- */
/* ------------------------- Main Methods ------------------------ */
/* --------------------------------------------------------------- */

/* Convert '__decimal' to binary number. For example: 

string decimal = "54.75";
string result = dec_to_bin(decimal);
printf("%s\n", result);

110110.11
*/
string dec_to_bin(string __decimal) {
   // Convert '__decimal' to floating-point number.
   double decimal = atof(__decimal);
   // Use the heap section of RAM for creating binary.
   string binary = malloc(sizeof(char) * MAX_LEN);
   // Declate the some variables and constants.
   int index = 0, max_pow = MAX_POW, min_pow = MIN_POW;

   while (True) {
      // Find the digits corresponding to decimal.
      if (pow(2, max_pow) > decimal) binary[index] = '0';
      else binary[index] = '1', decimal -= pow(2, max_pow);
      // Update the control variables.
      max_pow --; index ++; 
      // Break up the while-loop.
      if (max_pow < 0) break;
   }
   // Sometimes, '__decimal' has fractions. For that:
   if (decimal != 0.0) {
      // Append the point to 'binary'.
      binary[index] = '.', index ++;

      while (True) {
         // Find the digits corresponding to binary.
         if (pow(2, max_pow) <= decimal)
            binary[index] = '1', 
            decimal -= pow(2, max_pow);
         else 
            binary[index] = '0';
         // Update the constrol variables again.
         index ++, max_pow --;
         // Break up the while-loop.
         if (max_pow == min_pow) break;
   }} 
   return _cut_needless_digits_(binary);
}

/* Convert '__decimal' to octal number. For example: 

string decimal = "54.75";
string result = dec_to_oct(decimal);
printf("%s\n", result);

66.6
*/
string dec_to_oct(string __decimal) {
   // Convert '__decimal' to floating-point number.
   double decimal = atof(__decimal);
   // Use the heap section of RAM for creating binary.
   string octal = malloc(sizeof(char) * MAX_LEN);
   // Declare the some variables and constants.
   int max_pow = MAX_POW, min_pow = MIN_POW;
   int index = 0, biggest;

   while (True) {
      // Find the digits corresponding to decimal.
      if (pow(8, max_pow) > decimal) octal[index] = '0';
      else {
         // Find the biggest number in 'decimal'.
         biggest = (int) (decimal / pow(8, max_pow));
         // Append the biggest char into 'octal'.
         octal[index] = _num_to_char_(biggest);
         // Decrease decimal in each iteration.
         decimal -= (pow(8, max_pow) * biggest);
      }
      // Update the control variables.
      max_pow --; index ++; 
      // Break up the while-loop.
      if (max_pow < 0) break;
   }
   // Sometimes, '__decimal' has fractions. For that:
   if (decimal != 0.0) {
      // Append the point to 'binary'.
      octal[index] = '.', index ++;

      while (True) {
         // Find the digits corresponding to octal.
         if (pow(8, max_pow) <= decimal) {
            // Find the biggest number in 'decimal'.
            biggest = (int) (decimal / pow(8, max_pow));
            // Append the biggest char into 'octal'.
            octal[index] = _num_to_char_(biggest);
            // Decrease decimal in each iteration.
            decimal -= (pow(8, max_pow) * biggest);
         }
         else octal[index] = '0';
         // Update the constrol variables again.
         index ++, max_pow --;
         // Break up the while-loop.
         if (max_pow == min_pow) break;
   }} 
   return _cut_needless_digits_(octal);
}

/* Convert '__decimal' to hexadecimal number. For example: 

string decimal = "218.625";
string result = dec_to_hex(decimal);
printf("%s\n", result);

DA.A
*/ 
string dec_to_hex(string __decimal) {
   // Convert '__decimal' to floating-point number.
   double decimal = atof(__decimal);
   // Use the heap section of RAM for creating binary.
   string hex = malloc(sizeof(char) * MAX_LEN);
   // Declare the some variables and constants.
   int max_pow = MAX_POW, min_pow = MIN_POW;
   int index = 0, biggest;

   while (True) {
      // Find the digits corresponding to decimal.
      if (pow(16, max_pow) > decimal) hex[index] = '0';
      else {
         // Find the biggest number in 'decimal'.
         biggest = (int) (decimal / pow(16, max_pow));
         // Append the biggest char into 'hex'.
         hex[index] = _hex_chars_(decimal, max_pow);
         // Decrease decimal in each iteration.
         decimal -= (pow(16, max_pow) * biggest);
      }
      // Update the control variables.
      max_pow --; index ++; 
      // Break up the while-loop.
      if (max_pow < 0) break;
   }
   // Sometimes, '__decimal' has fractions. For that:
   if (decimal != 0.0) {
      // Append the point to 'binary'.
      hex[index] = '.', index ++;

      while (True) {
         // Find the digits corresponding to octal.
         if (pow(16, max_pow) <= decimal) {
            // Find the biggest number in 'decimal'.
            biggest = (int) (decimal / pow(16, max_pow));
            // Append the biggest char into 'octal'.
            hex[index] = _hex_chars_(decimal, max_pow);
            // Decrease decimal in each iteration.
            decimal -= (pow(16, max_pow) * biggest);
         }
         else hex[index] = '0';
         // Update the constrol variables again.
         index ++, max_pow --;
         // Break up the while-loop.
         if (max_pow == min_pow) break;
   }} 
   return _cut_needless_digits_(hex);
}

/* Convert '__binary' to decimal number. For example: 

string binary = "110110.11"; // 54.75
string result = bin_to_dec(binary);
printf("%s\n", result);

54.750000
*/
string bin_to_dec(string __binary) {
   // Declare the some variables and constants.
   double decimal = 0;
   int index = 0, len;
   boolean is_frac = False;

   // Check if '__binary' is floating-point or not.
   for (int i=0; i<strlen(__binary); i++)
      if (__binary[i] == '.') { is_frac = True; break; }
      else index ++;
   // Declare the iteration limits.
   len = index - 1;
   // If '__binary' is not floating-point number:
   for (int i=0; i<index; i++) 
      decimal += (__binary[i]-'0') * pow(2, len), len--; 
   // Update the iteration limits.
   len = -1;
   // If '__binary' is floating-point number:
   if (is_frac == True) 
      for (int i=index+1; i<strlen(__binary); i++)
         decimal += (__binary[i]-'0') * pow(2, len), len--;

   // Convert the decimal to string format.
   string cdecimal = malloc(sizeof(char) * MAX_LEN);
   sprintf(cdecimal, "%f", decimal);

   return cdecimal;
}

/* Convert '__binary' to octal number. For example: 

string binary = "110110.11"; 
string result = bin_to_oct(binary);
printf("%s\n", result);

66.6
*/
string bin_to_oct(string __binary) {
   // Instead of writing new algorithm for this method, 
   // we can use methods that we defined above. Shortly:
   return dec_to_oct(bin_to_dec(__binary));
}

/* Convert '__binary' to hexadecimal number. For example: 

string binary = "110110.11"; 
string result = bin_to_hex(binary);
printf("%s\n", result);

36.C
*/
string bin_to_hex(string __binary) {
   // Instead of writing new algorithm for this method, 
   // we can use methods that we defined above. Shortly:
   return dec_to_hex(bin_to_dec(__binary));
}

/* Convert '__octal' to decimal number. For example: 

string octal = "332.5"; 
string result = oct_to_dec(octal);
printf("%s\n", result);

218.625000
*/
string oct_to_dec(string __octal) {
   // Declare the some variables and constants.
   double decimal = 0;
   int index = 0, len;
   boolean is_frac = False;

   // Check if '__octal' is floating-point or not.
   for (int i=0; i<strlen(__octal); i++)
      if (__octal[i] == '.') { is_frac = True; break; }
      else index ++;
   // Declare the iteration limits.
   len = index - 1;
   // If '__octal' is not floating-point number:
   for (int i=0; i<index; i++) 
      decimal += (__octal[i]-'0') * pow(8, len), len--; 
   // Update the iteration limits.
   len = -1;
   // If '__binary' is floating-point number:
   if (is_frac == True) 
      for (int i=index+1; i<strlen(__octal); i++)
         decimal += (__octal[i]-'0') * pow(8, len), len--;

   // Convert the decimal to string format.
   string cdecimal = malloc(sizeof(char) * MAX_LEN);
   sprintf(cdecimal, "%f", decimal);

   return cdecimal;
} 

/* Convert '__octal' to binary number. For example: 

string octal = "332.5"; 
string result = oct_to_bin(octal);
printf("%s\n", result);

11011010.101
*/
string oct_to_bin(string __octal) {
   // Instead of writing new algorithm for this method, 
   // we can use methods that we defined above. Shortly:
   return dec_to_bin(oct_to_dec(__octal));
}

/* Convert '__octal' to hexadecimal number. For example: 

string octal = "332.5"; 
string result = oct_to_hex(octal);
printf("%s\n", result);

DA.A
*/
string oct_to_hex(string __octal) {
   // Instead of writing new algorithm for this method, 
   // we can use methods that we defined above. Shortly:
   return dec_to_hex(oct_to_dec(__octal));
} 

/* Convert '__hexadecimal' to decimal number. For example: 

string hexadecimal = "36.C"; 
string result = hex_to_dec(hexadecimal);
printf("%s\n", result);

54.750000
*/
string hex_to_dec(string __hexadecimal) {
   // Declare the some variables and constants.
   double decimal = 0;
   int index = 0, len;
   boolean is_frac = False;

   // Check if '__hexadecimal' is floating-point or not.
   for (int i=0; i<strlen(__hexadecimal); i++)
      if (__hexadecimal[i] == '.') { is_frac = True; break; }
      else index ++;
   // Declare the iteration limits.
   len = index - 1;
   // If '__hexadecimal' is not floating-point number:
   for (int i=0; i<index; i++) 
      decimal += _hex_to_num_(__hexadecimal[i]) * pow(16, len), 
      len--; 
   // Update the iteration limits.
   len = -1;
   // If '__hexadecimal' is floating-point number:
   if (is_frac == True) 
      for (int i=index+1; i<strlen(__hexadecimal); i++)
         decimal += _hex_to_num_(__hexadecimal[i]) * pow(16,len),
         len--;

   // Convert the decimal to string format.
   string cdecimal = malloc(sizeof(char) * MAX_LEN);
   sprintf(cdecimal, "%f", decimal);

   return cdecimal;
}

/* Convert '__hexadecimal' to binary number. For example: 

string hexadecimal = "36.C"; 
string result = hex_to_bin(hexadecimal);
printf("%s\n", result);

110110.11
*/
string hex_to_bin(string __hexadecimal) {
   // Instead of writing new algorithm for this method, 
   // we can use methods that we defined above. Shortly:
   return dec_to_bin(hex_to_dec(__hexadecimal));
}

/* Convert '__hexadecimal' to octal number. For example: 

string hexadecimal = "36.C"; 
string result = hex_to_oct(hexadecimal);
printf("%s\n", result);

66.6
*/
string hex_to_oct(string __hexadecimal) {
   // Instead of writing new algorithm for this method, 
   // we can use methods that we defined above. Shortly:
   return dec_to_oct(hex_to_dec(__hexadecimal));
}
