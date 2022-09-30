/* 
*
* 48430 Fundamentals of C Programming Assessment 3
* Name: Mohit Sewani
* Student ID: 12700771
* Last updated: 14/10/2021
* 
* This algorithm is a simple Caesar Shift cipher. Each character in any
* given text file is substituted by a replacement character that is a 
* fixed number of positions away from the original character.
*
* To be updated with comments.
*
*/

#include <stdio.h>
#include <stdlib.h>

void encryption(char in_file[])
{
    char ch;
    FILE *fp1, *fp2;

/* Reads the file entered as input by the user. */

    fp1 = fopen(in_file, "rb");

    if(fp1 == NULL)
    {
        printf("File does not exist.");
    }

/* File to be written to */

    fp2 = fopen("temp.txt", "wb");
    if(fp2 == NULL)
    {
        printf("Error in creating a temporary text file.");
        fclose(fp1);
    }

/* Reads every character in the file and replaces it into another file with a numerical shift */

    while(1)
    {
        ch = fgetc(fp1);
        if(ch == EOF)
        {
            break;
        }
        else
        {
            ch = ch + 5;
            fputc(ch, fp2);
        }
    }

    fclose(fp1);
    fclose(fp2);

    fp1 = fopen(in_file, "wb");
    if(fp1 == NULL)
    {
        printf("File does not exist");
    }

    fp2 = fopen("temp.txt", "rb");
    if(fp2 == NULL)
    {
        printf("File does not exist");
        fclose(fp2);
    }

/* Encrypted text is overwritten into the original text file */

    while(1)
    {
        ch = fgetc(fp2);
        if(ch == EOF)
        {
            break;
        }
        else
        {
            fputc(ch, fp1);   
        }
    }

    printf("File %s has been encrypted.", in_file);
    fclose(fp1);
    fclose(fp2);
    remove("temp.txt");
    
}