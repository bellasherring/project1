/* 
This code allows the user to choose between 5 process options: rotational encryption, rotational decryption, 
substitution encryption, substitution decryption, and rotational decryption of an unseen text without the
rotation key. It reads data from files and then either encrypts/decrypts the data within separate functions. 
To choose the process, a menu is printed to the screen, and the user has to type in a letter that corresponds 
to the process they want to do, and then press enter. The program will then print the result to the screen 
and also to an output file (labelled messageOutput.txt). The content of the input files should be edited 
beforehand. data.txt should hold the message being encrypted or decrypted all on one line, 
rotationEncryptionKey.txt should hold the integer shifting value for a rotation encryption/decryption, and 
substitutionEncryptionKey.txt should hold the substitution cipher key array.
*/

//Header files which include declarations of all of the functions used in the code such as fscanf and printf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
These are function prototypes. They 'declare' each of the functions that are created to execute specific
chunks of code within this program. The formatting is returnValue functionName(argument1, argument2);
*/
char rotencrypt(char *phrase, float rotationKey); //rotational encryption function prototype
char rotdecrypt(char *phrase, float rotationKey); //rotational decryption function prototype
char subencrypt(char *phrase, char *encryptionKey); //substitution encryption function prototype
char subdecrypt(char *phrase, char *encryptionKey); //substitution decryption function prototype
char unseenrotdecrypt(char *phrase, float rotationKey); //unseen rotational decryption function prototype

