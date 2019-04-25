#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes for each process
char rotencrypt(float key); //encryption function prototype
char rotdecrypt(float key); //rotational decryption prototype
char subencrypt(char *encryptionKey); //substitution encryption prototype
char subdecrypt(char *encryptionKey); //substitution decryption prototype

//choosing which process to carry out, done inside int main
int main()
{    
    //choosing process menu
    int choice;
    char temp;
    printf("Choose a process: \na) rotational encryption\nb) rotational decryption\nc) substitution encryption\nd) substitution decryption with key\ne) decrypting an unseen text encrypted with a rotation cipher\nf) decrypting an unseen text encrypted with a substitution cipher\n");
    scanf("%c", &choice);
    scanf("%c", &temp);
    
    //introducing variables necessary for the processes
    char phrase[2006];
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char encryptionKey[200];
    float key; //for rotation. key between 0 and 26
    
    //carries out the chosen process
    switch(choice)
    {
        case 'a': //rotational encryption  
            //allows user to choose a shifting value, the 'key'
            printf("Enter a key to shift by: \n");
            scanf("%f", &key);
        
            //encrypting and printing the encrypted phrase
            printf("The encryption is:\n");
            rotencrypt(key);    //encoding function
            printf(" \n"); //new line afterwards
            break;
        case 'b': //rotational decryption
            //inputs the shifting value, the 'key'
            printf("Enter the key it was shifted by: \n");
            scanf("%f", &key);
        
            //decrypting and printing the decrypted phrase
            printf("The decryption is:\n");
            rotdecrypt(key);    //decoding function
            printf(" \n"); //new line afterwards
            break;
        case 'c': //substitution encryption
            printf("Enter an encryption key, a string of capital letters with no spaces:\n");
            scanf("%s", encryptionKey);
            
            //encrypting the phrase
            printf("The encryption is:\n");
            subencrypt(encryptionKey);
            printf("\n");
            break;
        case 'd': //substitution decryption
            //printf("Enter a phrase to substitutionlly decrypt in capitals: \n"); //prompt to enter phrase
            //scanf("%[^\n]s", phrase); //reads phrase put in by user

            printf("Enter the encryption key, a string of capital letters with no spaces: \n"); //prompts encryption key
            scanf("%s", encryptionKey); //scans encryption key

            printf("The decryption is: \n"); //shows what the next line will be, the decrypted phrase
            subdecrypt(encryptionKey); //calls the decryption function which will decrypt the phrase and print it as well
            printf("\n");
            break;
        case 'e': //decrypting unseen text encrypted with a rotation cipher
            printf("Enter phrase that was encrypted: \n");
            scanf("%[^\n]s", phrase);
            break;
        case 'f':
            
            break;
        default: 
            printf("Process chosen is not an option.\n");
    }
}

//function definitions

//rotational encryption
char rotencrypt(float key) 
{
    char phrase[2048];
    FILE *input;
    input = fopen("data.txt", "r");
    fscanf(input, "%[^\n]s", phrase);     
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
char rotdecrypt(float key) 
{
    char phrase[2048];
    FILE *input;
    input = fopen("data.txt", "r");
    fscanf(input, "%[^\n]s", phrase);     
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
char subencrypt(char *encryptionKey) //substitution encryption
{
    char phrase[2048];
    FILE *input;
    input = fopen("data.txt", "r");
    fscanf(input, "%[^\n]s", phrase);     
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
            phrase[i]=encryptionKey[x];
            printf("%c", encryptionKey[x]);
        }
        i++;
    }
}

//substitution decryption
char subdecrypt(char *encryptionKey)
{
    char phrase[2048];
    FILE *input;
    input = fopen("data.txt", "r");
    fscanf(input, "%[^\n]s", phrase);
    char i=0, x=0; 
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    while(phrase[i] != 0) 
    {
        if(phrase[i]>=32 && phrase[i]<=64) 
        {
            printf("%c", phrase[i]); 
        }
        else 
        {
            while(phrase[i] != encryptionKey[x]) 
            {                                       
                x++; 
            }
            phrase[i]=alphabet[x]; 
            printf("%c", alphabet[x]); 
            x=0; 
        }
        i++;
    }
}
