/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3 - Compression
 * Name: Jacob Reed
 * Student ID: 14162996
 * Date of submission: 10 / 10 / 2021
 *
 * This compression algorithm is an implementation of LZ77 compression, a form
 * of lossless compression.
 * This algorithm finds exact matches of strings and creates triplets made of
 * offset, length and char. This creates a blueprint to re-create the file.
 * This implementation is intended for text files, however may be applicable
 * to all file types as the functions manipulate single bytes.

 * potential changes;
 * MUST IMPLEMENT CHANGING COMPRESSION FILE NAME - user choose name, push
    an extension on the file or add to the name.
 * continued function separation
 * better commenting
 * efficiencies may be possible in the algorithm
******************************************************************************/


#include <stdio.h> /*printf(), fopen(), fgetc(), EOF, FILE, fwrite(), scanf()*/
#include <stdlib.h> /*malloc(), realloc(), free(),*/

#define bufferSize 250 /* used to determine buffer/window size. 
MUST BE LESS THAN OR EQUAL TO 255 DUE TO 8 BIT INT */

void compressFile(char IFile[], char OFile[]){

/******************************************************************************
Initialisation of necessary tracking ints and array streams
******************************************************************************/
    
    int count = 0, pos = 0, debugMode = 0;
    char ch;
    
    /* char array of the entire file */
    char* inputStream;
    if((inputStream = (char*) malloc(0)) == NULL){
        printf("Memory allocation failed.\n");
        return;
    }
    
    /* unsigned char array for the compression data */
    unsigned char* compressedData;
    if((compressedData = malloc(0)) == NULL){
        printf("Memory allocation failed.\n");
        free(inputStream);
        free(compressedData);
        return;
    }
    
    /* receive all input data, allocate to input stream and count chars*/
    FILE* FP;
    FP = fopen(IFile, "rb");
    if(FP == NULL){
        
        printf("File unable to be opened.\n");
        free(compressedData);
        free(inputStream);
        
        return;
        
    }
    
    int fileCharLength = 1;
    for (ch=fgetc(FP); ch!=EOF; ch=fgetc(FP)){
        inputStream = (char*)realloc(inputStream, fileCharLength*sizeof(char));
        inputStream[fileCharLength-1] = ch;
        fileCharLength++;
    }
    inputStream = (char*)realloc(inputStream, fileCharLength*sizeof(char));
    inputStream[fileCharLength] = EOF;

    fclose(FP);
    printf("Buffer filled.\n");

    
/******************************************************************************
Main loop of function. 
******************************************************************************/

    while(pos<fileCharLength){

        int i = pos;

        /*track largest triplet for a given position*/
        unsigned char largestO = 0;
        unsigned char largestL = 0;
        unsigned char largestC = '0';

        while(i>=0 && pos-i<bufferSize){
            
            /*track temporary triplet for each potential largest*/
            unsigned char tempO = 0;
            unsigned char tempL = 0;
            unsigned char tempC = '0';

            /* Find any match with current position char */
            if(inputStream[i] == inputStream[pos]){
                int j = 0;
                
                /* checks several conditions; 
                    window check is not past the current position
                    buffer check is not past end of file
                    buffer is less than bufferSize
                    window check char is equal to buffer check char
                */
                while(i+j<pos && pos+j<fileCharLength && j<bufferSize && inputStream[i+j] == inputStream[pos+j]){
                    j++;
                    tempO = pos - i;
                    tempL = j;
                    tempC = inputStream[pos+j];                    
                }

                /* if no match found, creates "new" triplet otherwise triplets
                to push to largest if temp length is larger */
                if(tempC == '0'){
                    largestC = inputStream[pos];
                }else if(largestL<tempL){
                    largestO = tempO;
                    largestL = tempL;
                    largestC = tempC;
                }
            }
            i--;
        }
        /* moves position to next non-checked char */
        pos = pos + largestL + 1;
        
        /*debug used to check the output of all triplets generated*/
        if(debugMode == 1){
            printf("%d , %d , %d \n", largestO, largestL, largestC);
        }

        /*increases size of compressedData array and pushes largest triplet*/
        count++;
        compressedData = (unsigned char*) realloc(compressedData, count*3*sizeof(char));
        compressedData[(count*3)-3] = largestO;
        compressedData[(count*3)-2] = largestL;
        compressedData[(count*3)-1] = largestC;   
    }
    

    /*writes compressed data to new compression file*/
    

    FILE* NFP;
    NFP = fopen(OFile, "wb");
    if(NFP == NULL){
        printf("Failed to open new compression file");
    }
    fwrite(compressedData,sizeof(char),count*3,NFP);
    fclose(NFP);

    free(inputStream);
    free(compressedData);
    printf("Compression Successful");

    return;   
}

/*can be used when no main.c is available. */
/*
int main(void){
    char Ifile[100];
    char Ofile[100];
    printf("Enter file to compress>");
    scanf("%s", Ifile);
    printf("Enter compressed file name>");
    scanf("%s", Ofile);
    compressFile(Ifile, Ofile);
    return 0;
} */