int main()
{    
    char choice; //this declares the variable choice, a character which will store the process chosen by the user in the menu
    char phrase[3000]; //declares the phrase variable, an array in which the message will be stored so that it can be accessed in functions. It is of type char with a size of 2048.
    char alphabet[30]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declares the alphabet array and initialises it to ABCDEFGHIJKLMNOPQRSTUVWXYZ
    char encryptionKey[30]; //declares the substitution encryption key variable, an array in which the substitution cipher key will be stored so that it can be accessed in functions.
    float rotationKey; //declares the rotational encryption key variable, a float number in which the shifting value for rotation encryptions will be stored so that it can be accessed in functions
    //the below integer variables will be used to count the frequency of each letter as it appears in the message put in by the user for the 'decrypting an unseen rotationally encrypted' block of text. All initliased to 0 so that the counts will be accurate and not random numbers.
    int countA=0, countB=0, countC=0, countD=0, countE=0, countF=0, countG=0, countH=0, countI=0, countJ=0, countK=0, countL=0, countM=0, countN=0, countO=0, countP=0, countQ=0, countR=0, countS=0, countT=0, countU=0, countV=0, countW=0, countX=0, countY=0, countZ=0;
    int i=0; //this declares the integer variable i, which will be used to count through the letters of messages put in by the user so each letter/character can be analysed one at a time
    int data[26]; //this declares an integer array 'data' which will be used to store the values of the frequencies of all the letters of the message put in by the user
    int maxindex=0;//this declares the integer variable maxindex, which will be used to store the value of the position at which the most common letter occurs in the unseen text put in by the user
    int maximum=-1e30; //this declares the integer variable maximum as a very small number -1e30, which will be used to hold the frequency of the most commonly occurring letter in the unseen text put in by the user

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
    printf("Choose a process: \na) rotational encryption\nb) rotational decryption\nc) substitution encryption\nd) substitution decryption with key\ne) decrypting an unseen text encrypted with a rotation cipher\n");
    scanf("%c", &choice); //this reads a character (%c) from the user and stores it in the variable 'choice' as declared earlier (line 29)

    /*
    The below switch case statement is used to implement the menu from above. It switches 'cases' depending on the value of the variable
    'choice' in the switch() brackets. If the value stored in choice (which is read from the user in the above scanf) is 'a', the case 'a'
    process will occur until the break; statement. When the program gets up to the break; line, the switch case is exited and the program
    will move on. Case 'a' implements rotational encryption, case 'b' implements rotational decryption, case 'c' implements substitutional 
    encryption, case 'd' implements substitutional decryption, and case 'e' implements decryption of text encrypted with a rotational cipher,
    but without the original key. If the choice value is something other than a, b, c, d, or e, then the default case will occur.
    */
    switch(choice)
    {
        case 'a':
            fscanf(rotationshift, "%f", &rotationKey); //this reads the first float value from the file rotationshift, which is the shifting value the user desires/knows, and stores it in the rotationKey variable
            fscanf(input, "%[^\n]s", phrase); //this reads the message/phrase array from the file input until the program sees a new line in that file (indicated by the [^\n] before the s) and stores it in the phrase variable

            printf("The encryption is:\n"); //this is printed to the screen so that the user will know what the next line represents
            rotencrypt(phrase, rotationKey); //the rotencrypt function is called to implement the code that will encrypt the phrase. The two items in the brackets (phrase, rotationKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'b': 
            fscanf(rotationshift, "%f", &rotationKey); //reads the first float value from the file rotationshift, which is the shifting value the user desires/knows, and stores it in the rotationKey variable
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase array from the file input until the program sees a new line, and stores it in the phrase variable

            printf("The decryption is:\n"); //this is printed to the screen so that the user will know what the next line represents
            rotdecrypt(phrase, rotationKey); //the rotdecrypt function is called to implement the code that will decrypt the phrase. The two items in the brackets (phrase, rotationKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'c': 
            fscanf(substitutionkey, "%s", encryptionKey); //reads the first array from the file substitutionkey, which is the substitution cipher array, and stores it in the encryptionKey variable
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase array from the file input until the program sees a new line, and stores it in the phrase variable
            
            printf("The encryption is:\n"); //this is printed to the screen so that the user will know what the next line represents
            subencrypt(phrase, encryptionKey); //the subencrypt function is called to implement the code that will encrypt the phrase. The two items in the brackets (phrase, encryptionKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'd': 
            fscanf(substitutionkey, "%s", encryptionKey); //reads the first array from the file substitutionkey, which is the substitution cipher array, and stores it in the encryptionKey variable
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase array from the file input until the program sees a new line, and stores it in the phrase variable

            printf("The decryption is: \n"); //this is printed to the screen so that the user will know what the next line represents
            subdecrypt(phrase, encryptionKey); //calls the subdecrypt function which will implement the code that will decrypt the phrase. The two items in the brackets (phrase, encryptionKey) represent the arguments/variables that the function takes and then uses in its execution
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
        case 'e': 
            fscanf(input, "%[^\n]s", phrase); //reads the message/phrase array from the file input until the program sees a new line, and stores it in the phrase variable
            while(phrase[i] != EOF) //this will ensure that every character of the file will be read and analysed within this while loop. EOF means end of file.
            {
                switch(phrase[i]) //switches between the different characters each letter phrase[i] can be.
                {
                    case 65: countA++; break; //If phrase[i] is 65, the ASCII value for A, the countA counter will be incremented by 1 in order to keep count of how many times A occurs.
                    case 66: countB++; break; //if phrase [i] is 66 or B
                    case 67: countC++; break;
                    case 68: countD++; break;
                    case 69: countE++; break;
                    case 70: countF++; break;
                    case 71: countG++; break;
                    case 72: countH++; break;
                    case 73: countI++; break;
                    case 74: countJ++; break;
                    case 75: countK++; break;
                    case 76: countL++; break;
                    case 77: countM++; break;
                    case 78: countN++; break;
                    case 79: countO++; break;
                    case 80: countP++; break;
                    case 81: countQ++; break;
                    case 82: countR++; break;
                    case 83: countS++; break;
                    case 84: countT++; break;
                    case 85: countU++; break;
                    case 86: countV++; break;
                    case 87: countW++; break;
                    case 88: countX++; break;
                    case 89: countY++; break;
                    case 90: countZ++; break;
                    default: break; //if phrase[i] is something other than a capital letter, nothing will happen - no letter counters will be incremented.
                }
                i++; //i is incremented at the end of each loop so that the next loop will move on to the next letter.
            } 
            
            /*
            The positions in the datan array are filled with the values for the number of times each letter occured. The frequency of A is stored
            in position 0 (data[0]) since A is the first letter of the alphabet, and so on up until Z and data[25]. Then from this array of the
            letter frequencies, the maximum frequency can be found, and the position of that maximum frequency gives away the letter that occurred
            the most. The rotation key can then be calculated from that.
            */
            data[0]=countA; data[1]=countB; data[2]=countC; data[3]=countD; data[4]=countE; data[5]=countF; 
            data[6]=countG; data[7]=countH; data[8]=countI; data[9]=countJ; data[10]=countK; data[11]=countL; 
            data[12]=countM; data[13]=countN; data[14]=countO; data[15]=countP; data[16]=countQ; data[17]=countR; 
            data[18]=countS; data[19]=countT; data[20]=countU; data[21]=countV; data[22]=countW; data[23]=countX; 
            data[24]=countY; data[25]=countZ;
            
            i=0; //i is reset to 0 so that it starts from the beginning again. It is used below to count through the values of the datan array at each position/index
            while(i<26) //counts through only the 26 letters of the alphabet
            {
                if(data[i]>maximum) //if the value at the position of the datan array is greater than the maximum, the values for maximum and the index at which the maximum occurs will change. This means that the whole datan array will be looked at, and the maximum&maxindex only changed if they are surpassed
                {
                    maximum=data[i];    //the new maximum is assigned to the element number i
                    maxindex=i;     //max index is set as i
                }
                i++;    //add another to the i counter in order to look at the next index of the datan array
            }
            
            printf("If E is the most common letter in the decryption, the decryption will be: \n"); //this next block assumes that E is the most common letter in the plain decrypted English text version of the message.
            if(maxindex+65-'E' <= 0) //If the value is negative, 26 needs to be added so that the rotationKey will keep only within the capital letter range
            {
                rotationKey = (maxindex+65) - 'E' + 26; //the value for the maxindex has 65 added to it so that it becomes the ASCII value for the letter (between 65 and 90), not just the maxindex value (between 0 and 25). 
            }
            else if(maxindex+65 - 'E' > 0) //If the value is positive, no changes need to be made other than the simple calculation between the encrypted letter and the original letter, encrypted minus original.
            {
                rotationKey = (maxindex+65) - 'E';
            }
            unseenrotdecrypt(phrase, rotationKey); //calls the function which will decrypt the message based on the rotationKey calculated above.
            
            printf("\n\nIf T is the most common letter in the decryption, the decryption will be: \n"); //this next block assumes that T is the most common letter in the plain decrypted English text version of the message, and then does the same calculations as for 'E'.
            if(maxindex+65-'T' <= 0)
            {
                rotationKey = (maxindex+65) - 'T' + 26;
            }
            else if(maxindex+65 - 'T' > 0)
            {
                rotationKey = (maxindex+65) - 'T';
            }
            unseenrotdecrypt(phrase, rotationKey);
    
            printf("\n\nIf A is the most common letter in the decryption, the decryption will be: \n"); //this next block assumes that A is the most common letter in the plain decrypted English text version of the message, and then does the same calculations as for 'E'.
            if(maxindex+65-'A' <= 0)
            {
            rotationKey = (maxindex+65) - 'A' + 26;
            }
            else if(maxindex+65 - 'A' > 0)
            {
                rotationKey = (maxindex+65) - 'A';
            }
            unseenrotdecrypt(phrase, rotationKey);
            
            printf("\n\nIf O is the most common letter in the decryption, the decryption will be: \n"); //this next block assumes that O is the most common letter in the plain decrypted English text version of the message, and then does the same calculations as for 'E'.
            if(maxindex+65-'O' <= 0)
            {
                rotationKey = (maxindex+65) - 'O' + 26;
            }
            else if(maxindex+65 - 'O' > 0)
            {
                rotationKey = (maxindex+65) - 'O';
            }
            unseenrotdecrypt(phrase, rotationKey);
            
            printf("\n\nIf R is the most common letter in the decryption, the decryption will be: \n"); //this next block assumes that R is the most common letter in the plain decrypted English text version of the message, and then does the same calculations as for 'E'.
            if(maxindex+65-'R' <= 0)
            {
                rotationKey = (maxindex+65) - 'R' + 26;
            }
            else if(maxindex+65 - 'R' > 0)
            {
                rotationKey = (maxindex+65) - 'R';
            }
            unseenrotdecrypt(phrase, rotationKey);
            
            printf("\n\nIf I is the most common letter in the decryption, the decryption will be: \n"); //this next block assumes that I is the most common letter in the plain decrypted English text version of the message, and then does the same calculations as for 'E'.
            if(maxindex+65-'I' <= 0)
            {
                rotationKey = (maxindex+65) - 'I' + 26;
            }
            else if(maxindex+65 - 'I' > 0)
            {
                rotationKey = (maxindex+65) - 'I';
            }
            unseenrotdecrypt(phrase, rotationKey);
            
            printf(" \n"); //a new line is printed afterwards because eclipse che prints straight after the end of the code so this makes it look nicer and clearer for the user
            break; //the break statement tells the program to exit the switch case chunk of code and move on
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
into B, and B into C, etc, so if the word was "ABBA" it would be encrypted into "BCCB". This function prints the array to both the 
screen (stdout) and the file 'output'. The rotationKey must be greater than or equal to zero and less than or equal to 26 to work.
*/
char rotencrypt(char *phrase, float rotationKey) 
{ 
    int i=0; //i is the integer variable that will count through each individual character of the phrase array. It is initialised as 0 to start at the beginning of the array.
    FILE *output; //declares the file which will be referred to as output in the code whenever it is used
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'    
    while(phrase[i] != EOF) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to the end of the file EOF, because then it no longer fits the condition of != EOF (not equal to EOF)
    {
        /*
        phrase[i] + rotationKey utilises the ASCII values of each letter. A has the value 65, and Z the value 90. All capital letters are
        within 65 and 90. The rotationKey adds to the value of the phrase[i] ASCII value and therefore results in a new encrypted ASCII 
        character. Only one of these if...else if statements happens in each while loop.
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
        i++; //increments the value of i (the variable that counts through the letters of the phrase) so that the process within the while loop is executed for each letter consecutively
    }
    printf("%s", phrase); //prints the whole new 'phrase' array to the screen
    fprintf(output, "%s", phrase); //prints the whole new 'phrase' array to the file 'output'
}

/*
This is the rotational decryption function. When it is called, it takes the values for phrase and rotationKey and uses them in its body
to execute the rest of the code. This code takes a message in encrypted English text (phrase) and a float number (rotationKey). Each letter
of the encrypted phrase has been shifted through the alphabet by whatever the rotationKey is - for example if the rotationKey was 1, A would 
have been shifted into B, and B into C, etc, so if the word was "ABBA" it would be encrypted into "BCCB". This function shifts an 
encrypted message back into plain English text by this principle, and prints each encrypted letter one at a time to both the screen (stdout) 
and the file 'output'. The rotationKey must be greater than or equal to zero and less than or equal to 26 to work.
*/
char rotdecrypt(char *phrase, float rotationKey) 
{   
    int i=0; //i is the integer variable that will count through each individual character of the phrase array. It is initialised as 0 to start at the beginning of the array.
    FILE *output; //declares the file which will be referred to as output in the code whenever it is used
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
    while(phrase[i] != EOF) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to the end of the file EOF, because then it no longer fits the condition of != EOF (not equal to EOF).
    {
        /*
        phrase[i] - rotationKey utilises the ASCII values of each letter. A has the value 65, and Z the value 90. All capital letters are
        within 65 and 90. The rotationKey is taken away from the value of the phrase[i] ASCII value and therefore results in a new decrypted 
        ASCII character as it shifts it back into the original plain English version rather than the shifted cipher version. Only one of
        these if .. else if statements happens for each while loop.
        */
        if(phrase[i]<=64 || phrase[i]>=91) //if the value of the phrase[i] character in the original plain English text message is something other than a capital letter, this block of code will execute
        {
            phrase[i] = phrase[i]; //phrase[i] remains unchanged
        }  
        else if((phrase[i]-rotationKey)>=65 && (phrase[i]-rotationKey)<=90) //if the new decrypted ASCII falls within the capital letter range of 65 and 90 (i.e. it remains a capital letter not a different ASCII character that isn't English) this block of code will execute
        {
            phrase[i] = phrase[i] - rotationKey; //the ASCII value of phrase[i] is shifted back by the rotationKey in order to decrypt it into the plain English ASCII character
        }
        else if((phrase[i]-rotationKey)<65) //if the new decrypted ASCII value falls below the capital letter range
        {
            phrase[i] = phrase[i] + 26 - rotationKey; //phrase[i] is shifted back by the rotationKey, but 26 is added (the number of letters in the alphabet) so that it stays within the capital letter range
        }
        fprintf(output, "%c", phrase[i]); //prints the decrypted letter to the file 'output'
        printf("%c", phrase[i]); //prints the decrypted letter to the screen (stdout)
        i++; //increments i, the variable that counts through each letter of the phrase/message, so that the next while loop execution will read and decrypt the next character of the phrase/message
    }
}

/*
This is the substitution encryption function. When it is called, it takes the values for phrase and encryptionKey (these are the arguments)
and uses them in its body to execute the rest of the code. This code takes a message in plain English text (phrase) and an array of 26 
capital letters (encryptionKey). Each letter of the phrase is replaced by a random letter of the alphabet depending on the substitution 
cipher array. For example, if the encryptionKey was QAZXSWEDCVFRTGBNHYUJMKILOP, A would be encrypted as Q, and B as A - so if the word was 
"ABBA" it would be encrypted into "QAAQ". In other words, the letter of the alphabet at position 'p' is encrypted into the letter of the 
encryptionKey at position 'p'. This function encrypts a plain text message back into encrypted text by this principle, and prints
each encrypted letter one at a time to both the screen (stdout) and the file 'output'.
*/
char subencrypt(char *phrase, char *encryptionKey)
{  
    int i=0; //declares and initialises the integer variable i, which will be used to count through each letter of the phrase/message. It is set to 0 in order to begin at the first letter.
    char x=0; //declares and initialises the char variable x, which will be used to count through the alphabet in order to match each letter of the phrase to the alphabet, so that it can then be changed into the corresponding letter of the cipher text. x marks this position
    FILE *output; //declares the file which will be referred to as output in the code whenever it is used
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
    char alphabet[30]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declares and initialises an array as the alphabet. Each letter of the phrase will be matched to this until the correct one is found, so it can be changed into the corresponding letter of the cipher text.
    while(phrase[i] != EOF) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to the end of the file EOF, because then it no longer fits the condition of != EOF (not equal to EOF)
    {
        if(phrase[i]>=65 && phrase[i]<=90) //if the letter being analysed is a capital letter, this block of code will execute
        {
            while(phrase[i] != alphabet[x]) //the while loop will continue until the letter phrase[i] matches the letter alphabet[x]
            {
                x++; //x is incremented so that the while loop condition changes each time until the correct value of x is found - the one where the phrase[i] matches a letter of alphabet[x]. This then means the corresponding letter of the encryptionKey can be found at the same position x.
            }
            /*
            Now that phrase[i]'s position in the alphabet has been found (it is at position 'x'), the letter that it should be 
            encrypted into is known. It is the letter at position x in the encryptionKey array.
            */     
            printf("%c", encryptionKey[x]); //prints the value of the char encryptionKey[x] (the encrypted value of phrase[i]) to the screen
            fprintf(output, "%c", encryptionKey[x]); //prints the value of the char encryptionKey[x] (the encrypted value of phrase[i]) to the file 'output'
            x=0; //reinitialises x to 0 so that the analysis of the next letter starts at the beginning of the alphabet, not wherever it left off after the previous analysis
        }
        else //if phrase[i] is something other than a capital letter, this block of code will be executed. phrase[i] remains unchanged so numbers or other characters aren't changed in the encrypted text
        {
            printf("%c", phrase[i]); //the char phrase[i] is printed to the screen unchanged
            fprintf(output, "%c", phrase[i]); //the char phrase[i] is printed to the file 'output' unchanged
        }
        i++; //increments i so that for the next while loop, the next letter of the phrase is analysed and encrypted
    }
}

/*
This is the substitution decryption function. When it is called, it takes the values for phrase and encryptionKey (these are the arguments)
and uses them in its body to execute the rest of the code. This code takes a message in encrypted English text (phrase) and an array of 26 
capital letters (encryptionKey). Each letter of the encrypted phrase is replaced by the corresponding letter of the alphabet depending 
on the substitution cipher array, so that the message is returned into plain English text. For example, if the encryptionKey was 
QAZXSWEDCVFRTGBNHYUJMKILOP, Q would be decrypted back to A, and A would be decrypted back to B - so if the encryption was "QAAQ" 
the decryption would be "ABBA". In other words, the letter of the encryptionKey at position 'p' is decrypted into the letter of the 
alphabet at position 'p'. This function decrypts an encrypted text message back into plain English text by this principle, and prints
each decrypted letter one at a time to both the screen (stdout) and the file 'output'.
*/
char subdecrypt(char *phrase, char *encryptionKey)
{
    int i=0; //declares and initialises the integer variable i, which will be used to count through each letter of the phrase/message. It is set to 0 in order to begin at the first letter.
    char x=0; //declares and initialises the char variable x, which will be used to count through the alphabet in order to match each letter of the phrase to the alphabet, so that it can then be changed into the corresponding letter of the cipher text. x marks this position
    FILE *output; //declares the file which will be referred to as output in the code whenever it is used
    output = fopen("messageOutput.txt", "w"); //opens the file, indicates it will be written to by the "w", and assigns it to 'output'
    char alphabet[30]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declares and initialises an array as the alphabet. Each letter of the phrase will be matched to this until the correct one is found, so it can be changed into the corresponding letter of the cipher text.
    while(phrase[i] != EOF) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to the end of the file EOF, because then it no longer fits the condition of != EOF (not equal to EOF).
    {
        if(phrase[i]>=65 && phrase[i]<=90) //if the letter being analysed is a capital letter, this block of code will execute
        {
            while(phrase[i] != encryptionKey[x]) //the while loop will continue until the letter phrase[i] matches the letter encryptionKey[x]
            {
                x++; //x is incremented so that the while loop condition changes each time until the correct value of x is found - the one where the phrase[i] matches a letter of encryptionKey[x]. This then means the corresponding letter of the alphabet can be found at the same position x.
            }
            /*
            Now that phrase[i]'s position in the encryptionKey has been found (it is at position 'x'), the letter that it should be 
            decrypted back to is known. It is the letter at position x in the alphabet array.
            */            
            printf("%c", alphabet[x]); //prints the value of the char alphabet[x] (the decrypted value of phrase[i]) to the screen
            fprintf(output, "%c", alphabet[x]); //prints the value of the char alphabet[x] (the decrypted value of phrase[i]) to the file 'output'
            x=0; //reinitialises x to 0 so that the analysis of the next letter starts at the beginning of the encryptionKey, not wherever it left off after the previous analysis
        }
        else //if phrase[i] is something other than a capital letter, this block of code will be executed. phrase[i] remains unchanged so numbers or other characters aren't changed in the decrypted text
        {
            printf("%c", phrase[i]); //the char phrase[i] is printed to the screen unchanged
            fprintf(output, "%c", phrase[i]); //the char phrase[i] is printed to the file 'output' unchanged
        }
        i++; //increments i so that for the next while loop, the next letter of the phrase is analysed and decrypted 
    }
}

/*
This is the unseen rotational decryption function definition which holds the code that this function executes when it is called. It takes
the values for phrase and rotationKey as arguments to use in the body. It decrypts the phrase message read from the input file, and then 
prints the decrypted phrase to the messageOutput.txt file as well as the screen. Once it has decrypted and printed the message (to both 
the screen (stdout) and the file 'output'), it reencrypts it for next time the function is called. Since the exact rotationKey is unknown, 
multiple need to be tested, which is why the phrase needs to be restored into its original encrypted version each time. Ideally this
function would also match the decrypted phrases to a dictionary in order to pick which decryption was the correct one, but I could not do
that so neither can my program. RIP.
*/
char unseenrotdecrypt(char *phrase, float rotationKey)
{
    FILE *output;
    output = fopen("messageOutput.txt", "w");
    
    int i=0; //i is the variable that will count through each individual character of the phrase array. It is initialised as 0 to start at the beginning of the array.
    while(phrase[i] != EOF) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is the end of the file EOF, because then it no longer fits the condition of != EOF
    {
        if(phrase[i]<=64 || phrase[i]>=91) //if the value of the phrase[i] character in the original plain English text message is something other than a capital letter, this block of code will execute
        {
            phrase[i] = phrase[i]; //phrase[i] remains unchanged
        }  
        else if((phrase[i]-rotationKey)>=65 && (phrase[i]-rotationKey)<=90) //if the new decrypted ASCII falls within the capital letter range of 65 and 90 (i.e. it remains a capital letter not a different ASCII character that isn't English) this block of code will execute
        {
            phrase[i] = phrase[i] - rotationKey; //the ASCII value of phrase[i] is shifted back by the rotationKey in order to decrypt it into the plain English ASCII character
        }
        else if((phrase[i]-rotationKey)<65) //if the new decrypted ASCII value falls below the capital letter range, this else...if statement will execute
        {
            phrase[i] = phrase[i] + 26 - rotationKey; //phrase[i] is shifted back by the rotationKey, but 26 is added (the number of letters in the alphabet) so that it stays within the capital letter range
        }
        i++;
    }
    
    printf("%s", phrase); //prints the new decrypted phrase to the screen
    fprintf(output, "%s", phrase); //prints the new decrypted phrase to the file 'output'
    
    i=0; //i is reset back to 0 before the phrase is re-encrypted so it starts at the beginning of the phrase
    while(phrase[i] != EOF) //the content of this while loop will continue to execute until the computer finds that the character 'phrase[i]' is equal to the end of the file
    {
        if(phrase[i]<=64 || phrase[i]>=91) //if the character is something not within the capital letter range, it remains unchanged
        {
            phrase[i] = phrase[i];
        }
        else if(((phrase[i] + rotationKey)>=65) && ((phrase[i] + rotationKey)<=90)) //if the re-encrypted character will still fall within the capital letter range, only the rotationKey is readded back onto it to get it back to its original encrypted value
        {
            phrase[i] = phrase[i] + rotationKey;
        }
        else if((phrase[i] + rotationKey)>90) //if the re-encrypted is above the capital letter range, 26 is taken away so that it falls back within the range without change the shift value
        {
            phrase[i] = phrase[i] - 26 + rotationKey;
        }
        i++; //i is incremented to move onto the next letter of the phrase in the next while loop
    }
}