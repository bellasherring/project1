#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function prototypes for each process
char rotencrypt(float rotationkey); //encryption function prototype
char rotdecrypt(float rotationkey); //rotational decryption prototype
char subencrypt(char *phrase, char *encryptionKey); //substitution encryption prototype
char subdecrypt(char *phrase, char *encryptionKey); //substitution decryption prototype

//choosing which process to carry out, done inside int main
int main()
{    
    //choosing process menu
    int choice;
    char temp;
    printf("Enter your data into the appropriate files. \n");
    printf("Choose a process: \na) rotational encryption\nb) rotational decryption\nc) substitution encryption\nd) substitution decryption with key\ne) decrypting an unseen text encrypted with a rotation cipher\nf) decrypting an unseen text encrypted with a substitution cipher\n");
    scanf("%c", &choice);
    scanf("%c", &temp);
    
    //introducing variables necessary for the processes
    char phrase[2048];
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char encryptionKey[200];
    float rotationkey; 
    
    FILE *substitutionkey;
    substitutionkey = fopen("substitutionEncryptionKey.txt", "r");
    FILE *input;
    input = fopen("data.txt", "r");
    
    //carries out the chosen process
    switch(choice)
    {
        case 'a': //rotational encryption  
            //allows user to choose a shifting value, the 'key'
            printf("Enter a key to shift by: \n");
            scanf("%f", &rotationkey);
        
            //encrypting and printing the encrypted phrase
            printf("The encryption is:\n");
            rotencrypt(rotationkey);    //encoding function
            printf(" \n"); //new line afterwards
            break;
        case 'b': //rotational decryption
            //inputs the shifting value, the 'key'
            printf("Enter the key it was shifted by: \n");
            scanf("%f", &rotationkey);
        
            //decrypting and printing the decrypted phrase
            printf("The decryption is:\n");
            rotdecrypt(rotationkey);    //decoding function
            printf(" \n"); //new line afterwards
            break;
        case 'c': //substitution encryption
            fscanf(substitutionkey, "%s", encryptionKey);
            fscanf(input, "[^\n]s", phrase);
            
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
char rotencrypt(float rotationkey) 
{
    char phrase[2048];
    FILE *input;
    input = fopen("data.txt", "r");
    fscanf(input, "%[^\n]s", phrase);     
    char i=0;    
    while(phrase[i] != 0)
    {
        if((phrase[i]+rotationkey)>=65 && (phrase[i]+rotationkey)<=90) //if it ends up in the capital letter range, dont change it
        {
            phrase[i] = phrase[i] + rotationkey; //the new value of the letter (phrase[i]) is the letter shifted by the key
        }
        else if((phrase[i]+rotationkey)>90)//this is for in case the positive key shifts letters above the ascii capital letters range. this will rotate back around into it
        {
            phrase[i] = phrase[i] - 26 + rotationkey;
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
char rotdecrypt(float rotationkey) 
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
        else if((phrase[i]-rotationkey)>=65 && (phrase[i]-rotationkey)<=90) //if it is within the capital letter range and A-OK
        {
            phrase[i] = phrase[i] - rotationkey;
        }
        else if((phrase[i]-rotationkey)<65) //if it falls below the capital letter range
        {
            phrase[i] = phrase[i] + 26 - rotationkey;
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
