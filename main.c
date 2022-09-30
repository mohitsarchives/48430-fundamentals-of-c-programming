/*
Date of making: 07/10/2021

Mohit Sewani 12700771
Jacob Reed 14162996
Jerome Sario 13903051
Clark Kong 13545138
Isa Mukaramov 13515874  
Nicholas Ge 13544541


*/

/* For the compresson, decrompression, encrytion, and decryption to work sepereate files
 were made and introduced as a header file so they could be used in main.c*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "compression.h"
#include "decompression.h"
#include "encryption.h"
#include "decryption.h"

/*name size is limited to 15 characters*/
#define MAX_NAME_SIZE 15

/*stuctures are listed below*/
struct diary
{
    char name[50];
    int day;
    int month;
    int year;

    char content[9999];
};

typedef struct diary diary_t;

/* All funtions are listed below*/
void addDiary(void);
void readDiary(void);
void deleteDiary(void);
void printMainMenu(void);
int scanInput(void);
void encryptCompress(void);
void decryptDecompress(void);


int main(void)
{
    
    int choice, exitValue;
/*checks users inputs to determine which function to run*/
    while(exitValue == 0){
        printMainMenu();
        choice = scanInput();
        
        switch(choice){
            case 1: 
                printf("Add a new diary entry.\n");
                addDiary();
                break;

            case 2:
                printf("Read an existing diary entry.\n");
                readDiary();
                break;

            case 3:
                printf("Delete an existing diary entry.\n");
                deleteDiary();
                break;

            case 4:
                printf("Encrypt and compress your diary entry.\n");
                encryptCompress();
                break;

            case 5:
                printf("Decrypt and Decompress your diary entry.\n");
                decryptDecompress();
                break;

            case 6:    
                printf("Thank you for using Diary Manager.\n");
                exitValue = 1;
                break;                

            default:
                printf("Invalid choice, please try again.\n");
                while ( getchar() != '\n' ); 
                break;
            
        }
        
    }

    return 0;
}


/*Main menu is diplays the options for user dependent on what they want to do*/
void printMainMenu(void)
                        
{
    printf("\n-----(Diary Entry)----\n");
   
    printf("\nPlease select options below\n");
    printf("\n"
           "1. Log your personal journal\n"    
           "2. Read an existing journal\n"
           "3. Delete journal\n"
           "4. Encrypt and compress your journal\n"
           "5. Decrypt and decompress your journal\n"
           "6. Close the program\n\n"
           ">");
           
}

/* Reads an integer input to select a menu option */
int scanInput(void)
{
    int choice;
    scanf("%d",&choice);    
    return choice;
}


void addDiary(void)
{
    char fileName[50];
    diary_t newDiary;
    
    printf("Please enter the name of the new Diary file>");
    scanf("%s", fileName);

    while(1)
    {
        printf("Enter users name>");
        scanf("%s", newDiary.name);
        break;
    }
    while(1)
    {
        printf("Enter day>");
        scanf("%d", &newDiary.day);
        /* input is restricted to 31 days and nothing less than 1*/
        if(newDiary.day>=1 && newDiary.day<=31)
        {
            break;
        }
        else
        {
        printf("Invalid day, please try again. \n");
        }
    }
   
    while(1)
    {
        printf("Enter month>");
        scanf("%d",&newDiary.month);
        /* input is restricted to 12 months and nothing less than 1*/
        if(newDiary.month>=1 && newDiary.month<=12) 
        {
            break;
        }
            else
        {
            printf("Invalid month, please try again. \n");
        }
    }
  
    while(1)
    { 
        printf("Enter year>");
        scanf("%d",&newDiary.year);
        /* input is restricted*/
        if(newDiary.year>=1800 && newDiary.year<=2021) 
        {
            break;
        }
            else
        {
            printf("Invalid year, please try again. \n");
        }
     }   

    
    printf("Enter diary below. To stop editing, enter '*'\n");
    int breakCase = 0;
    int charCount = 0;
    char c;
    while((c = getc(stdin)) != '*'){                   
            newDiary.content[charCount] = c;
            charCount++;    
        } 
    while ( getchar() != '\n');   
    
    newDiary.content[charCount+1] = '\0';
    
    

    FILE *pFile;
    pFile = fopen (fileName, "wb");
    if (!pFile){
            printf("Error opening the file");
    }else{
        fwrite(&newDiary, sizeof(diary_t), 1, pFile);
        fclose(pFile);
    }

    return;
}


void encryptCompress(void){
    char filename[100];
    char finalName[100];
    printf("Please enter the file you want to encrypt/compress>");
    scanf("%s", filename);
    printf("Please enter a name for the output file (including an extension)>");
    scanf("%s", finalName);
    compressFile(filename, finalName);
    encryption(finalName);
    
    while ( getchar() != '\n' ); 
    return;
}

void decryptDecompress(void){
    char filename[100];
    char finalName[100];
    printf("Please enter the encrypted/compressed file name>");
    scanf("%s", filename);
    printf("Please enter a name for the output file (including .txt)");
    scanf("%s", finalName);
    printf("stuff1\n");
    decryption(filename);
    decompressFile(filename,finalName);
    
    while ( getchar() != '\n' ); 
    return;
}


void deleteDiary(void)
{   
    FILE *FP;
    char filename[100];
    printf("Please enter the file you wish to delete>");
    scanf("%s", filename);
    FP = fopen(filename, "w");
    if(!FP){
        printf("File does not exist.\n");
        return;
    }
    fclose(FP);
    if(remove(filename) == 0){
        printf("File successfully deleted.\n");
    }else{
        printf("File unable to be deleted.\n");
    }
    
    return;
}



void readDiary(void)
{   
    char c;
    char filename[100];
    printf("Please enter the file you want to read>");
    scanf("%s", filename);

    FILE *pFile;
    pFile = fopen (filename, "rb");
    if (!pFile){
            printf("Error opening the file");
    }else{
        diary_t openDiary;

        fread(&openDiary, sizeof(diary_t), 1, pFile);
        
        printf("Name of Author> %s\n", openDiary.name);
        printf("Date created> %d/%d/%d\n",openDiary.day,openDiary.month,openDiary.year);
        printf("%s",openDiary.content);


        fclose(pFile);
    }
    return;
}