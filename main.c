/* 
This code allows the user to choose between 4 process options: rotational encryption, rotational decryption, 
substitution encryption, and substitution decryption. It reads data from files and then either 
encrypts/decrypts the data within separate functions. To choose the process, a menu is printed to the screen,
and the user has to type in a letter that corresponds to the process they want to do, and then press enter.
The program will then print the result to the screen and also to an output file (labelled messageOutput.txt).
The content of the input files should be edited beforehand. data.txt should hold the message being
encrypted or decrypted all on one line, rotationEncryptionKey.txt should hold the integer shifting value
for a rotation encryption/decryption, and substitutionEncryptionKey.txt should hold the substitution
cipher key string.
*/

//Header files which include declarations of all of the functions used in the code such as fscanf and printf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
These are function prototypes. They 'declare' each of the functions that are created to execute specific
chunks of code within this program. The formatting is returnValue functionName(argument1, argument2);
*/
char rotencrypt(char *phrase, float rotationKey); //encryption function prototype
char rotdecrypt(char *phrase, float rotationKey); //rotational decryption prototype
char subencrypt(char *phrase, char *encryptionKey); //substitution encryption prototype
char subdecrypt(char *phrase, char *encryptionKey); //substitution decryption prototype

int main()
{    
    char choice; //this declares the variable choice, a character which will store the process chosen by the user in the menu
    char phrase[2048]; //declares the phrase variable, a string in which the message will be stored so that it can be accessed in functions. It is of type char with a size of 2048.
    char alphabet[200]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declares the alphabet string and initialises it to ABCDEFGHIJKLMNOPQRSTUVWXYZ
    char encryptionKey[200]; //declares the substitution encryption key variable, a string in which the substitution cipher key will be stored so that it can be accessed in functions.
    float rotationKey; //declares the rotational encryption key variable, a float number in which the shifting value for rotation encryptions will be stored so that it can be accessed in functions
    
    FILE *substitutionkey; //declares the use of a file which will be referred to as 'substitutionkey' within the code
    substitutionkey = fopen("substitutionEncryptionKey.txt", "r"); //the fopen function opens the file called 'substitutionEncryptionKey.txt' and the "r" indicates that the file will be read from. the contents of this file is assigned to 'substitutionkey'
    
    FILE *input; //declares file which will be referred to as 'input'
    input = fopen("data.txt", "r"); //opens the file, indicates it will be read from, and assigns it to 'input'
    
    FILE *rotationshift; //declares file which will be referred to as 'rotationshift'
    rotationshift = fopen("rotationEncryptionKey.txt", "r"); //opens the file, indicates it will be read from, and assigns it to 'rotationshift'
    
    FILE *output; //declares file which will be referred to as 'output'
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
    
    /*
    The first printf prints a prompt to the screen with a new line after it (\n) to instruct the user to enter their data into the 
    files, including the message and either the rotation or substitution keys. 
    The second printf prints a menu to the screen with each process on a new line, so that the user can see each process and the value
    they should enter in order to select each particular process.
    */
    printf("Enter your data (message and encryption keys) into the appropriate files. \n"); 
    printf("Choose a process: \na) rotational encryption\nb) rotational decryption\nc) substitution encryption\nd) substitution decryption with key\ne) decrypting an unseen text encrypted with a rotation cipher\nf) decrypting an unseen text encrypted with a substitution cipher\n");
    scanf("%c", &choice); //this reads a character (%c) from the user and stores it in the variable 'choice' as declared earlier (line 29)

    /*
    The below switch case statement is used to implement the menu from above. It switches 'cases' depending on the value of the variable
    'choice' in the switch() brackets. If the value stored in choice (which is read from the user in the above scanf) is 'a', the case 'a'
    process will occur until the break; statement. When the program gets up to the break; line, the switch case is exited and the program
    will move on. Case 'a' implements rotational encryption, case 'b' implements rotational decryption, case 'c' implements substitutional 
    encryption and case 'd' implements substitutional decryption. If the choice value is something other than a, b, c, or d, then the 
    default case will occur.
    */
    switch(choice)
    {
        case 'a':
            fscanf(rotationshift, "%f", &rotationKey); //this reads the first float value from the file rotationshift, which is the shifting value the user desires/knows, and stores it in the rotationKey variable
            fscanf(input, "%[^\n]s", phrase); //this reads the message/phrase string from the file input until the program sees a new line in that file (indicated by the [^\n] before the s) and stores it in the phrase variable

            printf("The encryption is:\n"); //this is printed to the screen so that the user will know what the next line represents
            rotencrypt(phrase, rotationKey); //the rotencrypt function is called to implement the code that will encrypt the phrase. The two items in the brackets (phrase, rotationKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'b': 
            fscanf(rotationshift, "%f", &rotationKey); //reads the first float value from the file rotationshift, which is the shifting value the user desires/knows, and stores it in the rotationKey variable
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase string from the file input until the program sees a new line, and stores it in the phrase variable

            printf("The decryption is:\n"); //this is printed to the screen so that the user will know what the next line represents
            rotdecrypt(phrase, rotationKey); //the rotdecrypt function is called to implement the code that will decrypt the phrase. The two items in the brackets (phrase, rotationKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'c': 
            fscanf(substitutionkey, "%s", encryptionKey); //reads the first string from the file substitutionkey, which is the substitution cipher string, and stores it in the encryptionKey variable
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase string from the file input until the program sees a new line, and stores it in the phrase variable
            
            printf("The encryption is:\n"); //this is printed to the screen so that the user will know what the next line represents
            subencrypt(phrase, encryptionKey); //the subencrypt function is called to implement the code that will encrypt the phrase. The two items in the brackets (phrase, encryptionKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'd': 
            fscanf(substitutionkey, "%s", encryptionKey); //reads the first string from the file substitutionkey, which is the substitution cipher string, and stores it in the encryptionKey variable
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase string from the file input until the program sees a new line, and stores it in the phrase variable

            printf("The decryption is: \n"); //this is printed to the screen so that the user will know what the next line represents
            subdecrypt(phrase, encryptionKey); //calls the subdecrypt function which will implement the code that will decrypt the phrase. The two items in the brackets (phrase, encryptionKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'e': //decrypting unseen text encrypted with a rotation cipher
            printf("Enter phrase that was encrypted: \n");
            scanf("%[^\n]s", phrase);
            break;
        case 'f':
            
            break;
        default: //the code that happens if the character put in by the user doesn't match any of the cases
            printf("Process chosen is not an option. Run the code again\n"); //tells the user that they entered a character that doesn't correspond to one of the process options, so the code has to be run again
    }
}

