#include <stdio.h>
#include "nbases.h"

int main(void) {
   
   /* nbases - number bases conversions package examples for C.

   There are two main method groups. These are 'Helper Methods'
   and 'Main Methods'. I don't care about 'Helper Methods'. Just, 
   I want to explain 'Mains Methods'.
   */ 

   /* 'dec_to_bin'

   char dec1[] = "1071";
   char dec2[] = "54.75";

   printf("1071 = %s \n", dec_to_bin(dec1)); 
   printf("54.75 =  %s \n", dec_to_bin(dec2)); 
   */

   /* 'dec_to_oct'

   char dec3[] = "1453";
   char dec4[] = "54.75";

   printf("1453 = %s \n", dec_to_oct(dec3)); 
   printf("54.75 = %s \n", dec_to_oct(dec4)); 
   */

   /* 'dec_to_hex'

   char dec5[] = "1071";
   char dec6[] = "218.625";

   printf("1071 = %s \n", dec_to_hex(dec5)); 
   printf("218.625 =  %s \n", dec_to_hex(dec6)); 
   */

   /* bin_to_dec 

   char bin1[] = "10110101101";
   char bin2[] = "110110.11";

   printf("10110101101 = %s \n", bin_to_dec(bin1)); 
   printf("11110.11 =  %s \n", bin_to_dec(bin2)); 
   */

   /* bin_to_oct 

   char bin3[] = "10110101101";
   char bin4[] = "110110.11";

   printf("10110101101 = %s \n", bin_to_oct(bin3)); 
   printf("110110.11 =  %s \n", bin_to_oct(bin4)); 
   */

   /* bin_to_hex 

   char bin5[] = "10110101101";
   char bin6[] = "110110.11";

   printf("10110101101 = %s \n", bin_to_hex(bin5)); 
   printf("110110.11 =  %s \n", bin_to_hex(bin6)); 
   */

   /* oct_to_dec 

   char oct1[] = "2057";
   char oct2[] = "332.5";

   printf("2057 = %s \n", oct_to_dec(oct1)); 
   printf("332.5 =  %s \n", oct_to_dec(oct2)); 
   */

   /* oct_to_bin 

   char oct3[] = "2057";
   char oct4[] = "332.5";

   printf("2057 = %s \n", oct_to_bin(oct3)); 
   printf("332.5 =  %s \n", oct_to_bin(oct4)); 
   */

   /* oct_to_hex 

   char oct5[] = "2057";
   char oct6[] = "332.5";

   printf("2057 = %s \n", oct_to_hex(oct5)); 
   printf("332.5 =  %s \n", oct_to_hex(oct6)); 
   */

   /* hex_to_dec

   char hex1[] = "5AD";
   char hex2[] = "36.C";

   printf("5AD = %s \n", hex_to_dec(hex1)); 
   printf("36.C =  %s \n", hex_to_dec(hex2)); 
   */

   /* hex_to_bin 

   char hex3[] = "5AD";
   char hex4[] = "36.C";

   printf("5AD = %s \n", hex_to_bin(hex3)); 
   printf("36.C =  %s \n", hex_to_bin(hex4)); 
   */

   /* hex_to_oct 

   char hex5[] = "5AD";
   char hex6[] = "36.C";

   printf("5AD = %s \n", hex_to_oct(hex5)); 
   printf("36.C =  %s \n", hex_to_oct(hex6)); 
   */


   return 0;
}