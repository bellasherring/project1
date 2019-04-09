#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//this is a file that will do rotational encryption

char encrypt(char *phrase, float key); //function prototype that will eventually encrypt something hopefully

int main()
{    
    //introducing variables
    char phrase[206]; 
    float key; //key can be between -25 and 25. 0 & 26 imply no encryption

    //getting the phrase
    printf("enter a phrase to encode in capitals: \n");     //prompts phrase to be put in by user
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
        if((phrase[i]+key)>=65 && (phrase[i]+key)<=90) //if it ends up in the capital letter range dont change it
        {
            phrase[i] = phrase[i] + key;
        }
        else if((phrase[i]+key)>90) //if it ends up above the range, take away 26 and then add the key
        {
            phrase[i] = phrase[i] - 26 + key;
        }
        else if((phrase[i]+key)<65) //if it ends up below the range, add 26 and then the key
        {
            phrase[i] = phrase[i] + 26 + key;
        }
        printf("%c", phrase[i]);
        i++;
    }
}