//All of the code below includes function definitions, which hold the code that the function executes whenever it is called in int main().

/*
This is the rotational encryption function. When it is called, it takes the values for phrase and rotationKey and uses them in its body
to execute the rest of the code. This code takes a message in plain English text (phrase) and a float number (rotationKey). Each letter
of the phrase is shifted through the alphabet by whatever the rotationKey is - for example if the rotationKey was 1, A would be shifted
into B, and B into C, etc, so if the word was "ABBA" it would be encrypted into "BCCB". This function prints each encrypted letter one
at a time to both the screen (stdout) and the file 'output'.
*/
char rotencrypt(char *phrase, float rotationKey) 
{ 
    char i=0; //i is the variable that will count through each individual character of the phrase string. It is initialised as 0 to start at the beginning of the string.
    FILE *output; //declares the file which will be referred to as output in the code whenever it is used
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
    while(phrase[i] != 0) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to 0, because then it no longer fits the condition of != 0 (not equal to 0). It will occur until a new line is reached.
    {
        /*
        phrase[i] + rotationKey utilises the ASCII values of each letter. A has the value 65, and Z the value 90. All capital letters are
        within 65 and 90. The rotationKey adds to the value of the phrase[i] ASCII value and therefore results in a new encrypted ASCII 
        character.
        */
        if(phrase[i]<=64 || phrase[i]>=91) //if the value of the phrase[i] character in the original plain English text message is something other than a capital letter, this block of code will execute
        {
            phrase[i] = phrase[i]; //phrase[i] is not changed/encrypted by the code
        }  
        else if((phrase[i]+rotationKey)>=65 && (phrase[i]+rotationKey)<=90) //if the new encrypted ASCII value would fall within the capital letter range (between 65 and 90) this block of code will execute.
        {
            phrase[i] = phrase[i] + rotationKey; //phrase[i] is reassigned a new value - itself plus the rotationKey, which makes it into the new encrypted ASCII character.
        }
    
        else if((phrase[i]+rotationKey)>90) //if the new encrypted ASCII value would fall above the capital letter range (above 90) this block of code will execute
        {
            phrase[i] = phrase[i] - 26 + rotationKey; //phrase[i] is reassigned a new value - itself plus the rotationKey minus 26 (the number of letters in the alphabet) in order to stay within the range of capital letters. 
        }         
        printf("%c", phrase[i]); //prints each character phrase[i] to the screen
        fprintf(output, "%c", phrase[i]); //prints each character phrase[i] to the file 'output'
        i++; //increments the value of i (the variable that counts through the letters of the phrase) so that the process within the while loop is executed for each letter consecutively
    }
}

