#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes for each process
char rotencrypt(char *phrase, float key); //encryption function prototype

char rotdecrypt(char *phrase, float key); //rotational decryption prototype

char subencrypt(char *phrase, char *encryptionKey); //substitution encryption prototype
char alphabetencrypt(char *phrase, char x, char *encryptionKey);

char subdecrypt(char *phrase, char *encryptionKey); //substitution decryption prototype


//choosing which process to carry out, done inside int main
int main()
{    
    //choosing process menu
    int choice;
    char temp;
    printf("Choose a process: \nPress 1 for rotational encryption\nPress 2 for rotational decryption\nPress 3 for substitution encryption\nPress 4 for substitution decryption with key\n");
    scanf("%d", &choice);
    scanf("%c", &temp);
    
    //introducing variables necessary for the processes
    char phrase[206];
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char encryptionKey[200];
    float key; //for rotation. key between 0 and 26
    
    //carries out the chosen process
    switch(choice)
    {
        case 1: //rotational encryption
            //getting the phrase
            printf("Enter a phrase to rotationally encrypt in capitals: \n");     //prompts phrase to be put in by user
            scanf("%[^\n]s", phrase);                        //scans the phrase from the user until it reads a new line
    
            //allows user to choose a shifting value, the 'key'
            printf("Enter a key to shift by: \n");
            scanf("%f", &key);
        
            //encrypting and printing the encrypted phrase
            printf("The encryption is:\n");
            rotencrypt(phrase, key);    //encoding function
            printf(" \n"); //new line afterwards
            break;
        case 2: //rotational decryption
            //getting the phrase
            printf("Enter a phrase to rotationally decrypt in capitals: \n");     //prompts phrase to be put in by user
            scanf("%[^\n]s", phrase);                        //scans the phrase from the user
    
            //inputs the shifting value, the 'key'
            printf("Enter the key it was shifted by: \n");
            scanf("%f", &key);
        
            //decrypting and printing the decrypted phrase
            printf("The decryption is:\n");
            rotdecrypt(phrase, key);    //decoding function
            printf(" \n"); //new line afterwards
            break;
        case 3: //substitution encryption
            printf("Enter a phrase to substitutionally encrypt in capitals: \n");
            scanf("%[^\n]s", phrase);
            
            printf("Enter an encryption key, a string of capital letters with no spaces:\n");
            scanf("%s", encryptionKey);
            
            //encrypting the phrase
            printf("The encryption is:\n");
            subencrypt(phrase, encryptionKey);
            printf("\n");
            break;
        case 4: //substitution decryption
            printf("Enter a phrase to substitutionlly decrypt in capitals: \n"); //prompt to enter phrase
            scanf("%[^\n]s", phrase); //reads phrase put in by user

            printf("Enter the encryption key, a string of capital letters with no spaces: \n"); //prompts encryption key
            scanf("%s", encryptionKey); //scans encryption key

            printf("The decryption is: \n"); //shows what the next line will be, the decrypted phrase
            subdecrypt(phrase, encryptionKey); //calls the decryption function which will decrypt the phrase and print it as well
            printf("\n");
            break;
        default: 
            printf("Process chosen is not an option.\n");
    }
}

//function definitions

//rotational encryption
char rotencrypt(char *phrase, float key) 
{
    char i=0;
    while(phrase[i] != 0)
    {
        if((phrase[i]+key)>=65 && (phrase[i]+key)<=90) //if it ends up in the capital letter range, dont change it
        {
            phrase[i] = phrase[i] + key; //the new value of the letter (phrase[i]) is the letter shifted by the key
        }
        else if((phrase[i]+key)>90)//this is for in case the positive key shifts letters above the ascii capital letters range. this will rotate back around into it
        {
            phrase[i] = phrase[i] - 26 + key;
        }        
        else if(phrase[i]>=32 && phrase[i]<=64) //this makes sure punctuation and numbers are not changed 
        {
            phrase[i] = phrase[i];
        }       
        
        printf("%c", phrase[i]); //prints each reassigned letter
        i++; //increments so that the loop goes through each letter
    }
}

//rotational decryption
char rotdecrypt(char *phrase, float key) 
{
    char i=0;
    while(phrase[i] != 0)
    {
        if(phrase[i]>=32 && phrase[i]<=64) //this makes sure punctuation and numbers are not changed 
        {
            phrase[i] = phrase[i];
        }  
        else if((phrase[i]-key)>=65 && (phrase[i]-key)<=90) //if it is within the capital letter range and A-OK
        {
            phrase[i] = phrase[i] - key;
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
char subencrypt(char *phrase, char *encryptionKey) //substitution encryption
{
    char i=0, x=0;
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while(phrase[i] != 0)
    {
        if(phrase[i]>=32 && phrase[i]<=64) //this makes sure punctuation and numbers are not changed 
        {
            phrase[i] = phrase[i];
            printf("%c", phrase[i]);
        } 
        else
        {
            while(phrase[i] != alphabet[x])
            {
                x++;
            }
            alphabetencrypt(phrase, x, encryptionKey);
        }
        i++;
    }
}

//alphabet encryption to use in the substitution encryption
char alphabetencrypt(char *phrase, char x, char *encryptionKey)
{
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alphabet[x]=encryptionKey[x];
    printf("%c", encryptionKey[x]);
}

//substitution decryption
char subdecrypt(char *phrase, char *encryptionKey)
{
    char i=0, x=0; //initialises these variables to 0. i counts through the letters of the phrase, and x counts through the letters of the encryption key and alphabet
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //the alphabet being used
    while(phrase[i] != 0) //while the letter of the phrase is not a new line
    {
        if(phrase[i]>=32 && phrase[i]<=64) //if the character is punctuation or a space or something, it remains unchanged
        {
            printf("%c", phrase[i]); //the character is printed as it was, and it isnt changed
        }
        else //if the character is a capital letter, basically
        {
            while(phrase[i] != encryptionKey[x]) //while the letter of the phrase doesn't match the letter of the encryption key string
            {                                       
                x++; //increment x from 0 so that it moves through each letter of the encryption key string. this will happen until the letter of the phrase matches the letter of the encryption key
            }
            phrase[i]=alphabet[x]; //the letter of the encryption string at position x (which is the same as the letter at position i of the phrase) is changed into the letter of the alphabet string at position x, the matching one
            printf("%c", alphabet[x]); //the letter of the alphabet string at position x is printed
            x=0; //x is reassigned back to 0 so that next time a letter of the phrase is analysed, the code checks back through the alphabet string from the beginning (x=0)
        }
        i++; //this increments i, and therefore makes the code move on to analyse the next letter of the phrase.
    }
}
