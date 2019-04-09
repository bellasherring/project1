#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//decoding function prototype that will decrypt something

char decrypt(char *phrase, float key);

int main()
{
    //introducing variables
    char phrase[1024]; 
    float key;
    
    //getting the phrase
    printf("enter a phrase to decode: \n");     //prompts phrase to be put in by user
    scanf("%s", phrase);                        //scans the phrase from the user
    
    //inputs the shifting value, the 'key'
    printf("enter the key it was shifted by: \n");
    scanf("%f", &key);
        
    //decrypting and printing the decrypted phrase
    printf("the decryption is:\n");
    decrypt(phrase, key);    //decoding function
    printf(" \n");      //gives new line afterwards    
    return 0;
}

//decoding function definition
char decrypt(char *phrase, float key)
{
    char i=0;
    while(phrase[i] != 0)
    {
        if((phrase[i]-key)>=65 && (phrase[i]-key)<=90) //if it is within the capital letter range and A-OK
        {
            phrase[i] = phrase[i] - key;
        }
        else if((phrase[i]-key)>90) //if it falls above the capital letter range
        {
            phrase[i] = phrase[i] - 26 - key;
        }
        else if((phrase[i]-key)<65) //if it falls below the capital letter range
        {
            phrase[i] = phrase[i] + 26 - key;
        }
        
        printf("%c", phrase[i]);    //prints each decrypted letter
        i++;
    }
}