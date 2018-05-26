#include<stdio.h>
#include<string.h>
#include "roman.h"


int roman_parser(char roman_Number[]){

    //char roman_Number[1000];
    int i=0;
    int number =0;
   
   
    while(roman_Number[i]){

         if(digitValue(roman_Number[i]) >= digitValue(roman_Number[i+1]))
             number = number + digitValue(roman_Number[i]);
         else{
             number = number + (digitValue(roman_Number[i+1]) - digitValue(roman_Number[i]));
             i++;
         }
         i++;
    }
        
   
    return number;

}

int digitValue(char c){

    int value=0;

    switch(c){
         case 'I': value = 1; break;
         case 'V': value = 5; break;
         case 'X': value = 10; break;
         case 'L': value = 50; break;
         case 'C': value = 100; break;
         case 'D': value = 500; break;
         case 'M': value = 1000; break;
         case '\0': value = 0; break;
         default: value = -1; 
    }

    return value;
}