/*
This is the rotational decryption function. When it is called, it takes the values for phrase and rotationKey and uses them in its body
to execute the rest of the code. This code takes a message in encrypted English text (phrase) and a float number (rotationKey). Each letter
of the encrypted phrase has been shifted through the alphabet by whatever the rotationKey is - for example if the rotationKey was 1, A would 
have been shifted into B, and B into C, etc, so if the word was "ABBA" it would be encrypted into "BCCB". This function shifts an 
encrypted message back into plain English text by this principle, and prints each encrypted letter one at a time to both the screen (stdout) 
and the file 'output'.
*/
char rotdecrypt(char *phrase, float rotationKey) 
{   
    char i=0; //i is the variable that will count through each individual character of the phrase string. It is initialised as 0 to start at the beginning of the string.
    FILE *output; //declares the file which will be referred to as output in the code whenever it is used
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
    while(phrase[i] != 0) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to 0, because then it no longer fits the condition of != 0 (not equal to 0). It will occur until a new line is reached.
    {
        /*
        phrase[i] - rotationKey utilises the ASCII values of each letter. A has the value 65, and Z the value 90. All capital letters are
        within 65 and 90. The rotationKey is taken away from the value of the phrase[i] ASCII value and therefore results in a new decrypted 
        ASCII character as it shifts it back into the original plain English version rather than the shifted cipher version.
        */
        if(phrase[i]<=64 || phrase[i]>=91) //if the value of the phrase[i] character in the original plain English text message is something other than a capital letter, this block of code will execute
        {
            phrase[i] = phrase[i]; //phrase[i] remains unchanged
        }  
        else if((phrase[i]-rotationKey)>=65 && (phrase[i]-rotationKey)<=90) //if the new decrypted ASCII falls within the capital letter range of 65 and 90 (i.e. it remains a capital letter not a different ASCII character that isn't English) 
        {
            phrase[i] = phrase[i] - rotationKey;
        }
        else if((phrase[i]-rotationKey)<65)
        {
            phrase[i] = phrase[i] + 26 - rotationKey;
        }
        fprintf(output, "%c", phrase[i]);
        printf("%c", phrase[i]);   
        i++;
    }
}

//substitution encryption
char subencrypt(char *phrase, char *encryptionKey)
{  
    char i=0, x=0;
    FILE *output;
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
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
            fprintf(output, "%c", encryptionKey[x]);
            x=0;
        }
        else 
        {
            printf("%c", phrase[i]);
            fprintf(output, "%c", phrase[i]);
        }
        i++; 
    }
}

//substitution decryption
char subdecrypt(char *phrase, char *encryptionKey)
{
    char i=0, x=0; 
    FILE *output;
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
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
            fprintf(output, "%c", alphabet[x]);
            x=0;
        }
        else
        {
            printf("%c", phrase[i]);
            fprintf(output, "%c", phrase[i]);
        }
        i++; 
    }
}
