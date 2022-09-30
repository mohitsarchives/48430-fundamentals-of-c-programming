/*
48430 Fundamentals of C Programming - Assignment 3 - Compression
Name: Jerome Sario
Id: 13903051
*/

#include <stdio.h>
#include <stdlib.h>

void decryption(char in_file[])
{
    char ch;
    FILE *fp1, *fp2;

    fp1 = fopen(in_file, "rb");
    if(fp1 == NULL)
    {
        printf("File does not exist.");
    }

    fp2 = fopen("temp.txt", "wb");
    if(fp2 == NULL)
    {
        printf("Error in creating a temporary text file.");
        fclose(fp1);
    }
    while(1)
    {
        ch = fgetc(fp1);
        if(ch == EOF)
        {
            break;
        }
        else
        {
            ch = ch - 5;
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

    /*printf("File %s has been decrypted.", in_file);*/
    fclose(fp1);
    fclose(fp2);
}