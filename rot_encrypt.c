#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this is a file that will do rotational encryption

char encrypt(char *phrase, float key); //function prototype that will eventually encrypt something hopefully

int main()
{    
    //introducing variables
    char phrase[206]; 
    float key;

    //getting the phrase
    printf("enter a phrase to encode: \n");     //prompts phrase to be put in by user
    scanf("%s", phrase);                        //scans the phrase from the user
    
    //allows user to choose a shifting value, the 'key'
    printf("enter a key to shift by: \n");
    scanf("%f", &key);
        
    //encrypting and printing the encrypted phrase
    printf("the encryption is:\n");
    encrypt(phrase, key);    //encoding function
    printf(" \n");      //gives new line afterwards
    
    return 0;
}

char encrypt(char *phrase, float key) // encoding function definition 
{
    char i=0;
    while(phrase[i] != 0)
    {
        phrase[i] = phrase[i] + key;    //shifts it by the key
        printf("%c", phrase[i]);
        i++;
    }
}
