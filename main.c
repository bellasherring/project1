#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes for each process
char rotencrypt(char *phrase, float key); //encryption function prototype

char rotdecrypt(char *phrase, float key); //rotational decryption pt

char subencrypt(char *phrase, char *encryptionKey); //substitution encryption pt
char alphabetencrypt(char *phrase, char x, char *encryptionKey);

char subdecrypt(char *phrase, char *encryptionKey); //substitution decryption pt
char alphabetdecrypt(char *phrase, char x, char *encryptionKey);


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
    char alphabet[200];
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
            
            printf("Enter an encyption key, a string of capital letters with no spaces:\n");
            scanf("%s", encryptionKey);
            
            //encrypting the phrase
            printf("The encryption is:\n");
            subencrypt(phrase, encryptionKey);
            printf("\n");
            break;
        case 4: //substitution decryption
            printf("Enter a phrase to substitutionally decrypt in capitals:\n");
            scanf("%[^\n]s", phrase);
            
            printf("Enter an encyption key, a string of capital letters with no spaces:\n");
            scanf("%s", encryptionKey);
            
            //decrypting the phrase
            printf("The decryption is:\n");
            subdecrypt(phrase, encryptionKey);
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
    char i=0, x=0;
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while(phrase[i] != 0)
    {
        if(phrase[i]>=65 && phrase[i]<=90)
        {
            while(phrase[i] != encryptionKey[x])
            {
                x++;
            }
            alphabetdecrypt(phrase, x, encryptionKey);
        }
        else if(phrase[i]>=32 && phrase[i]<=64) //this makes sure punctuation and numbers are not changed 
        {
            phrase[i] = phrase[i];
            printf("%c", phrase[i]);
        } 
        i++;
    }
}

//alphabet decryption to use in the substitution decryption
char alphabetdecrypt(char *phrase, char x, char *encryptionKey)
{
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //char encryptionKey[200]="QAZXSWEDCVFRTGBNHYUJMKILOP";
    encryptionKey[x]=alphabet[x];
    printf("%c", alphabet[x]);
}
