#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes for each process
char rotencrypt(char *phrase, float rotationKey); //encryption function prototype
char rotdecrypt(char *phrase, float rotationKey); //rotational decryption prototype
char subencrypt(char *phrase, char *encryptionKey); //substitution encryption prototype
char subdecrypt(char *phrase, char *encryptionKey); //substitution decryption prototype

//choosing which process to carry out, done inside int main
int main()
{    
    char choice;
    char temp;
    printf("Enter your data (message and encryption keys) into the appropriate files. \n");
    printf("Choose a process: \na) rotational encryption\nb) rotational decryption\nc) substitution encryption\nd) substitution decryption with key\ne) decrypting an unseen text encrypted with a rotation cipher\nf) decrypting an unseen text encrypted with a substitution cipher\n");
    scanf("%c", &choice);
    scanf("%c", &temp);
    
    //introducing variables necessary for the processes
    char phrase[2048];
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char encryptionKey[200];
    float rotationKey; 
    
    FILE *substitutionkey;
    substitutionkey = fopen("substitutionEncryptionKey.txt", "r");
    
    FILE *input;
    input = fopen("data.txt", "r");
    
    FILE *rotationshift;
    rotationshift = fopen("rotationEncryptionKey.txt", "r");
    
    //carries out the chosen process
    switch(choice)
    {
        case 'a': //rotational encryption  
            fscanf(rotationshift, "%f", rotationKey);
            fscanf(input, "%[^\n]s", phrase);

            printf("The encryption is:\n");
            rotencrypt(phrase, rotationKey);    //encoding function
            printf(" \n"); //new line afterwards
            break;
        case 'b': //rotational decryption
            fscanf(rotationshift, "%f", rotationKey);
            fscanf(input, "%[^\n]s", phrase);

            printf("The decryption is:\n");
            rotdecrypt(phrase, rotationKey);    //decoding function
            printf(" \n"); //new line afterwards
            break;
        case 'c': //substitution encryption
            fscanf(substitutionkey, "%s", encryptionKey);
            fscanf(input, "%[^\n]s", phrase);
            
            printf("The encryption is:\n");
            subencrypt(phrase, encryptionKey);
            printf("\n");
            break;
        case 'd': //substitution decryption
            fscanf(substitutionkey, "%s", encryptionKey);
            fscanf(input, "%[^\n]s", phrase);

            printf("The decryption is: \n"); 
            subdecrypt(phrase, encryptionKey);
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
char rotencrypt(char *phrase, float rotationKey) 
{ 
    char i=0;    
    while(phrase[i] != 0)
    {
        if((phrase[i]+rotationKey)>=65 && (phrase[i]+rotationKey)<=90) //if it ends up in the capital letter range, dont change it
        {
            phrase[i] = phrase[i] + rotationKey; //the new value of the letter (phrase[i]) is the letter shifted by the key
        }
        else if((phrase[i]+rotationKey)>90)//this is for in case the positive key shifts letters above the ascii capital letters range. this will rotate back around into it
        {
            phrase[i] = phrase[i] - 26 + rotationKey;
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
char rotdecrypt(char *phrase, float rotationKey) 
{   
    char i=0;    
    while(phrase[i] != 0)
    {
        if(phrase[i]>=32 && phrase[i]<=64) //this makes sure punctuation and numbers are not changed 
        {
            phrase[i] = phrase[i];
        }  
        else if((phrase[i]-rotationKey)>=65 && (phrase[i]-rotationKey)<=90) //if it is within the capital letter range and A-OK
        {
            phrase[i] = phrase[i] - rotationKey;
        }
        else if((phrase[i]-rotationKey)<65) //if it falls below the capital letter range
        {
            phrase[i] = phrase[i] + 26 - rotationKey;
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
        if(phrase[i]>=65 && phrase[i]<=90)
        {
            while(phrase[i] != alphabet[x])
            {
                x++;
            }
            printf("%c", encryptionKey[x]);
            x=0;
        }
        else 
        {
            printf("%c", phrase[i]);
        }
        i++; 
    }
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
            printf("%c", alphabet[x]);
            x=0;
        }
        else
        {
            printf("%c", phrase[i]);
        }
        i++; 
    }
}
