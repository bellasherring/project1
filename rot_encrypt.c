#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes for each process
char encrypt(char *phrase, float key); //encryption function prototype
char decrypt(char *phrase, float key); //rotational decryption pt
//substitution encryption pt
//substitution decryption pt

//choosing which process to carry out, done inside int main
int main()
{    
    int choice;
    printf("Choose a process: \nPress 1 for rotational encryption\n2 for rotational decryption\n3 for substitution encryption\n4 for substitution decryption\n");
    scanf("%d", &choice);
    
    switch(choice)
    {
        case 1: //rotational encryption
            char phrase[206]; 
            float key; //key can be between -25 and 25. 0 & 26 imply no encryption

            //getting the phrase
            printf("enter a phrase to encode in capitals: \n");     //prompts phrase to be put in by user
            scanf("%s", phrase);                        //scans the phrase from the user. wont read spaces
    
            //allows user to choose a shifting value, the 'key'
            printf("enter a key to shift by: \n");
            scanf("%f", &key);
        
            //encrypting and printing the encrypted phrase
            printf("the encryption is:\n");
            encrypt(phrase, key);    //encoding function
            break;
        case 2: //rotational decryption
            char phrase[1024]; 
            float key; //key can be between -25 and 25. 0 & 26 imply no encryption
    
            //getting the phrase
            printf("enter a phrase to decode: \n");     //prompts phrase to be put in by user
            scanf("%s", phrase);                        //scans the phrase from the user
    
            //inputs the shifting value, the 'key'
            printf("enter the key it was shifted by: \n");
            scanf("%f", &key);
        
            //decrypting and printing the decrypted phrase
            printf("the decryption is:\n");
            decrypt(phrase, key);    //decoding function
            break;
        case 3: //substitution encryption
        case 4: //substitution decryption
        default: 
            printf("process chosen is not an option\n");
    }

}

//function definitions

//rotational encryption
char encrypt(char *phrase, float key) 
{
    int i=0;
    while(phrase[i] != 0)
    {
        if(phrase[i]=32) //when spaces get read, they should stay as spaces in the encryption
        {
            phrase[i] = 32;
        }
        else if((phrase[i]+key)>=65 && (phrase[i]+key)<=90) //if it ends up in the capital letter range dont change it
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

//rotational decryption
char decrypt(char *phrase, float key) //rotational decryption definition
{
    char i=0;
    while(phrase[i] != 0)
    {
        if(phrase[i]=32) //when spaces get read, they should stay as spaces in the decryption
        {
            phrase[i] = 32;
        }
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

//substitution encryption

//substitution decryption

