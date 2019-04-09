#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char *phrase); //function prototype that will eventually encrypt something

int main()
{    
    //introducing variables
    char encoded; 
    char phrase[1024]='HELLO'; 
    int key=6;
    
    //getting the phrase
    printf("enter a phrase to encode: \n");     //prompts phrase to be put in by user
    scanf("%s", phrase);                        //scans the phrase from the user
    
    //allows user to choose a shifting value, the 'key'
    printf("enter a key to shift by: \n");
    scanf("%d", &key);
        
    //encrypting and printing the encrypted phrase
    printf("the encryption is:\n");
    encrypt(phrase);    //encoding function
    printf(" \n");      //gives new line afterwards
    
    return 0;
}

char encrypt(char *phrase) // encoding function definition 
{
    char i=0;
    int key;
    while(phrase[i] != NULL)
    {
        phrase[i]=phrase[i]+key;    //shifts it by the key
        printf("%c", phrase[i]);
        i++;
    }
}
